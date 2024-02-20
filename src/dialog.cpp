#include "dialog.h"
#include "ui_dialog.h"

#include <QStandardPaths>
#include <QSettings>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QDesktopServices>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
	// Load Settings //

	QString roamingPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	roamingPath = roamingPath.left(roamingPath.lastIndexOf('/'));
	QSettings* settings = new QSettings("settings.conf",QSettings::IniFormat);
	if(!settings->value("qtSettingsPath").isValid()) settings->setValue("qtSettingsPath", roamingPath+"/QtProject/qtcreator");

	// Check QtVersions //

	QHash<QString, QString> qtVersions;
	QFile versionsFile(settings->value("qtSettingsPath").toString()+"/qtversion.xml");
	if(!versionsFile.open(QIODevice::ReadOnly)){qWarning()<<R"(Impossible d'ouvrir le fichier "qtversion.xml")"; std::exit(EXIT_FAILURE);}
	QString VData = versionsFile.readAll();
	versionsFile.close();

	QRegularExpression rxv(R"(Id">(\d).+?QMakePath">.+?(\d+\.\d+\.\d+).+?Source">(.*?)<)",QRegularExpression::DotMatchesEverythingOption);
	QRegularExpressionMatchIterator i = rxv.globalMatch(VData);
	while(i.hasNext()){
		QRegularExpressionMatch m = i.next();
		qtVersions.insert(!m.captured(3).isEmpty() ? m.captured(3) : m.captured(1), m.captured(2));}

	// Check QtKits //

	QHash<QString, QString> qtKits;
	QFile kitsFile(settings->value("qtSettingsPath").toString()+"/profiles.xml");
	if(!kitsFile.open(QIODevice::ReadOnly)){qWarning()<<R"(Impossible d'ouvrir le fichier "profiles.xml")"; std::exit(EXIT_FAILURE);}
	QString KData = kitsFile.readAll();
	kitsFile.close();

	QRegularExpression rxk(R"(QtInformation">(.+?)<.+?Id">(.+?)<.+?Name\">(.+?)<)",QRegularExpression::DotMatchesEverythingOption);
	QRegularExpressionMatchIterator j = rxk.globalMatch(KData);
	while(j.hasNext()){
		QRegularExpressionMatch m = j.next();
		qtKits.insert(m.captured(3).replace("%{Qt:Version}",qtVersions.value(m.captured(1))),m.captured(2));
	}

	// UI SETUP //

	ui->setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui->directoryLineEdit->setText(settings->value("defaultProjectPath").toString());
	ui->pathCheckBox->setChecked(!ui->directoryLineEdit->text().isEmpty());

	for(auto i = qtKits.begin(); i != qtKits.end(); ++i)
		ui->projectKitCombo->addItem(i.key(), i.value());

	ui->projectTypeCombo->addItem(ProjectType::QT_CONSOLE_APP);
	ui->projectTypeCombo->addItem(ProjectType::QT_WIDGETS_APP);

	ui->baseClassCombo->addItem(BaseClass::QMAINWINDOW);
	ui->baseClassCombo->addItem(BaseClass::QWIDGET);
	ui->baseClassCombo->addItem(BaseClass::QDIALOG);

	ui->classNameLineEdit->setText("MainWindow");

	// CONNECTIONS

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [=]{
		ui->warningLabel->clear();
		ui->warningLabel->setStyleSheet("background-color: none;");
		ui->projectNameLineEdit->setStyleSheet("background-color: white;");
		ui->directoryLineEdit->setStyleSheet("background-color: white;");
	});

	connect(ui->projectTypeCombo, &QComboBox::currentTextChanged, this, [=](const QString& value){
		bool enable = value == ProjectType::QT_WIDGETS_APP;
		ui->classNameLabel->setEnabled(enable);
		ui->classNameLineEdit->setEnabled(enable);
		ui->baseClassLabel->setEnabled(enable);
		ui->baseClassCombo->setEnabled(enable);
		ui->formCheckBox->setEnabled(enable);
	});

	connect(ui->baseClassCombo, &QComboBox::currentTextChanged, this, [=](const QString& value){
		QString text =  ui->classNameLineEdit->text();
		if(text.isEmpty() || text == "MainWindow" || text == "Widget" || text == "Dialog"){
			if(value == BaseClass::QMAINWINDOW) ui->classNameLineEdit->setText("MainWindow");
			if(value == BaseClass::QWIDGET) ui->classNameLineEdit->setText("Widget");
			if(value == BaseClass::QDIALOG) ui->classNameLineEdit->setText("Dialog");
		}
	});

	connect(ui->browseButton, &QPushButton::clicked, this, [=]{ui->directoryLineEdit->setText(QFileDialog::getExistingDirectory(this,"QtExpress",qApp->applicationDirPath()));});

	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [=]{

		// Check user datas
		if(ui->projectNameLineEdit->text().isEmpty()) {warn(ui->projectNameLineEdit, "Le nom du projet ne peut pas etre vide"); return;}
		if(ui->directoryLineEdit->text().isEmpty()) {warn(ui->directoryLineEdit, "L'emplacement du projet ne peut pas etre vide"); return;}
		if(!QRegExp("[\\w-]+").exactMatch(ui->projectNameLineEdit->text())) {warn(ui->projectNameLineEdit, "Le nom du projet est invalide"); return;}
		if(!QRegExp("[\\w-]+").exactMatch(ui->classNameLineEdit->text())) {warn(ui->classNameLineEdit, "Le nom de la classe est invalide"); return;}

		// Creating project
		QString project =createProject();
		if(project.isEmpty()) return;

		// Open new project
		QDesktopServices::openUrl(QUrl("file:///"+project));

		if(ui->pathCheckBox->isChecked())
			settings->setValue("defaultProjectPath", ui->directoryLineEdit->text());
		accept();
	});
}

Dialog::~Dialog(){delete ui;}

void Dialog::warn(QWidget* widget, const QString& text)
{
	ui->warningLabel->setText(" "+text);
	ui->warningLabel->setStyleSheet("background-color: #ff8080;");
	widget->setStyleSheet("background-color: LightCoral;");
	timer->start(2000);
}

QString Dialog::createProject()
{
	// Working variables

	bool isConsoleApp = ui->projectTypeCombo->currentText() == ProjectType::QT_CONSOLE_APP;
	QString baseClass = ui->baseClassCombo->currentText();
	QString className = ui->classNameLineEdit->text();
	QString HFileName = className.toLower()+".h";
	QString CFileName = className.toLower()+".cpp";
	QString UIFileName = className.toLower()+".ui";

	QDir projectDir(ui->directoryLineEdit->text()+QDir::separator()+ui->projectNameLineEdit->text());
	if(projectDir.exists()) {warn(ui->projectNameLineEdit, "Ce projet exist deja"); return "";}

	QDir srcDir(ui->srcCheckBox->isChecked() ? projectDir.absolutePath()+QDir::separator()+"src" : projectDir);
	QString projectName = ui->projectNameLineEdit->text();

	QDir().mkpath(srcDir.absolutePath());
	QFile::copy("files\\common-pro-user",srcDir.absolutePath()+QDir::separator()+projectName+".pro.user");

	// <projectName>.pro.user

	QFile userFile(srcDir.absolutePath()+QDir::separator()+projectName+".pro.user");
	if(!userFile.open(QIODevice::ReadOnly)){qWarning()<<"Impossible d'ouvrir le fichier \""+userFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
	QString data = userFile.readAll(); userFile.close();

	data.replace("ProjectConfiguration.Id\"><","ProjectConfiguration.Id\">"+ui->projectKitCombo->currentData().toString()+"<");
	data.replace("Qt4RunConfiguration:","Qt4RunConfiguration:"+srcDir.absolutePath()+"/"+projectName+".pro");
	data.replace("RunConfiguration.BuildKey\"><","RunConfiguration.BuildKey\">"+srcDir.absolutePath()+"/"+projectName+".pro<");
	data.replace("RunConfiguration.WorkingDirectory\"><","RunConfiguration.WorkingDirectory\">"+projectDir.absolutePath()+"<");

	if(!userFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+userFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
	userFile.write(data.toUtf8()); userFile.close();

	// <projectName>.pro

	QString code;
	code += QString("QT %1\n\n").arg(isConsoleApp ? "-= gui" : "+= widgets");
	code += QString("CONFIG += debug_and_release debug_and_release_target\n\n");
	code += QString("DEFINES += QT_DEPRECATED_WARNINGS\n\n");
	code += QString("SOURCES += \\\n\tmain.cpp%1\n\n").arg(!isConsoleApp ? " \\\n\t"+CFileName : "");
	if(!isConsoleApp) code += QString("HEADERS += \\\n\t%1\n").arg(HFileName);
	if(!isConsoleApp && ui->formCheckBox->isChecked()) code += QString("\nFORMS += \\\n\t%1\n").arg(UIFileName);

	QFile proFile(srcDir.absolutePath()+QDir::separator()+projectName+".pro");
	if(!proFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+proFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
	proFile.write(code.toUtf8()); proFile.close();

	// main.cpp

	code.clear();
	if(!isConsoleApp) code += QString("#include \"%1\"\n\n").arg(HFileName);
	code += QString("#include <Q%1Application>\n\n").arg(isConsoleApp ? "Core" : "");
	code += QString("int main(int argc, char *argv[])\n{\n");
	code += QString("\tQ%1Application a(argc, argv);\n").arg(isConsoleApp ? "Core" : "");
	if(!isConsoleApp) code += QString("\t%1 w;\n\tw.show();\n").arg(className);
	code += QString("\treturn a.exec();\n}\n");

	QFile mainFile(srcDir.absolutePath()+QDir::separator()+"main.cpp");
	if(!mainFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+mainFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
	mainFile.write(code.toUtf8()); mainFile.close();

	// End if is QT Console App

	if(isConsoleApp) return proFile.fileName();

	// <className>.h

	code.clear();
	code += QString("#ifndef %1_H\n").arg(className.toUpper());
	code += QString("#define %1_H\n\n").arg(className.toUpper());
	code += QString("#include <%1>\n\n").arg(baseClass);
	if(ui->formCheckBox->isChecked()) code += QString("namespace Ui {class %1;}\n\n").arg(className);
	code += QString("class %1 : public %2\n{\n\tQ_OBJECT\n\n\tpublic:\n").arg(className, baseClass);
	code += QString("\t\t%1(QWidget* parent = nullptr);\n\t\t~%1();\n").arg(className);
	if(ui->formCheckBox->isChecked()) code += QString("\n\tprivate:\n\t\tUi::%1 *ui;\n").arg(className);
	code += QString("};\n\n#endif // %1_H\n").arg(className.toUpper());

	QFile HFile(srcDir.absolutePath()+QDir::separator()+HFileName);
	if(!HFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+HFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
	HFile.write(code.toUtf8()); HFile.close();

	// <className>.cpp

	code.clear();
	code += QString("#include \"%1\"\n").arg(HFileName);
	if(ui->formCheckBox->isChecked()) code += QString("#include \"ui_%1\"\n").arg(HFileName);
	code += QString("\n%1::%1(QWidget* parent) : %2(parent)").arg(className, baseClass);
	if(ui->formCheckBox->isChecked()) code += QString(", ui(new Ui::%1)\n{\n\tui->setupUi(this);").arg(className);
	else code += QString("\n{\n");
	code += QString("\n}\n\n%1::~%1()\n{\n%2\n}\n").arg(className, ui->formCheckBox->isChecked() ? "\tdelete ui;" : "");

	QFile CFile(srcDir.absolutePath()+QDir::separator()+CFileName);
	if(!CFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+CFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
	CFile.write(code.toUtf8()); CFile.close();

	// <className>.ui

	code.clear();
	code += QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<ui version=\"4.0\">\n");
	code += QString(" <class>%1</class>\n <widget class=\"%2\" name=\"%1\">\n").arg(className, baseClass);
	code += QString("  <property name=\"geometry\">\n   <rect>\n    <x>0</x>\n    <y>0</y>\n    <width>800</width>\n    <height>600</height>\n   </rect>\n");
	code += QString("  </property>\n  <property name=\"windowTitle\">\n   <string>%1</string>\n  </property>\n").arg(className);
	if(baseClass == BaseClass::QMAINWINDOW)
		code += QString("  <widget class=\"QWidget\" name=\"centralwidget\"/>\n  <widget class=\"QMenuBar\" name=\"menubar\"/>\n  <widget class=\"QStatusBar\" name=\"statusbar\"/>\n");
	code += QString("  </widget>\n <resources/>\n <connections/>\n</ui>\n");

	QFile UIFile(srcDir.absolutePath()+QDir::separator()+UIFileName);
	if(!UIFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+UIFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
	UIFile.write(code.toUtf8()); UIFile.close();

	return proFile.fileName();
}

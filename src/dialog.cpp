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
	roamingPath = roamingPath.left(roamingPath.lastIndexOf('/'))+"/QtProject/";

	QSettings* settings = new QSettings(roamingPath+"QtCreator.ini",QSettings::IniFormat);
	QString defaultProjectPath = settings->value("Directories/Projects").toString();

	// Check QtVersions //

	QHash<QString, QString> qtVersions;
	QFile versionsFile(roamingPath+"qtcreator/qtversion.xml");
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
	QFile kitsFile(roamingPath+"qtcreator/profiles.xml");
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

	ui->directoryLineEdit->setText(defaultProjectPath);
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
			if(defaultProjectPath != ui->directoryLineEdit->text())
				settings->setValue("Directories/Projects", ui->directoryLineEdit->text());
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
	bool useBuild = ui->buildCheckBox->isChecked();
	bool useForm = ui->formCheckBox->isChecked();
	QString baseClass = ui->baseClassCombo->currentText();
	QString className = ui->classNameLineEdit->text();
	QString HFileName = className.toLower()+".h";
	QString CFileName = className.toLower()+".cpp";
	QString UIFileName = className.toLower()+".ui";

	QDir projectDir(ui->directoryLineEdit->text()+QDir::separator()+ui->projectNameLineEdit->text());
	if(projectDir.exists()) {warn(ui->projectNameLineEdit, "Ce projet existe deja"); return "";}

	QDir srcDir(ui->srcCheckBox->isChecked() ? projectDir.absolutePath()+QDir::separator()+"src" : projectDir);
	QString projectName = ui->projectNameLineEdit->text();
	QString userFilePath = srcDir.absolutePath()+QDir::separator()+projectName+".pro.user";
	QString proFilePath = srcDir.absolutePath()+QDir::separator()+projectName+".pro";

	QDir().mkpath(srcDir.absolutePath());
	QString data;

	// <projectName>.pro.user
	{
		QString buildPath = useBuild ? "../build/%{Project:Name}-%{Kit:FileSystemName}-%{BuildConfig:Name}" : "";
		data = ProjectFile::USER_FILE.arg(ui->projectKitCombo->currentData().toString(),buildPath,proFilePath,projectDir.absolutePath());

		QFile userFile(userFilePath);
		if(!userFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+userFilePath+"\"" ; qApp->exit(EXIT_FAILURE);}
		userFile.write(data.toUtf8()); userFile.close();
	}
	// <projectName>.pro
	{
		QString config = useBuild ? "-= debug_and_release" : "+= debug_and_release debug_and_release_target";
		QString form = useForm ? QString("\nFORMS += \\\n\t%1\n").arg(UIFileName) : "";
		QString files = isConsoleApp?"\n" : QString(" \\\n\t%1\n\nHEADERS += \\\n\t%2\n%3").arg(CFileName,HFileName,form);
		data = ProjectFile::PRO_FILE.arg(isConsoleApp?"-= gui" : "+= widgets",config, files);

		QFile proFile(proFilePath);
		if(!proFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+proFilePath+"\"" ; qApp->exit(EXIT_FAILURE);}
		proFile.write(data.toUtf8()); proFile.close();
	}
	// main.cpp
	{
		QString include = isConsoleApp ? "" : QString("#include \"%1\"\n\n").arg(HFileName);
		QString show = isConsoleApp ? "" :  QString("\t%1 w;\n\tw.show();\n").arg(className);
		data =  ProjectFile::MAIN_FILE.arg(include,isConsoleApp ? "Core" : "", show);

		QFile mainFile(srcDir.absolutePath()+QDir::separator()+"main.cpp");
		if(!mainFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+mainFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
		mainFile.write(data.toUtf8()); mainFile.close();
	}
	// End if is QT Console App

	if(isConsoleApp) return proFilePath;

	// <className>.h
	{
		data = ProjectFile::CLASS_H_FILE.arg(useForm?"\n\tprivate:\n\t\tUi::%5 *ui;\n":"",useForm?"namespace Ui {class %5;}\n\n":"").arg(className.toUpper(), baseClass, className);

		QFile HFile(srcDir.absolutePath()+QDir::separator()+HFileName);
		if(!HFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+HFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
		HFile.write(data.toUtf8()); HFile.close();
	}
	// <className>.cpp
	{
		QString incForm = useForm ? "#include \"ui_%3\"\n" : "";
		QString constr = useForm ? ", ui(new Ui::%4)\n{\n\tui->setupUi(this);" : "\n{\n";
		data = ProjectFile::CLASS_C_FILE.arg(incForm,constr).arg(HFileName,className,baseClass,useForm?"\tdelete ui;" : "");

		QFile CFile(srcDir.absolutePath()+QDir::separator()+CFileName);
		if(!CFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+CFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
		CFile.write(data.toUtf8()); CFile.close();
	}
	// <className>.ui
	{
		QString centWidget = baseClass==BaseClass::QMAINWINDOW ? ""
			"  <widget class=\"QWidget\" name=\"centralwidget\"/>\n"
			"  <widget class=\"QMenuBar\" name=\"menubar\"/>\n"
			"  <widget class=\"QStatusBar\" name=\"statusbar\"/>\n":"";
		data = ProjectFile::CLASS_UI_FILE.arg(className,baseClass,centWidget);

		QFile UIFile(srcDir.absolutePath()+QDir::separator()+UIFileName);
		if(!UIFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+UIFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
		UIFile.write(data.toUtf8()); UIFile.close();
	}

	return proFilePath;
}

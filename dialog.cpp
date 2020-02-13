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
	if(!versionsFile.open(QIODevice::ReadOnly)){qWarning()<<"Impossible d'ouvrir le fichier \"qtversion.xml\""; std::exit(EXIT_FAILURE);}
	QString VData = versionsFile.readAll();
	versionsFile.close();

	QRegularExpression rxv("Id\">(.+?).+?QMakePath\">.+?(\\d+\\.\\d+\\.\\d+).+?(Source\">(.+?)<.+)?Autodetected",QRegularExpression::DotMatchesEverythingOption);
	QRegularExpressionMatchIterator i = rxv.globalMatch(VData);
	while(i.hasNext()){
		QRegularExpressionMatch m = i.next();
		qtVersions.insert(!m.captured(4).isNull() ? m.captured(4) : m.captured(1), m.captured(2));}
	qDebug() << qtVersions;

	// Check QtKits //

	QHash<QString, QString> qtKits;
	QFile kitsFile(settings->value("qtSettingsPath").toString()+"/profiles.xml");
	if(!kitsFile.open(QIODevice::ReadOnly)){qWarning()<<"Impossible d'ouvrir le fichier \"profiles.xml\""; std::exit(EXIT_FAILURE);}
	QString KData = kitsFile.readAll();
	kitsFile.close();

	QRegularExpression rxk("QtInformation\">(.+?)<.+?Id\">(.+?)<.+?Name\">(.+?)<",QRegularExpression::DotMatchesEverythingOption);
	QRegularExpressionMatchIterator j = rxk.globalMatch(KData);
	while(j.hasNext()){
		QRegularExpressionMatch m = j.next();
		qtKits.insert(m.captured(3).replace("%{Qt:Version}",qtVersions.value(m.captured(1))),m.captured(2));}
	qDebug() << qtKits;

	// UI SETUP //

	ui->setupUi(this);
	setWindowTitle(qApp->applicationDisplayName());
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	ui->directoryLineEdit->setText(settings->value("defaultProjectPath").toString());
	ui->checkBox->setChecked(!ui->directoryLineEdit->text().isEmpty());

	for(QString k : qtKits.keys()) ui->projectKitCombo->addItem(k, qtKits.value(k));
	new ConsoleAppItem(ui->projectTypeCombo);
	new WidgetsAppItem(ui->projectTypeCombo);

	// CONNECTIONS

	QTimer* t = new QTimer(this);
	connect(t, &QTimer::timeout, [=]{
		ui->warningLabel->clear();
		ui->projectNameLineEdit->setStyleSheet("background-color: white;");
		ui->directoryLineEdit->setStyleSheet("background-color: white;");});


	connect(ui->browseButton, &QPushButton::clicked, [=]{
		ui->directoryLineEdit->setText(QFileDialog::getExistingDirectory(this,qApp->applicationDisplayName(),qApp->applicationDirPath()));});

	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, [=]{

		// Check user datas
		if(ui->projectNameLineEdit->text().isEmpty()) {
			ui->warningLabel->setText("Le nom du projet ne peut pas etre vide");
			ui->projectNameLineEdit->setStyleSheet("background-color: LightCoral;");
			t->start(2000);return;}
		if(ui->directoryLineEdit->text().isEmpty()) {
			ui->warningLabel->setText("L'emplacement du projet ne peut pas etre vide");
			ui->directoryLineEdit->setStyleSheet("background-color: LightCoral;");
			t->start(2000);return;}
		if(ui->projectNameLineEdit->text().contains(QRegExp("\\W+"))) {
			ui->warningLabel->setText("Le nom du projet est invalide");
			ui->projectNameLineEdit->setStyleSheet("background-color: LightCoral;");
			t->start(2000);return;}
		if(ui->directoryLineEdit->text().contains(QRegExp("[^\\w\\/\\\\:]+"))) {
			ui->warningLabel->setText("L'emplacement du projet est invalide");
			ui->directoryLineEdit->setStyleSheet("background-color: LightCoral;");
			t->start(2000);return;}

		QDir dir(ui->directoryLineEdit->text()+QDir::separator()+ui->projectNameLineEdit->text());
		if(dir.exists()) {
			ui->warningLabel->setText("Ce projet exist deja");
			ui->directoryLineEdit->setStyleSheet("background-color: LightCoral;");
			t->start(2000);return;}

		// Copy corresponding files
		qvariant_cast<Item*>(ui->projectTypeCombo->currentData())->createProject(dir);

		// Edit ".pro.user" file with QtKit selected
		QFile userFile(dir.absolutePath()+QDir::separator()+dir.dirName()+".pro.user");
		if(!userFile.open(QIODevice::ReadOnly)){qWarning()<<"Impossible d'ouvrir le fichier \""+userFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
		QString data = userFile.readAll(); userFile.close();

		data.replace("ProjectConfiguration.Id\"><","ProjectConfiguration.Id\">"+ui->projectKitCombo->currentData().toString()+"<");

		if(!userFile.open(QIODevice::WriteOnly|QIODevice::Truncate)){qWarning()<<"Impossible d'ouvrir le fichier \""+userFile.fileName()+"\"" ; qApp->exit(EXIT_FAILURE);}
		userFile.write(data.toUtf8()); userFile.close();

		// Open new project
		QDesktopServices::openUrl(QUrl("file:///"+dir.absolutePath()+QDir::separator()+dir.dirName()+".pro"));

		settings->setValue("defaultProjectPath", ui->checkBox->isChecked() ? ui->directoryLineEdit->text() : "");
		accept();});
}

Dialog::~Dialog(){delete ui;}

///////////////////////////////////////////////

Item::Item(QObject* parent) : QObject(parent){}

///////////////////////////////////////////////

ConsoleAppItem::ConsoleAppItem(QComboBox* box) : Item(box) {box->addItem("Qt Console Application", QVariant::fromValue(this));}

void ConsoleAppItem::createProject(const QDir& dir)
{
	dir.mkpath(dir.absolutePath());
	QFile::copy("files\\console-main",dir.absolutePath()+QDir::separator()+"main.cpp");
	QFile::copy("files\\console-pro",dir.absolutePath()+QDir::separator()+dir.dirName()+".pro");
	QFile::copy("files\\common-pro-user",dir.absolutePath()+QDir::separator()+dir.dirName()+".pro.user");
}

//////////////////////////////////////////////

WidgetsAppItem::WidgetsAppItem(QComboBox* box) : Item(box) {box->addItem("Qt Widgets Application", QVariant::fromValue(this));}

void WidgetsAppItem::createProject(const QDir& dir)
{
	dir.mkpath(dir.absolutePath());
	QFile::copy("files\\widgets-main",dir.absolutePath()+QDir::separator()+"main.cpp");
	QFile::copy("files\\widgets-mainwindow-h",dir.absolutePath()+QDir::separator()+"mainwindow.h");
	QFile::copy("files\\widgets-mainwindow-cpp",dir.absolutePath()+QDir::separator()+"mainwindow.cpp");
	QFile::copy("files\\widgets-pro",dir.absolutePath()+QDir::separator()+dir.dirName()+".pro");
	QFile::copy("files\\common-pro-user",dir.absolutePath()+QDir::separator()+dir.dirName()+".pro.user");
}

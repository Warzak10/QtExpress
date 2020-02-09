#include "dialog.h"
#include "ui_dialog.h"

#include <QStandardPaths>
#include <QSettings>
#include <QDebug>

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
	QByteArray VData = versionsFile.readAll();
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
	QByteArray KData = kitsFile.readAll();
	kitsFile.close();

	QRegularExpression rxk("QtInformation\">(.+?)<.+?Id\">(.+?)<.+?Name\">(.+?)<",QRegularExpression::DotMatchesEverythingOption);
	QRegularExpressionMatchIterator j = rxk.globalMatch(KData);
	while(j.hasNext()){
		QRegularExpressionMatch m = j.next();
		qtKits.insert(m.captured(3).replace("%{Qt:Version}",qtVersions.value(m.captured(1))),m.captured(2));}
	qDebug() << qtKits;

	// UI SETUP //

	ui->setupUi(this);
	for(QString k : qtKits.keys()) ui->projectKitCombo->addItem(k, qtKits.value(k));




	//std::exit(EXIT_FAILURE);
}

Dialog::~Dialog()
{
	delete ui;
}


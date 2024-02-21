#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace ProjectType{
	const QString QT_CONSOLE_APP = QStringLiteral("Qt Console Application");
	const QString QT_WIDGETS_APP = QStringLiteral("Qt Widgets Application");
}

namespace BaseClass{
	const QString QMAINWINDOW = QStringLiteral("QMainWindow");
	const QString QWIDGET = QStringLiteral("QWidget");
	const QString QDIALOG = QStringLiteral("QDialog");
}

namespace ProjectFile{
	const QString USER_FILE = QStringLiteral(
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<!DOCTYPE QtCreatorProject>\n"
"<qtcreator>\n"
" <data>\n"
"  <variable>ProjectExplorer.Project.Target.0</variable>\n"
"  <valuemap type=\"QVariantMap\">\n"
"   <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">%1</value>\n"
"   <value type=\"int\" key=\"ProjectExplorer.Target.ActiveBuildConfiguration\">1</value>\n"
"   <value type=\"int\" key=\"ProjectExplorer.Target.ActiveDeployConfiguration\">0</value>\n"
"   <value type=\"int\" key=\"ProjectExplorer.Target.ActiveRunConfiguration\">0</value>\n"
"   <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.Target.BuildConfiguration.0\">\n"
"    <value type=\"QString\" key=\"ProjectExplorer.BuildConfiguration.BuildDirectory\">%2</value>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.BuildConfiguration.BuildDirectory.shadowDir\">%2</value>\n"
"    <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildConfiguration.BuildStepList.0\">\n"
"     <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildStepList.Step.0\">\n"
"      <value type=\"bool\" key=\"ProjectExplorer.BuildStep.Enabled\">true</value>\n"
"      <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">QtProjectManager.QMakeBuildStep</value>\n"
"      <value type=\"QString\" key=\"QtProjectManager.QMakeBuildStep.QMakeArguments\"></value>\n"
"      <value type=\"bool\" key=\"QtProjectManager.QMakeBuildStep.QMakeForced\">false</value>\n"
"      <valuelist type=\"QVariantList\" key=\"QtProjectManager.QMakeBuildStep.SelectedAbis\"/>\n"
"     </valuemap>\n"
"     <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildStepList.Step.1\">\n"
"      <value type=\"bool\" key=\"ProjectExplorer.BuildStep.Enabled\">true</value>\n"
"      <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">Qt4ProjectManager.MakeStep</value>\n"
"     </valuemap>\n"
"     <value type=\"int\" key=\"ProjectExplorer.BuildStepList.StepsCount\">2</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DefaultDisplayName\">Build</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DisplayName\">Build</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">ProjectExplorer.BuildSteps.Build</value>\n"
"    </valuemap>\n"
"    <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildConfiguration.BuildStepList.1\">\n"
"     <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildStepList.Step.0\">\n"
"      <value type=\"bool\" key=\"ProjectExplorer.BuildStep.Enabled\">true</value>\n"
"      <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">Qt4ProjectManager.MakeStep</value>\n"
"      <value type=\"QString\" key=\"Qt4ProjectManager.MakeStep.MakeArguments\">clean</value>\n"
"     </valuemap>\n"
"     <value type=\"int\" key=\"ProjectExplorer.BuildStepList.StepsCount\">1</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DefaultDisplayName\">Clean</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DisplayName\">Clean</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">ProjectExplorer.BuildSteps.Clean</value>\n"
"    </valuemap>\n"
"    <value type=\"int\" key=\"ProjectExplorer.BuildConfiguration.BuildStepListCount\">2</value>\n"
"    <value type=\"bool\" key=\"ProjectExplorer.BuildConfiguration.ClearSystemEnvironment\">false</value>\n"
"    <valuelist type=\"QVariantList\" key=\"ProjectExplorer.BuildConfiguration.CustomParsers\"/>\n"
"    <valuelist type=\"QVariantList\" key=\"ProjectExplorer.BuildConfiguration.UserEnvironmentChanges\"/>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DisplayName\">Debug</value>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">Qt4ProjectManager.Qt4BuildConfiguration</value>\n"
"    <value type=\"int\" key=\"Qt4ProjectManager.Qt4BuildConfiguration.BuildConfiguration\">2</value>\n"
"   </valuemap>\n"
"   <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.Target.BuildConfiguration.1\">\n"
"    <value type=\"QString\" key=\"ProjectExplorer.BuildConfiguration.BuildDirectory\">%2</value>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.BuildConfiguration.BuildDirectory.shadowDir\">%2</value>\n"
"    <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildConfiguration.BuildStepList.0\">\n"
"     <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildStepList.Step.0\">\n"
"      <value type=\"bool\" key=\"ProjectExplorer.BuildStep.Enabled\">true</value>\n"
"      <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">QtProjectManager.QMakeBuildStep</value>\n"
"      <value type=\"QString\" key=\"QtProjectManager.QMakeBuildStep.QMakeArguments\"></value>\n"
"      <value type=\"bool\" key=\"QtProjectManager.QMakeBuildStep.QMakeForced\">false</value>\n"
"      <valuelist type=\"QVariantList\" key=\"QtProjectManager.QMakeBuildStep.SelectedAbis\"/>\n"
"     </valuemap>\n"
"     <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildStepList.Step.1\">\n"
"      <value type=\"bool\" key=\"ProjectExplorer.BuildStep.Enabled\">true</value>\n"
"      <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">Qt4ProjectManager.MakeStep</value>\n"
"     </valuemap>\n"
"     <value type=\"int\" key=\"ProjectExplorer.BuildStepList.StepsCount\">2</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DefaultDisplayName\">Build</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DisplayName\">Build</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">ProjectExplorer.BuildSteps.Build</value>\n"
"    </valuemap>\n"
"    <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildConfiguration.BuildStepList.1\">\n"
"     <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.BuildStepList.Step.0\">\n"
"      <value type=\"bool\" key=\"ProjectExplorer.BuildStep.Enabled\">true</value>\n"
"      <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">Qt4ProjectManager.MakeStep</value>\n"
"      <value type=\"QString\" key=\"Qt4ProjectManager.MakeStep.MakeArguments\">clean</value>\n"
"     </valuemap>\n"
"     <value type=\"int\" key=\"ProjectExplorer.BuildStepList.StepsCount\">1</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DefaultDisplayName\">Clean</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DisplayName\">Clean</value>\n"
"     <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">ProjectExplorer.BuildSteps.Clean</value>\n"
"    </valuemap>\n"
"    <value type=\"int\" key=\"ProjectExplorer.BuildConfiguration.BuildStepListCount\">2</value>\n"
"    <value type=\"bool\" key=\"ProjectExplorer.BuildConfiguration.ClearSystemEnvironment\">false</value>\n"
"    <valuelist type=\"QVariantList\" key=\"ProjectExplorer.BuildConfiguration.CustomParsers\"/>\n"
"    <valuelist type=\"QVariantList\" key=\"ProjectExplorer.BuildConfiguration.UserEnvironmentChanges\"/>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.DisplayName\">Release</value>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">Qt4ProjectManager.Qt4BuildConfiguration</value>\n"
"    <value type=\"int\" key=\"Qt4ProjectManager.Qt4BuildConfiguration.BuildConfiguration\">0</value>\n"
"   </valuemap>\n"
"   <value type=\"int\" key=\"ProjectExplorer.Target.BuildConfigurationCount\">2</value>\n"
"   <valuemap type=\"QVariantMap\" key=\"ProjectExplorer.Target.RunConfiguration.0\">\n"
"    <value type=\"int\" key=\"PE.EnvironmentAspect.Base\">2</value>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.ProjectConfiguration.Id\">Qt4ProjectManager.Qt4RunConfiguration:%3</value>\n"
"    <value type=\"QString\" key=\"ProjectExplorer.RunConfiguration.BuildKey\">%3</value>\n"
"    <value type=\"bool\" key=\"RunConfiguration.UseCppDebugger\">false</value>\n"
"    <value type=\"bool\" key=\"RunConfiguration.UseCppDebuggerAuto\">true</value>\n"
"    <value type=\"bool\" key=\"RunConfiguration.UseLibrarySearchPath\">true</value>\n"
"    <value type=\"bool\" key=\"RunConfiguration.UseQmlDebugger\">false</value>\n"
"    <value type=\"bool\" key=\"RunConfiguration.UseQmlDebuggerAuto\">true</value>\n"
"    <value type=\"QString\" key=\"RunConfiguration.WorkingDirectory\">%4</value>\n"
"   </valuemap>\n"
"   <value type=\"int\" key=\"ProjectExplorer.Target.RunConfigurationCount\">1</value>\n"
"  </valuemap>\n"
" </data>\n"
" <data>\n"
"  <variable>ProjectExplorer.Project.TargetCount</variable>\n"
"  <value type=\"int\">1</value>\n"
" </data>\n"
" <data>\n"
"  <variable>ProjectExplorer.Project.Updater.FileVersion</variable>\n"
"  <value type=\"int\">22</value>\n"
" </data>\n"
" <data>\n"
"  <variable>Version</variable>\n"
"  <value type=\"int\">22</value>\n"
" </data>\n"
"</qtcreator>"
);
	const QString PRO_FILE = QStringLiteral(
"QT %1\n\n"													//add or remove module
"CONFIG += c++17\n"
"CONFIG %2\n\n"
"DEFINES += QT_DEPRECATED_WARNINGS\n\n"
"SOURCES += \\\n\tmain.cpp%3"								//add more file if not console app
);
	const QString MAIN_FILE = QStringLiteral(
"%1"														//add "include header" if not console app
"#include <Q%2Application>\n\n"								//add Core if console app
"int main(int argc, char *argv[])\n{\n"
"\tQ%2Application a(argc, argv);\n"							//add Core if console app
"%3\treturn a.exec();\n}\n"									//add "show class" if not console app
);
	const QString CLASS_H_FILE = QStringLiteral(
"#ifndef %3_H\n"											//add class upper
"#define %3_H\n\n"											//add class upper
"#include <%4>\n\n"											//add baseclass
"%2"														//add "namespace" if form
"class %5 : public %4\n{\n\tQ_OBJECT\n\n\tpublic:\n"		//add class, baseclass
"\t\t%5(QWidget* parent = nullptr);\n\t\t~%5();\n"			//add class
"%1"														//add "private ui"
"};\n\n#endif // %3_H\n"									//add class upper
);
	const QString CLASS_C_FILE = QStringLiteral(
"#include \"%3\"\n"											//add header
"%1"														//add "include form"
"\n%4::%4(QWidget* parent) : %5(parent)"					//add class, baseclass
"%2"														//add constructor (ui or not)
"\n}\n\n%4::~%4()\n{\n%6\n}\n"								//add class, "delete ui"
);
	const QString CLASS_UI_FILE = QStringLiteral(
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<ui version=\"4.0\">\n"
" <class>%1</class>\n"
" <widget class=\"%2\" name=\"%1\">\n"						//add class, baseclass
"  <property name=\"geometry\">\n"
"   <rect>\n"
"    <x>0</x>\n"
"    <y>0</y>\n"
"    <width>800</width>\n"
"    <height>600</height>\n"
"   </rect>\n"
"  </property>\n"
"  <property name=\"windowTitle\">\n"
"   <string>%1</string>\n"									//add class
"  </property>\n"
"%3"														//add "central widget" if baseclass is QMainwindows
"  </widget>\n"
" <resources/>\n"
" <connections/>\n"
"</ui>\n"
);
}

namespace Ui {class Dialog;}

class Dialog : public QDialog
{
	Q_OBJECT

	public:
		Dialog(QWidget *parent = nullptr);
		~Dialog();

		void warn(QWidget* widget, const QString& text);
		QString createProject();

	private:
		Ui::Dialog *ui;
		QTimer* timer;
};

#endif // DIALOG_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDir>

class QComboBox;

namespace Ui { class Dialog; }

class Dialog : public QDialog
{
	Q_OBJECT

	public:
		Dialog(QWidget *parent = nullptr);
		~Dialog();

	private:
		Ui::Dialog *ui;
};

//////////////////////////////////////////////////////////

struct Item : public QObject
{
	Q_OBJECT

	Item(QObject* parent);
	virtual void createProject(const QDir& dir) = 0;
};

struct ConsoleAppItem : public Item
{
	ConsoleAppItem(QComboBox* box);
	virtual void createProject(const QDir& dir);
};

struct WidgetsAppItem : public Item
{
	WidgetsAppItem(QComboBox* box);
	virtual void createProject(const QDir& dir);
};
#endif // DIALOG_H

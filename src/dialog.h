#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>


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

#ifndef QT_TEST_H
#define QT_TEST_H

#include <QtWidgets/QWidget>
#include "ui_qt_test.h"

class QPushButton;
class QLineEdit;
class QMessageBox;
class QLabel;

class QT_test : public QWidget
{
	Q_OBJECT

public:
	QT_test(QWidget *parent = 0);
	~QT_test();

private slots:
	void buttonClicked();
	void quit();

private:
	QLabel *showOut;
	QPushButton *quitButton;
	QPushButton *inputButton;
	QLineEdit *inputLine;

};

#endif // QT_TEST_H

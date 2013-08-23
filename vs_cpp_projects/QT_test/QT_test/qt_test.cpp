#include <QtWidgets>
#include "qt_test.h"

QT_test::QT_test(QWidget *parent)
	: QWidget(parent)
{
	showOut = new QLabel;
	quitButton = new QPushButton;
	inputButton = new QPushButton;
	inputLine = new QLineEdit;

	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *headLayout = new QHBoxLayout;
	QHBoxLayout *showLayout = new QHBoxLayout;

	headLayout->addWidget(inputLine);
	headLayout->addWidget(inputButton);
	showLayout->addWidget(showOut);
	mainLayout->addLayout(headLayout);
	mainLayout->addLayout(showLayout);
	mainLayout->addWidget(quitButton);

	setLayout(mainLayout);

	connect(quitButton,SIGNAL(clicked()), this,SLOT(quit()));

}

QT_test::~QT_test()
{

}

void QT_test::quit(){
}

void QT_test::buttonClicked(){
}

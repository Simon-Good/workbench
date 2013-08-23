/********************************************************************************
** Form generated from reading UI file 'qt_test.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_TEST_H
#define UI_QT_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_testClass
{
public:

    void setupUi(QWidget *QT_testClass)
    {
        if (QT_testClass->objectName().isEmpty())
            QT_testClass->setObjectName(QStringLiteral("QT_testClass"));
        QT_testClass->resize(600, 400);

        retranslateUi(QT_testClass);

        QMetaObject::connectSlotsByName(QT_testClass);
    } // setupUi

    void retranslateUi(QWidget *QT_testClass)
    {
        QT_testClass->setWindowTitle(QApplication::translate("QT_testClass", "QT_test", 0));
    } // retranslateUi

};

namespace Ui {
    class QT_testClass: public Ui_QT_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H

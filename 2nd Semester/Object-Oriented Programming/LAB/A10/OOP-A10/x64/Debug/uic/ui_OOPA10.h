/********************************************************************************
** Form generated from reading UI file 'OOPA10.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OOPA10_H
#define UI_OOPA10_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OOPA10Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OOPA10Class)
    {
        if (OOPA10Class->objectName().isEmpty())
            OOPA10Class->setObjectName("OOPA10Class");
        OOPA10Class->resize(600, 400);
        menuBar = new QMenuBar(OOPA10Class);
        menuBar->setObjectName("menuBar");
        OOPA10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OOPA10Class);
        mainToolBar->setObjectName("mainToolBar");
        OOPA10Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(OOPA10Class);
        centralWidget->setObjectName("centralWidget");
        OOPA10Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OOPA10Class);
        statusBar->setObjectName("statusBar");
        OOPA10Class->setStatusBar(statusBar);

        retranslateUi(OOPA10Class);

        QMetaObject::connectSlotsByName(OOPA10Class);
    } // setupUi

    void retranslateUi(QMainWindow *OOPA10Class)
    {
        OOPA10Class->setWindowTitle(QCoreApplication::translate("OOPA10Class", "OOPA10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OOPA10Class: public Ui_OOPA10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OOPA10_H

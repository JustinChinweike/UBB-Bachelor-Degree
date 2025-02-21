/********************************************************************************
** Form generated from reading UI file 'PatientManagement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTMANAGEMENT_H
#define UI_PATIENTMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientManagementClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PatientManagementClass)
    {
        if (PatientManagementClass->objectName().isEmpty())
            PatientManagementClass->setObjectName("PatientManagementClass");
        PatientManagementClass->resize(600, 400);
        menuBar = new QMenuBar(PatientManagementClass);
        menuBar->setObjectName("menuBar");
        PatientManagementClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PatientManagementClass);
        mainToolBar->setObjectName("mainToolBar");
        PatientManagementClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PatientManagementClass);
        centralWidget->setObjectName("centralWidget");
        PatientManagementClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PatientManagementClass);
        statusBar->setObjectName("statusBar");
        PatientManagementClass->setStatusBar(statusBar);

        retranslateUi(PatientManagementClass);

        QMetaObject::connectSlotsByName(PatientManagementClass);
    } // setupUi

    void retranslateUi(QMainWindow *PatientManagementClass)
    {
        PatientManagementClass->setWindowTitle(QCoreApplication::translate("PatientManagementClass", "PatientManagement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientManagementClass: public Ui_PatientManagementClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTMANAGEMENT_H

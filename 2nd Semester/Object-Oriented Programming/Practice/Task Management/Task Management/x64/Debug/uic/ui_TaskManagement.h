/********************************************************************************
** Form generated from reading UI file 'TaskManagement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMANAGEMENT_H
#define UI_TASKMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskManagementClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TaskManagementClass)
    {
        if (TaskManagementClass->objectName().isEmpty())
            TaskManagementClass->setObjectName("TaskManagementClass");
        TaskManagementClass->resize(600, 400);
        menuBar = new QMenuBar(TaskManagementClass);
        menuBar->setObjectName("menuBar");
        TaskManagementClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TaskManagementClass);
        mainToolBar->setObjectName("mainToolBar");
        TaskManagementClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TaskManagementClass);
        centralWidget->setObjectName("centralWidget");
        TaskManagementClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TaskManagementClass);
        statusBar->setObjectName("statusBar");
        TaskManagementClass->setStatusBar(statusBar);

        retranslateUi(TaskManagementClass);

        QMetaObject::connectSlotsByName(TaskManagementClass);
    } // setupUi

    void retranslateUi(QMainWindow *TaskManagementClass)
    {
        TaskManagementClass->setWindowTitle(QCoreApplication::translate("TaskManagementClass", "TaskManagement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskManagementClass: public Ui_TaskManagementClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKMANAGEMENT_H

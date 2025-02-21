#ifndef PROGRAMMERWINDOW_H
#define PROGRAMMERWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include "TaskController.h"

class ProgrammerWindow : public QMainWindow {
    Q_OBJECT

public:
    ProgrammerWindow(TaskController& controller, const Programmer& programmer, QWidget* parent = nullptr);

private slots:
    void addTask();
    void removeTask();
    void startTask();
    void doneTask();
    void populateTaskList();

private:
    TaskController& controller;
    Programmer programmer;
    QListWidget* taskListWidget;

    QString statusToString(TaskStatus status);
};

#endif // PROGRAMMERWINDOW_H

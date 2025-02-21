
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "DataManager.h"
#include "DoctorWindow.h"
#include "StatisticsWindow.h"

class MainWindow : public QMainWindow, public Subject {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    std::vector<Doctor> doctors;
    std::vector<Patient> patients;
    std::vector<DoctorWindow*> doctorWindows;
    StatisticsWindow* statisticsWindow;

    void loadDoctorWindows();
    void loadStatisticsWindow();
};

#endif // MAINWINDOW_H

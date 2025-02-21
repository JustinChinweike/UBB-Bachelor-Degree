#include "MainWindow.h"



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    doctors = DataManager::loadDoctors("doctors.txt");
    patients = DataManager::loadPatients("patients.txt");

    loadDoctorWindows();
    loadStatisticsWindow();
}

MainWindow::~MainWindow() {
    DataManager::savePatients("patients.txt", patients);
}

void MainWindow::loadDoctorWindows() {
    for (const auto& doctor : doctors) {
        DoctorWindow* window = new DoctorWindow(doctor, patients);
        doctorWindows.push_back(window);
        addObserver(window);
        window->show();
    }
}

void MainWindow::loadStatisticsWindow() {
    statisticsWindow = new StatisticsWindow(patients);
    addObserver(statisticsWindow);
    statisticsWindow->show();
}

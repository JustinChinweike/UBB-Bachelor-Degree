#include <QApplication>
#include <vector>
#include "DataManager.h"
#include "DoctorWindow.h"
#include "StatisticsWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Load doctors and patients from files
    std::vector<Doctor> doctors = DataManager::loadDoctors("doctors.txt");
    std::vector<Patient> patients = DataManager::loadPatients("patients.txt");

    // Create the observer pattern relationships
    std::vector<DoctorWindow*> doctorWindows;
    for (const auto& doctor : doctors) {
        DoctorWindow* doctorWindow = new DoctorWindow(doctor, patients);
        doctorWindows.push_back(doctorWindow);
    }

    // Make each doctor window observe each other
    for (auto doctorWindow : doctorWindows) {
        for (auto otherDoctorWindow : doctorWindows) {
            if (doctorWindow != otherDoctorWindow) {
                doctorWindow->addObserver(otherDoctorWindow);
            }
        }
    }

    // Create and show the statistics window
    StatisticsWindow statsWindow(patients);
    for (auto doctorWindow : doctorWindows) {
        doctorWindow->addObserver(&statsWindow);
    }
    statsWindow.show();

    // Show all doctor windows
    for (auto doctorWindow : doctorWindows) {
        doctorWindow->show();
    }

    // Run the application
    int result = app.exec();

    // Save the patients back to the file upon exit
    DataManager::savePatients("patients.txt", patients);

    // Clean up
    for (auto doctorWindow : doctorWindows) {
        delete doctorWindow;
    }

    return result;
}

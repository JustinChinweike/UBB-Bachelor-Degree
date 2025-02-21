#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <QDate>

std::vector<Doctor> DataManager::loadDoctors(const std::string& filename) {
    std::vector<Doctor> doctors;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, specialization;
        std::getline(iss, name, ',');
        std::getline(iss, specialization, ',');

        doctors.emplace_back(QString::fromStdString(name), QString::fromStdString(specialization));
    }

    return doctors;
}

std::vector<Patient> DataManager::loadPatients(const std::string& filename) {
    std::vector<Patient> patients;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, diagnosis, specializationNeeded, currentDoctor, dateStr;
        std::getline(iss, name, ',');
        std::getline(iss, diagnosis, ',');
        std::getline(iss, specializationNeeded, ',');
        std::getline(iss, currentDoctor, ',');
        std::getline(iss, dateStr, ',');

        QDate admissionDate = QDate::fromString(QString::fromStdString(dateStr), "yyyy-MM-dd");
        patients.emplace_back(
            QString::fromStdString(name),
            QString::fromStdString(diagnosis),
            QString::fromStdString(specializationNeeded),
            QString::fromStdString(currentDoctor),
            admissionDate
        );
    }

    return patients;
}

void DataManager::savePatients(const std::string& filename, const std::vector<Patient>& patients) {
    std::ofstream file(filename);

    for (const auto& patient : patients) {
        file << patient.name.toStdString() << ","
            << patient.diagnosis.toStdString() << ","
            << patient.specializationNeeded.toStdString() << ","
            << patient.currentDoctor.toStdString() << ","
            << patient.admissionDate.toString("yyyy-MM-dd").toStdString() << "\n";
    }
}

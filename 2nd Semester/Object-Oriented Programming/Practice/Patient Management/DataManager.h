#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>
#include "Doctor.h"
#include "Patient.h"

class DataManager {
public:
    static std::vector<Doctor> loadDoctors(const std::string& filename);
    static std::vector<Patient> loadPatients(const std::string& filename);
    static void savePatients(const std::string& filename, const std::vector<Patient>& patients);
};

#endif // DATAMANAGER_H

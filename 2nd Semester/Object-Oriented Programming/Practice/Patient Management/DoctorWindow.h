#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QListWidget>
#include "Doctor.h"
#include "Patient.h"
#include "Observer.h"

class DoctorWindow : public QWidget, public Observer, public Subject {
    Q_OBJECT

public:
    DoctorWindow(const Doctor& doctor, std::vector<Patient>& patients, QWidget* parent = nullptr);
    void update() override;

private slots:
    void onCheckboxToggled(bool checked);
    void onAddPatient();
    void onUpdatePatient();

private:
    Doctor doctor;
    std::vector<Patient>& allPatients;
    QListWidget* patientListWidget;
    QCheckBox* filterCheckBox;
    QVBoxLayout* layout;

    void updatePatientList();
    void addPatientDialog();
    void updatePatientDialog();
};

#endif // DOCTORWINDOW_H

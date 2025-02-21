

#include "DoctorWindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDate>
#include <QPushButton>

DoctorWindow::DoctorWindow(const Doctor& doctor, std::vector<Patient>& patients, QWidget* parent)
    : QWidget(parent), doctor(doctor), allPatients(patients) {
    setWindowTitle(doctor.name);

    layout = new QVBoxLayout(this);
    filterCheckBox = new QCheckBox("Show only my patients", this);
    connect(filterCheckBox, &QCheckBox::toggled, this, &DoctorWindow::onCheckboxToggled);
    layout->addWidget(filterCheckBox);

    patientListWidget = new QListWidget(this);
    layout->addWidget(patientListWidget);

    QPushButton* addButton = new QPushButton("Add Patient", this);
    connect(addButton, &QPushButton::clicked, this, &DoctorWindow::onAddPatient);
    layout->addWidget(addButton);

    QPushButton* updateButton = new QPushButton("Update Patient", this);
    connect(updateButton, &QPushButton::clicked, this, &DoctorWindow::onUpdatePatient);
    layout->addWidget(updateButton);

    updatePatientList();
}

void DoctorWindow::onCheckboxToggled(bool checked) {
    updatePatientList();
}

void DoctorWindow::updatePatientList() {
    patientListWidget->clear();
    for (const auto& patient : allPatients) {
        if (patient.specializationNeeded == doctor.specialization || patient.diagnosis == "Undiagnosed") {
            if (!filterCheckBox->isChecked() || patient.currentDoctor == doctor.name) {
                QListWidgetItem* item = new QListWidgetItem(patient.name, patientListWidget);
                if (patient.currentDoctor == doctor.name) {
                    item->setBackground(Qt::green);
                }
            }
        }
    }
}

void DoctorWindow::update() {
    updatePatientList();
}

void DoctorWindow::onAddPatient() {
    addPatientDialog();
}

void DoctorWindow::onUpdatePatient() {
    updatePatientDialog();
}

void DoctorWindow::addPatientDialog() {
    QString name = QInputDialog::getText(this, "Add Patient", "Name:");
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Patient name cannot be empty");
        return;
    }

    QString diagnosis = QInputDialog::getText(this, "Add Patient", "Diagnosis:", QLineEdit::Normal, "Undiagnosed");
    QString specializationNeeded = QInputDialog::getText(this, "Add Patient", "Specialization Needed:");
    QString currentDoctor = QInputDialog::getText(this, "Add Patient", "Current Doctor:");
    QDate admissionDate = QDate::fromString(QInputDialog::getText(this, "Add Patient", "Admission Date (yyyy-MM-dd):"), "yyyy-MM-dd");

    if (!admissionDate.isValid() || admissionDate > QDate::currentDate()) {
        QMessageBox::warning(this, "Error", "Invalid admission date");
        return;
    }

    allPatients.emplace_back(name, diagnosis, specializationNeeded, currentDoctor, admissionDate);
    notify();
}

void DoctorWindow::updatePatientDialog() {
    QListWidgetItem* selectedItem = patientListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No patient selected");
        return;
    }

    QString name = selectedItem->text();
    auto it = std::find_if(allPatients.begin(), allPatients.end(), [&name](const Patient& patient) {
        return patient.name == name;
        });

    if (it == allPatients.end()) return;

    if (it->currentDoctor != doctor.name && it->diagnosis != "Undiagnosed") {
        QMessageBox::warning(this, "Error", "Cannot update this patient");
        return;
    }

    QString diagnosis = QInputDialog::getText(this, "Update Patient", "Diagnosis:", QLineEdit::Normal, it->diagnosis);
    QString specializationNeeded = QInputDialog::getText(this, "Update Patient", "Specialization Needed:", QLineEdit::Normal, it->specializationNeeded);
    QString dateStr = QInputDialog::getText(this, "Update Patient", "Admission Date (yyyy-MM-dd):", QLineEdit::Normal, it->admissionDate.toString("yyyy-MM-dd"));
    QDate admissionDate = QDate::fromString(dateStr, "yyyy-MM-dd");

    if (diagnosis.isEmpty() || diagnosis == "Undiagnosed") {
        QMessageBox::warning(this, "Error", "Invalid diagnosis");
        return;
    }

    if (!admissionDate.isValid() || admissionDate > QDate::currentDate()) {
        QMessageBox::warning(this, "Error", "Invalid admission date");
        return;
    }

    it->diagnosis = diagnosis;
    it->specializationNeeded = specializationNeeded;
    it->admissionDate = admissionDate;

    if (specializationNeeded != doctor.specialization) {
        it->currentDoctor = "";
    }
    else {
        it->currentDoctor = doctor.name;
    }

    updatePatientList();
    notify();
}

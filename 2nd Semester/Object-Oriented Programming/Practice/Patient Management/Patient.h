#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>

class Patient {
public:
    QString name;
    QString diagnosis;
    QString specializationNeeded;
    QString currentDoctor;
    QDate admissionDate;

    Patient(const QString& name, const QString& diagnosis, const QString& specializationNeeded, const QString& currentDoctor, const QDate& admissionDate)
        : name(name), diagnosis(diagnosis), specializationNeeded(specializationNeeded), currentDoctor(currentDoctor), admissionDate(admissionDate) {}
};

#endif // PATIENT_H

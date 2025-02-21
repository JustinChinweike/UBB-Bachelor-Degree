#ifndef DOCTOR_H
#define DOCTOR_H

#include <QString>

class Doctor {
public:
    QString name;
    QString specialization;

    Doctor(const QString& name, const QString& specialization)
        : name(name), specialization(specialization) {}
};

#endif // DOCTOR_H

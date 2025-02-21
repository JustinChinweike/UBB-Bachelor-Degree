#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>
#include <vector>
#include "Patient.h"
#include "Observer.h"

class StatisticsWindow : public QWidget, public Observer {
    Q_OBJECT

public:
    StatisticsWindow(const std::vector<Patient>& patients, QWidget* parent = nullptr);
    void update() override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    const std::vector<Patient>& patients;
    std::map<QString, int> specializationCount;

    void calculateStatistics();
};

#endif // STATISTICSWINDOW_H

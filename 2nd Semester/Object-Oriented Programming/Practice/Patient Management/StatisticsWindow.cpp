#include "StatisticsWindow.h"
#include <QPainter>
#include <QMap>

StatisticsWindow::StatisticsWindow(const std::vector<Patient>& patients, QWidget* parent)
    : QWidget(parent), patients(patients) {
    calculateStatistics();
    setWindowTitle("Statistics");
    resize(400, 300);
}

void StatisticsWindow::update() {
    calculateStatistics();
    repaint();
}

void StatisticsWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    int totalPatients = 0;
    for (const auto& entry : specializationCount) {
        totalPatients += entry.second;
    }

    if (totalPatients == 0) return;

    int startAngle = 0;
    for (const auto& entry : specializationCount) {
        int spanAngle = (entry.second * 360) / totalPatients;
        painter.drawPie(10, 10, 200, 200, startAngle * 16, spanAngle * 16);
        startAngle += spanAngle;
    }
}

void StatisticsWindow::calculateStatistics() {
    specializationCount.clear();
    for (const auto& patient : patients) {
        specializationCount[patient.specializationNeeded]++;
    }
}

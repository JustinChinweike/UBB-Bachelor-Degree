#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OOPA10.h"

class OOPA10 : public QMainWindow
{
    Q_OBJECT

public:
    OOPA10(QWidget *parent = nullptr);
    ~OOPA10();

private:
    Ui::OOPA10Class ui;
};

// TrenchCoatGUI.cpp
#include "TrenchCoatGUI.h"
#include <Controller.h>
#include <QVBoxLayout>
#include <QShortcut>
#include <QInputDialog>
#include <QInputDialog>
#include <QMessageBox> 





TrenchCoatGUI::TrenchCoatGUI(Controller & controller, QWidget * parent)
    : QWidget(parent), controller(controller) {
    setupUI();
    connectSignalsSlots();
}

TrenchCoatGUI::~TrenchCoatGUI() {
    delete model;
    delete tableView;
    delete addButton;
    delete removeButton;
    delete updateButton;
    delete undoButton;
    delete redoButton;
}


void TrenchCoatGUI::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    model = new TrenchCoatTableModel(this);
    model->setTrenchCoats(controller.getAllTrenchCoats());


    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this, SLOT(handleUndo()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this, SLOT(handleRedo()));

    tableView = new QTableView(this);
    tableView->setModel(model);


    addButton = new QPushButton("Add", this);
    removeButton = new QPushButton("Remove", this);
    updateButton = new QPushButton("Update", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);
    writeToDatabaseButton = new QPushButton("Write to database", this);


    layout->addWidget(tableView);
    layout->addWidget(addButton);
    layout->addWidget(removeButton); 
    layout->addWidget(updateButton);
    layout->addWidget(undoButton);
    layout->addWidget(redoButton);
    layout->addWidget(writeToDatabaseButton);

    setLayout(layout);
}

void TrenchCoatGUI::connectSignalsSlots() {
    connect(addButton, &QPushButton::clicked, this, &TrenchCoatGUI::handleAdd);
    connect(removeButton, &QPushButton::clicked, this, &TrenchCoatGUI::handleRemove);
    connect(updateButton, &QPushButton::clicked, this, &TrenchCoatGUI::handleUpdate);
    connect(undoButton, &QPushButton::clicked, this, &TrenchCoatGUI::handleUndo);
    connect(redoButton, &QPushButton::clicked, this, &TrenchCoatGUI::handleRedo);
    connect(writeToDatabaseButton, &QPushButton::clicked, this, &TrenchCoatGUI::handlewriteToDatabase);
    
}




void TrenchCoatGUI::handleUndo() {
    controller.undo();
    model->setTrenchCoats(controller.getAllTrenchCoats());
}

void TrenchCoatGUI::handleRedo() {
    controller.redo();
    model->setTrenchCoats(controller.getAllTrenchCoats());
}


void TrenchCoatGUI::handleAdd() {
    bool ok;

    int trenchID = QInputDialog::getInt(this, tr("Add Trench Coat"),
        tr("Trench ID:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    int trenchSize = QInputDialog::getInt(this, tr("Add Trench Coat"),
        tr("Trench Size:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    QString trenchColour = QInputDialog::getText(this, tr("Add Trench Coat"),
        tr("Trench Colour:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || trenchColour.isEmpty())
        return;

    float trenchPrice = QInputDialog::getDouble(this, tr("Add Trench Coat"),
        tr("Trench Price:"), 0, 0, 10000, 2, &ok);
    if (!ok)
        return;

    int trenchQuantity = QInputDialog::getInt(this, tr("Add Trench Coat"),
        tr("Trench Quantity:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    QString trenchPhotograph = QInputDialog::getText(this, tr("Add Trench Coat"),
        tr("Trench Photograph:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || trenchPhotograph.isEmpty())
        return;

    controller.addTrenchCoat(trenchID, trenchSize, 
        trenchColour.toStdString(), trenchPrice, 
        trenchQuantity, trenchPhotograph.toStdString());

    controller.saveProgress();  // Save changes to the file
    model->setTrenchCoats(controller.getAllTrenchCoats());
}



void TrenchCoatGUI::handleRemove() {
    bool ok;

    int trenchID = QInputDialog::getInt(this, tr("Remove Trench Coat"),
        tr("Trench ID:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    controller.removeTrenchCoat(trenchID);
    model->setTrenchCoats(controller.getAllTrenchCoats());
}




void TrenchCoatGUI::handleUpdate() {
    bool ok;

    int trenchID = QInputDialog::getInt(this, tr("Update Trench Coat"),
        tr("Trench ID:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    int newTrenchID = QInputDialog::getInt(this, tr("Update Trench Coat"),
        tr("New Trench ID:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    int newTrenchSize = QInputDialog::getInt(this, tr("Update Trench Coat"),
        tr("New Trench Size:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    QString newTrenchColour = QInputDialog::getText(this, tr("Update Trench Coat"),
        tr("New Trench Colour:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || newTrenchColour.isEmpty())
        return;

    float newTrenchPrice = QInputDialog::getDouble(this, tr("Update Trench Coat"),
        tr("New Trench Price:"), 0, 0, 10000, 2, &ok);
    if (!ok)
        return;

    int newTrenchQuantity = QInputDialog::getInt(this, tr("Update Trench Coat"),
        tr("New Trench Quantity:"), 0, 0, 10000, 1, &ok);
    if (!ok)
        return;

    QString newTrenchPhotograph = QInputDialog::getText(this, tr("Update Trench Coat"),
        tr("New Trench Photograph:"), QLineEdit::Normal,
        "", &ok);
    if (!ok || newTrenchPhotograph.isEmpty())
        return;

    controller.updateTrenchCoat(trenchID, newTrenchID, newTrenchSize, newTrenchColour.toStdString(), 
        newTrenchPrice, newTrenchQuantity, newTrenchPhotograph.toStdString());
    model->setTrenchCoats(controller.getAllTrenchCoats());
}




void TrenchCoatGUI::handlewriteToDatabase() {
    try {
        controller.saveProgress();

        // Show a message box to confirm that the data was written successfully
        QMessageBox::information(this, "Success", "Data written to database successfully.");
    }
    catch (const std::exception& e) {
        // Handle the error
        // For example, you could show a message box with the error message:
        QMessageBox::warning(this, "Error", e.what());
    }
}




#include "AdminWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

AdminWindow::AdminWindow(Controller& controller, QWidget* parent)
    : QWidget(parent), controller(controller) {
    setupUI();
    populateTable();
}

void AdminWindow::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    table = new QTableWidget(this);
    table->setColumnCount(6);
    QStringList headers;
    headers << "ID" << "Size" << "Color" << "Price" << "Quantity" << "Photo URL";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(table);

    QHBoxLayout* formLayout = new QHBoxLayout();

    idInput = new QLineEdit(this);
    sizeInput = new QLineEdit(this);
    colorInput = new QLineEdit(this);
    priceInput = new QLineEdit(this);
    quantityInput = new QLineEdit(this);
    photoInput = new QLineEdit(this);




    formLayout->addWidget(new QLabel("ID:", this));
    formLayout->addWidget(idInput);
    formLayout->addWidget(new QLabel("Size:", this));
    formLayout->addWidget(sizeInput);
    formLayout->addWidget(new QLabel("Color:", this));
    formLayout->addWidget(colorInput);
    formLayout->addWidget(new QLabel("Price:", this));
    formLayout->addWidget(priceInput);
    formLayout->addWidget(new QLabel("Quantity:", this));
    formLayout->addWidget(quantityInput);
    formLayout->addWidget(new QLabel("Photo URL:", this));
    formLayout->addWidget(photoInput);
    

    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton* addButton = new QPushButton("Add", this);
    QPushButton* removeButton = new QPushButton("Remove", this);
    QPushButton* updateButton = new QPushButton("Update", this);
	QPushButton* writeToDatabaseButton = new QPushButton("Write to database", this);
    QPushButton* readfromDatabase = new QPushButton("Read from Database", this);
    QPushButton* backButton = new QPushButton("Back", this);


    connect(addButton, &QPushButton::clicked, this, &AdminWindow::addTrenchCoat);
    connect(removeButton, &QPushButton::clicked, this, &AdminWindow::removeTrenchCoat);
    connect(updateButton, &QPushButton::clicked, this, &AdminWindow::updateTrenchCoat);
    connect(writeToDatabaseButton, &QPushButton::clicked, this, &AdminWindow::writeToDatabase);
	connect(readfromDatabase, &QPushButton::clicked, this, &AdminWindow::readfromDatabase);
	connect(backButton, &QPushButton::clicked, this, &AdminWindow::close);
    connect(backButton, &QPushButton::clicked, this, &AdminWindow::backButtonClicked);


    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(updateButton);
	buttonsLayout->addWidget(writeToDatabaseButton);
	buttonsLayout->addWidget(readfromDatabase);
	buttonsLayout->addWidget(backButton);

    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void AdminWindow::populateTable() {
    table->clearContents();
    const std::vector<TrenchCoat>& coats = controller.getAllTrenchCoats();
    table->setRowCount(coats.size());

    for (size_t i = 0; i < coats.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(QString::number(coats[i].getTrenchID())));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(coats[i].getTrenchSize())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(coats[i].getTrenchColour())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(coats[i].getTrenchPrice())));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(coats[i].getTrenchQuantity())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(coats[i].getTrenchPhotographyLink())));
    }
}

void AdminWindow::addTrenchCoat() {
    int id = idInput->text().toInt();
    int size = sizeInput->text().toInt();
    std::string color = colorInput->text().toStdString();
    float price = priceInput->text().toFloat();
    int quantity = quantityInput->text().toInt();
    std::string photo = photoInput->text().toStdString();

    controller.addTrenchCoat(id, size, color, price, quantity, photo);
    populateTable();
}

void AdminWindow::removeTrenchCoat() {
    int id = idInput->text().toInt();
    controller.removeTrenchCoat(id);
    populateTable();
}

void AdminWindow::updateTrenchCoat() {
    int id = idInput->text().toInt();
    int newId = idInput->text().toInt();  // Assuming we want to update with the same ID for simplicity
    int size = sizeInput->text().toInt();
    std::string color = colorInput->text().toStdString();
    float price = priceInput->text().toFloat();
    int quantity = quantityInput->text().toInt();
    std::string photo = photoInput->text().toStdString();

    controller.updateTrenchCoat(id, newId, size, color, price, quantity, photo);
    populateTable();
}

void AdminWindow::writeToDatabase() {
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



void AdminWindow::readfromDatabase() {
	try {
		controller.loadFromFile();
		populateTable();
		// Show a message box to confirm that the data was read successfully
		QMessageBox::information(this, "Success", "Data read from database successfully.");
	}
	catch (const std::exception& e) {
		// Handle the error
		// For example, you could show a message box with the error message:
		QMessageBox::warning(this, "Error", e.what());
	}
}
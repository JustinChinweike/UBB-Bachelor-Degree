#include "UserWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileInfo>
#include <FileStorage.h>

#include <QDesktopServices>


UserWindow::UserWindow(Controller& controller, QWidget* parent)
    : QWidget(parent), controller(controller), currentIndex(0), totalCost(0) {
    setupUI();
    //populateTable();
    if (!controller.getAllTrenchCoats().empty()) {
        showTrenchCoatDetails(currentIndex);
    }
}

void UserWindow::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    table = new QTableWidget(this);
    table->setColumnCount(6);
    QStringList headers;
    headers << "ID" << "Size" << "Color" << "Price" << "Quantity" << "Photo URL";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(table);

    trenchDetails = new QLabel(this);
    mainLayout->addWidget(trenchDetails);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton* nextButton = new QPushButton("Next", this);
	QPushButton* cycleButton = new QPushButton("Cycle", this);
    QPushButton* addToBasketButton = new QPushButton("Add to Basket", this);
	QPushButton* removeButton = new QPushButton("Remove from Basket", this);
	QPushButton* printBasketButton = new QPushButton("Print Basket", this);
	QPushButton* emptyBasketButton = new QPushButton("Empty Basket", this);
	QPushButton* displayBasketButton = new QPushButton("Display Basket", this);
	QPushButton* saveBasketButton = new QPushButton("Save Basket", this);
	QPushButton* backButton = new QPushButton("Back", this);


    connect(nextButton, &QPushButton::clicked, this, &UserWindow::nextTrenchCoat);
	 
    connect(cycleButton, &QPushButton::clicked, this, &UserWindow::cycleThroughTrenchCoats);
    connect(addToBasketButton, &QPushButton::clicked, this, &UserWindow::addTrenchCoatToShoppingBasket);
	connect(removeButton, &QPushButton::clicked, this, &UserWindow::removeTrenchCoatFromShoppingBasket);
	connect(printBasketButton, &QPushButton::clicked, this, &UserWindow::printShoppingBasket);
	connect(emptyBasketButton, &QPushButton::clicked, this, &UserWindow::emptyBasketOfTrenchCoats);
	connect(displayBasketButton, &QPushButton::clicked, this, &UserWindow::displayShoppingBasket);
	connect(saveBasketButton, &QPushButton::clicked, this, &UserWindow::saveShoppingBasketToFile);

    connect(backButton, &QPushButton::clicked, this, &UserWindow::close);
    connect(backButton, &QPushButton::clicked, this, &UserWindow::backButtonClicked);


    buttonsLayout->addWidget(nextButton);
	buttonsLayout->addWidget(cycleButton);
	buttonsLayout->addWidget(addToBasketButton);
	buttonsLayout->addWidget(removeButton);
	buttonsLayout->addWidget(printBasketButton);
	buttonsLayout->addWidget(emptyBasketButton);
	buttonsLayout->addWidget(displayBasketButton);
	buttonsLayout->addWidget(saveBasketButton);
	buttonsLayout->addWidget(backButton);

    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);




    
}


void UserWindow::populateTable() {
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

void UserWindow::showTrenchCoatDetails(int index) {
    const std::vector<TrenchCoat>& coats = controller.getAllTrenchCoats();
    if (index < 0 || index >= coats.size()) return;

    const TrenchCoat& coat = coats[index];
    QString details = QString("ID: %1\nSize: %2\nColor: %3\nPrice: %4\nQuantity: %5\nPhoto URL: %6")
        .arg(coat.getTrenchID())
        .arg(coat.getTrenchSize())
        .arg(QString::fromStdString(coat.getTrenchColour()))
        .arg(coat.getTrenchPrice())
        .arg(coat.getTrenchQuantity())
        .arg(QString::fromStdString(coat.getTrenchPhotographyLink()));

    trenchDetails->setText(details);
}



void UserWindow::nextTrenchCoat() {
    currentIndex = (currentIndex + 1) % controller.getAllTrenchCoats().size();
    showTrenchCoatDetails(currentIndex);
}



void UserWindow::updateTrenchCoatDetails() {
    const TrenchCoat& coat = trenchCoats[currentIndex];
    QString details = QString("ID: %1\nSize: %2\nColor: %3\nPrice: %4\nQuantity: %5\nPhoto URL: %6")
        .arg(coat.getTrenchID())
        .arg(coat.getTrenchSize())
        .arg(QString::fromStdString(coat.getTrenchColour()))
        .arg(coat.getTrenchPrice())
        .arg(coat.getTrenchQuantity())
        .arg(QString::fromStdString(coat.getTrenchPhotographyLink()));

    trenchDetails->setText(details);
}




void UserWindow::cycleThroughTrenchCoats() {
    bool ok;
    int sizeToFilterBy = QInputDialog::getInt(this, tr("Cycle Through Trench Coats"),
        tr("Enter the size of the trench coats you want to see, or press 0 to see all trench coats:"), 0, 0, 100, 1, &ok);
    if (!ok) {
        // The user canceled the dialog
        return;
    }

    if (sizeToFilterBy != 0) {
        trenchCoats = controller.filterBySize(sizeToFilterBy);
    }
    else {
        trenchCoats = controller.getAllTrenchCoats();
    }

    if (trenchCoats.empty()) {
        QMessageBox::information(this, "Information", "There are no trench coats with that size!");
        return;
    }

    currentIndex = 0;
    totalCost = 0;
    updateTrenchCoatDetails();
}
 


void UserWindow::addTrenchCoatToShoppingBasket() {
    if (trenchCoats.empty()) {
        QMessageBox::information(this, "Information", "No trench coat is currently displayed!");
        return;
    }

    try {
        // Add the trench coat to the shopping basket
        controller.addTrenchCoatToShoppingBasket(trenchCoats[currentIndex].getTrenchID());

        // Update the total cost
        totalCost += trenchCoats[currentIndex].getTrenchPrice();

        

        // Show a success message
        QMessageBox::information(this, "Success", "Trench coat added to basket successfully. Total cost: " + QString::number(totalCost));
    }
    catch (const std::exception& e) {
        // Handle the error
        QMessageBox::warning(this, "Error", e.what());
    }
}





void UserWindow::removeTrenchCoatFromShoppingBasket() {
    // Implement the functionality...
}




void UserWindow::printShoppingBasket() {
    std::vector<TrenchCoat> shoppingBasket = controller.getShoppingBasketTrenchCoats();
    if (shoppingBasket.empty()) {
        QMessageBox::information(this, "Shopping Basket", "The shopping basket is empty.");
        return;
    }

    QString message = "Shopping Basket:\n\n";
    for (const TrenchCoat& coat : shoppingBasket) {
        message += QString("ID: %1, Size: %2, Color: %3, Price: %4, Quantity: %5, Photo URL: %6\n")
            .arg(coat.getTrenchID())
            .arg(coat.getTrenchSize())
            .arg(QString::fromStdString(coat.getTrenchColour()))
            .arg(coat.getTrenchPrice())
            .arg(coat.getTrenchQuantity())
            .arg(QString::fromStdString(coat.getTrenchPhotographyLink()));
    }

    QMessageBox::information(this, "Shopping Basket", message);
}



void UserWindow::emptyBasketOfTrenchCoats() {
    // Clear the shopping basket
    controller.clearShoppingBasket();

    // Show a success message
    QMessageBox::information(this, "Success", "Shopping basket cleared successfully.");
}




void UserWindow::displayShoppingBasket() {
    // Ask the user to enter the filename of the shopping basket
    QString filename = QInputDialog::getText(this, "Enter filename", "Enter the filename of the shopping basket (with .csv or .html extension):");
    if (filename.isEmpty()) {
        // The user canceled the dialog
        return;
    }

    // Depending on the file extension, determine the command to open the file
    QString extension = QFileInfo(filename).suffix();
    if (extension != "csv" && extension != "html") {
        // Unsupported file format
        QMessageBox::warning(this, "Error", "Unsupported file format!");
        return;
    }

    // Save the shopping basket to the file
    // TODO: Implement this function in your Controller class
    //controller.saveShoppingBasketToFile(filename.toStdString());

    // Open the file with the default application
    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}








void UserWindow::saveShoppingBasketToFile() {
    // Ask the user to enter the filename of the shopping basket
    QString filename = QInputDialog::getText(this, "Enter filename", "Enter the filename of the shopping basket (with .csv or .html extension):");
    if (filename.isEmpty()) {
        // The user canceled the dialog
        return;
    }

    // Depending on the file extension, save the shopping basket to the file in the correct format
    QString extension = QFileInfo(filename).suffix();
    std::vector<TrenchCoat> shoppingBasket = controller.getShoppingBasketTrenchCoats();
    if (extension == "csv") {
        FileStorage::saveToCSV(shoppingBasket, filename.toStdString());
    }
    else if (extension == "html") {
        FileStorage::saveToHTML(shoppingBasket, filename.toStdString());
    }
    else {
        // Unsupported file format
        QMessageBox::warning(this, "Error", "Unsupported file format!");
    }
}
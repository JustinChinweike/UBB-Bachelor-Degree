#include "TrenchCoatGUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include "Controller.h"

TrenchCoatGUI::TrenchCoatGUI(Controller& controller, QWidget* parent)
    : QWidget(parent), controller(controller)
{
	// Create a new QVBoxLayout
	QVBoxLayout* mainLayout = new QVBoxLayout;
    
    
    // Create UI elements
    QLabel* titleLabel = new QLabel("Proper Trench Coats");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont font = titleLabel->font();
    font.setPointSize(20);
    font.setBold(true);
    titleLabel->setFont(font);

    adminButton = new QPushButton("Administrator Mode");
    userButton = new QPushButton("User Mode");

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(adminButton);
    mainLayout->addWidget(userButton);

    setLayout(mainLayout);

    connect(adminButton, &QPushButton::clicked, this, &TrenchCoatGUI::adminMode);
    connect(userButton, &QPushButton::clicked, this, &TrenchCoatGUI::userMode);
}

void TrenchCoatGUI::adminMode() {
    clearLayout();
    QVBoxLayout* adminLayout = new QVBoxLayout;

    QLabel* adminTitleLabel = new QLabel("Administrator Mode");
    adminTitleLabel->setAlignment(Qt::AlignCenter);
    QFont font = adminTitleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    adminTitleLabel->setFont(font);

    tableView = new QTableView;
    model = new QStandardItemModel;

    // Populate the table with data from the repository
    auto allTrenchCoats = controller.getAllTrenchCoats();
    int row = 0;
    for (const auto& trenchCoat : allTrenchCoats) {
        model->setItem(row, 0, new QStandardItem(QString::number(trenchCoat.getTrenchID())));
        model->setItem(row, 1, new QStandardItem(QString::number(trenchCoat.getTrenchSize())));
        model->setItem(row, 2, new QStandardItem(QString::fromStdString(trenchCoat.getTrenchColour())));
        model->setItem(row, 3, new QStandardItem(QString::number(trenchCoat.getTrenchPrice())));
        model->setItem(row, 4, new QStandardItem(QString::number(trenchCoat.getTrenchQuantity())));
        model->setItem(row, 5, new QStandardItem(QString::fromStdString(trenchCoat.getTrenchPhotographyLink())));
        row++;
    }

    model->setHorizontalHeaderLabels({ "ID", "Size", "Colour", "Price", "Quantity", "Photograph" });
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    adminLayout->addWidget(adminTitleLabel);
    adminLayout->addWidget(tableView);

    setLayout(adminLayout);
}

void TrenchCoatGUI::userMode() {
    clearLayout();
    QVBoxLayout* userLayout = new QVBoxLayout;

    QLabel* userTitleLabel = new QLabel("User Mode");
    userTitleLabel->setAlignment(Qt::AlignCenter);
    QFont font = userTitleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    userTitleLabel->setFont(font);

    QLabel* userInstructionsLabel = new QLabel("Choose an option:");
    userInstructionsLabel->setAlignment(Qt::AlignCenter);

    QPushButton* browseButton = new QPushButton("Browse Trench Coats");
    QPushButton* viewBasketButton = new QPushButton("View Shopping Basket");

    userLayout->addWidget(userTitleLabel);
    userLayout->addWidget(userInstructionsLabel);
    userLayout->addWidget(browseButton);
    userLayout->addWidget(viewBasketButton);

    setLayout(userLayout);

    connect(browseButton, &QPushButton::clicked, this, &TrenchCoatGUI::browseTrenchCoats);
    connect(viewBasketButton, &QPushButton::clicked, this, &TrenchCoatGUI::viewShoppingBasket);
}

void TrenchCoatGUI::browseTrenchCoats() {
    clearLayout();
    QVBoxLayout* browseLayout = new QVBoxLayout;

    QLabel* browseTitleLabel = new QLabel("Browse Trench Coats");
    browseTitleLabel->setAlignment(Qt::AlignCenter);
    QFont font = browseTitleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    browseTitleLabel->setFont(font);

    tableView = new QTableView;
    model = new QStandardItemModel;

    // Populate the table with data from the repository
    auto allTrenchCoats = controller.getAllTrenchCoats();
    int row = 0;
    for (const auto& trenchCoat : allTrenchCoats) {
        model->setItem(row, 0, new QStandardItem(QString::number(trenchCoat.getTrenchID())));
        model->setItem(row, 1, new QStandardItem(QString::number(trenchCoat.getTrenchSize())));
        model->setItem(row, 2, new QStandardItem(QString::fromStdString(trenchCoat.getTrenchColour())));
        model->setItem(row, 3, new QStandardItem(QString::number(trenchCoat.getTrenchPrice())));
        model->setItem(row, 4, new QStandardItem(QString::number(trenchCoat.getTrenchQuantity())));
        model->setItem(row, 5, new QStandardItem(QString::fromStdString(trenchCoat.getTrenchPhotographyLink())));
        row++;
    }

    model->setHorizontalHeaderLabels({ "ID", "Size", "Colour", "Price", "Quantity", "Photograph" });
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    browseLayout->addWidget(browseTitleLabel);
    browseLayout->addWidget(tableView);

    setLayout(browseLayout);

}




void TrenchCoatGUI::viewShoppingBasket() {
    clearLayout();
    QVBoxLayout* basketLayout = new QVBoxLayout;

    QLabel* basketTitleLabel = new QLabel("All Trench Coats");
    basketTitleLabel->setAlignment(Qt::AlignCenter);
    QFont font = basketTitleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    basketTitleLabel->setFont(font);

    tableView = new QTableView;
    model = new QStandardItemModel;

    // Populate the table with data from the repository
    auto allItems = controller.getAllTrenchCoats();
    int row = 0;
    for (const auto& item : allItems) {
        model->setItem(row, 0, new QStandardItem(QString::number(item.getTrenchID())));
        model->setItem(row, 1, new QStandardItem(QString::number(item.getTrenchSize())));
        model->setItem(row, 2, new QStandardItem(QString::fromStdString(item.getTrenchColour())));
        model->setItem(row, 3, new QStandardItem(QString::number(item.getTrenchPrice())));
        model->setItem(row, 4, new QStandardItem(QString::number(item.getTrenchQuantity())));
        model->setItem(row, 5, new QStandardItem(QString::fromStdString(item.getTrenchPhotographyLink())));
        row++;
    }

    model->setHorizontalHeaderLabels({ "ID", "Size", "Colour", "Price", "Quantity", "Photograph" });
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    basketLayout->addWidget(basketTitleLabel);
    basketLayout->addWidget(tableView);

    setLayout(basketLayout);
}





void TrenchCoatGUI::clearLayout() {
    QLayout* layout = this->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}



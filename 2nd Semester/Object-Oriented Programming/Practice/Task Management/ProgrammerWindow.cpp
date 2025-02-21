#include "ProgrammerWindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>

ProgrammerWindow::ProgrammerWindow(TaskController& controller, const Programmer& programmer, QWidget* parent)
    : QMainWindow(parent), controller(controller), programmer(programmer) {
    setWindowTitle(QString::fromStdString(programmer.name));

    QVBoxLayout* layout = new QVBoxLayout;

    taskListWidget = new QListWidget(this);
    layout->addWidget(taskListWidget);

    QPushButton* addTaskButton = new QPushButton("Add Task", this);
    layout->addWidget(addTaskButton);
    connect(addTaskButton, &QPushButton::clicked, this, &ProgrammerWindow::addTask);

    QPushButton* removeTaskButton = new QPushButton("Remove Task", this);
    layout->addWidget(removeTaskButton);
    connect(removeTaskButton, &QPushButton::clicked, this, &ProgrammerWindow::removeTask);

    QPushButton* startTaskButton = new QPushButton("Start Task", this);
    layout->addWidget(startTaskButton);
    connect(startTaskButton, &QPushButton::clicked, this, &ProgrammerWindow::startTask);

    QPushButton* doneTaskButton = new QPushButton("Done Task", this);
    layout->addWidget(doneTaskButton);
    connect(doneTaskButton, &QPushButton::clicked, this, &ProgrammerWindow::doneTask);

    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);

    populateTaskList(); // Populate the task list initially
}

void ProgrammerWindow::addTask() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Task"), tr("Task description:"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        controller.addTask(text.toStdString());
        populateTaskList(); // Update the task list after adding a task
    }
}

void ProgrammerWindow::removeTask() {
    QListWidgetItem* item = taskListWidget->currentItem();
    if (item) {
        controller.removeTask(item->text().split(" (")[0].toStdString()); // Ensure task description is correctly extracted
        populateTaskList(); // Update the task list after removing a task
    }
}

void ProgrammerWindow::startTask() {
    QListWidgetItem* item = taskListWidget->currentItem();
    if (item) {
        try {
            controller.startTask(item->text().split(" (")[0].toStdString(), programmer.id); // Ensure task description is correctly extracted
            populateTaskList(); // Update the task list after starting a task
        }
        catch (const std::runtime_error& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void ProgrammerWindow::doneTask() {
    QListWidgetItem* item = taskListWidget->currentItem();
    if (item) {
        try {
            controller.completeTask(item->text().split(" (")[0].toStdString(), programmer.id); // Ensure task description is correctly extracted
            populateTaskList(); // Update the task list after completing a task
        }
        catch (const std::runtime_error& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void ProgrammerWindow::populateTaskList() {
    taskListWidget->clear();
    auto tasks = controller.getTasks();
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.status < b.status; // Adjust the sorting logic if needed
        });
    for (const Task& task : tasks) {
        QString itemText = QString::fromStdString(task.description) + " (" + statusToString(task.status) + ")";
        if (task.status != TaskStatus::Open) {
            itemText += " - " + QString::number(task.programmerId);
        }
        taskListWidget->addItem(itemText);
    }
}

QString ProgrammerWindow::statusToString(TaskStatus status) {
    switch (status) {
    case TaskStatus::Open: return "Open";
    case TaskStatus::InProgress: return "In Progress";
    case TaskStatus::Closed: return "Closed";
    default: return "";
    }
}

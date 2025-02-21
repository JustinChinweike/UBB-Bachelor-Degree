// TaskController.cpp
#include "TaskController.h"

const std::vector<Programmer>& TaskController::getProgrammers() const {
    return repository.getProgrammers();
}

const std::vector<Task>& TaskController::getTasks() const {
    return repository.getTasks();
}

void TaskController::addTask(const std::string& description) {
    repository.addTask(Task(description, TaskStatus::Open));
}

void TaskController::removeTask(const std::string& description) {
    repository.removeTask(description);
}

void TaskController::startTask(const std::string& description, int programmerId) {
    repository.updateTaskStatus(description, TaskStatus::InProgress, programmerId);
}

void TaskController::completeTask(const std::string& description, int programmerId) {
    repository.updateTaskStatus(description, TaskStatus::Closed, programmerId);
}

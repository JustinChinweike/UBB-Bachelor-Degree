#include "TaskRepository.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

TaskRepository::TaskRepository(const std::string& programmersFile, const std::string& tasksFile) {
    loadProgrammers(programmersFile);
    loadTasks(tasksFile);
}

void TaskRepository::loadProgrammers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    int id;
    std::string name;
    while (file >> id >> name) {
        programmers.push_back(Programmer(id, name));
    }

    file.close();
}

void TaskRepository::loadTasks(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string description, statusStr, programmerIdStr;
        std::getline(ss, description, ';');
        std::getline(ss, statusStr, ';');
        TaskStatus status;
        if (statusStr == "open") {
            status = TaskStatus::Open;
        }
        else if (statusStr == "in progress") {
            status = TaskStatus::InProgress;
        }
        else if (statusStr == "closed") {
            status = TaskStatus::Closed;
        }
        else {
            throw std::runtime_error("Invalid task status");
        }

        int programmerId = -1; // Default value for open tasks
        if (status != TaskStatus::Open) {
            std::getline(ss, programmerIdStr, ';');
            programmerId = std::stoi(programmerIdStr);
        }

        tasks.emplace_back(description, status, programmerId);
    }

    file.close();
}

void TaskRepository::saveTasks(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    for (const auto& task : tasks) {
        file << task.description << ";" << statusToString(task.status);
        if (task.status != TaskStatus::Open) {
            file << ";" << task.programmerId;
        }
        file << "\n";
    }

    file.close();
}

const std::vector<Programmer>& TaskRepository::getProgrammers() const {
    return programmers;
}

const std::vector<Task>& TaskRepository::getTasks() const {
    return tasks;
}

void TaskRepository::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskRepository::removeTask(const std::string& description) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [&](const Task& task) {
        return task.description == description;
        });
    tasks.erase(it, tasks.end());
}

void TaskRepository::updateTaskStatus(const std::string& description, TaskStatus status, int programmerId) {
    for (auto& task : tasks) {
        if (task.description == description) {
            if (task.status == TaskStatus::Open || (task.status == TaskStatus::InProgress && task.programmerId == programmerId)) {
                task.status = status;
                task.programmerId = programmerId;
                return;
            }
            else {
                throw std::runtime_error("Task cannot be updated by this programmer");
            }
        }
    }
}

std::string TaskRepository::statusToString(TaskStatus status) const {
    switch (status) {
    case TaskStatus::Open: return "open";
    case TaskStatus::InProgress: return "in progress";
    case TaskStatus::Closed: return "closed";
    default: return "";
    }
}

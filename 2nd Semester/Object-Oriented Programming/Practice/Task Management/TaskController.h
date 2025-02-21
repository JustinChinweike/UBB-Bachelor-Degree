// TaskController.h
#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include <vector>
#include <string>
#include "TaskRepository.h"
#include "Task.h"

class TaskController {
private:
    TaskRepository& repository;

public:
    TaskController(TaskRepository& repository) : repository(repository) {}

    const std::vector<Programmer>& getProgrammers() const;
    const std::vector<Task>& getTasks() const;

    void addTask(const std::string& description);
    void removeTask(const std::string& description);
    void startTask(const std::string& description, int programmerId);
    void completeTask(const std::string& description, int programmerId);
};

#endif // TASKCONTROLLER_H

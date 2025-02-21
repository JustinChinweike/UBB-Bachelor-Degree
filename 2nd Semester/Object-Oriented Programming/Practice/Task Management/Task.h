// Task.h
#ifndef TASK_H
#define TASK_H

#include <string>

enum class TaskStatus { Open, InProgress, Closed };

class Task {
public:
    std::string description;
    TaskStatus status;
    int programmerId;

    Task(const std::string& description, TaskStatus status, int programmerId = -1)
        : description(description), status(status), programmerId(programmerId) {}
};

#endif // TASK_H

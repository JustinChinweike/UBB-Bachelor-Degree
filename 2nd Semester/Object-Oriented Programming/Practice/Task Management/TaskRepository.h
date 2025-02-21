#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include "Task.h"
#include "Programmer.h"
#include <vector>
#include <string>

class TaskRepository {
private:
    std::vector<Programmer> programmers;
    std::vector<Task> tasks;

    void loadProgrammers(const std::string& filename);
    void loadTasks(const std::string& filename);

    std::string statusToString(TaskStatus status) const; // Add this line

public:
    TaskRepository(const std::string& programmersFile, const std::string& tasksFile);

    const std::vector<Programmer>& getProgrammers() const;
    const std::vector<Task>& getTasks() const;

    void addTask(const Task& task);
    void removeTask(const std::string& description);
    void updateTaskStatus(const std::string& description, TaskStatus status, int programmerId);

    void saveTasks(const std::string& filename);
};

#endif // TASKREPOSITORY_H

// TaskException.h
#ifndef TASKEXCEPTION_H
#define TASKEXCEPTION_H

#include <stdexcept>
#include <string>

class TaskException : public std::runtime_error {
public:
    TaskException(const std::string& message) : std::runtime_error(message) {}
};

#endif // TASKEXCEPTION_H

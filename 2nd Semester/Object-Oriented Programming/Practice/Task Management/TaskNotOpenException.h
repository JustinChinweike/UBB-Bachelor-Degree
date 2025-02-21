#ifndef TASKNOTOPENEXCEPTION_H
#define TASKNOTOPENEXCEPTION_H

#include <exception>
#include <string>

class TaskNotOpenException : public std::exception {
private:
    std::string message;

public:
    TaskNotOpenException(const std::string& msg) : message(msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // TASKNOTOPENEXCEPTION_H

#pragma once
#include <stdexcept>


class ValidatorException : public std::runtime_error {
public:
    explicit ValidatorException(const std::string& message) : std::runtime_error(message) {}
    
};
#pragma once
#include <stdexcept>


class RepositoryException : public std::runtime_error {
public:
	RepositoryException(const std::string& message) : std::runtime_error(message) {}

};
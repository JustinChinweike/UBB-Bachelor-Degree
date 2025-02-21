// Programmer.h
#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <string>

class Programmer {
public:
    int id;
    std::string name;

    Programmer(int id, const std::string& name) : id(id), name(name) {}
};

#endif // PROGRAMMER_H

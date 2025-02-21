
#ifndef A789_ABSTRACTSHOPPINGBASKET_H
#define A789_ABSTRACTSHOPPINGBASKET_H

#pragma once
#include <vector>
#include "domain.h"

class AbstractShoppingBasket {
public:
    virtual void write() = 0;
    virtual void open() = 0;
    virtual void set_data(std::vector<Coat> elements) = 0;
    virtual ~AbstractShoppingBasket() = default;
};

#endif //A789_ABSTRACTSHOPPINGBASKET_H
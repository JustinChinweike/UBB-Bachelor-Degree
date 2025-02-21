
#pragma once
#include <cstring>
#include "domain.h"
#include "AbstractShoppingBasket.h"
#include <vector>


class HTMLShoppingBasket : public AbstractShoppingBasket {
private:
    std::vector<Coat> elements;
    std::string FileName;

public:
    HTMLShoppingBasket();
    void write() override;
    void open() override;
    void set_data(std::vector<Coat> elements) override;
    ~HTMLShoppingBasket() override = default;

};
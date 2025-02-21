
#pragma once
#include "validation.h"
#include "AbstractShoppingBasket.h"
#include "service.h"
#include <iostream>
class Console
{
private:

    Service& service;
    AbstractShoppingBasket* ASB{};

public:

    /// Constructor
    Console(Service& service);

    /// Destructor
    ~Console() = default;

    void Start();

    void OpenApplication();

    void AdministratorMode();

    void UserMode();

    void DisplayShoppingBag();

    static void MenuAdminMode();

    void UpdateProductsPriceAdmin();

    void UpdateProductsQuantityAdmin();

    void DeleteEntireProductAdmin();

    int DisplayProductsUser();

    int DisplayProductsUserWithSize(const std::string& size);

    void DeleteSoldOutProductAdmin();

    void MenuDisplayProductsUser();

    void DisplayProductsAdmin();

    void AddAdminConsole();

};
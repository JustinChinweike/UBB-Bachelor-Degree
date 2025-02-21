
// TrenchCoatValidator.h
#pragma once
#include "Domain.h"
#include <string>
#include "ValidatorException.h"



class TrenchCoatValidator {
public:
    static void validate(const TrenchCoat& trenchCoat);
    static void validateID(int id);
    static void validateSize(int size);
    static void validateColour(const std::string& colour);
    static void validatePrice(float price);
    static void validateQuantity(int quantity);
    static void validatePhotographyLink(const std::string& photographyLink);
};

// TrenchCoatValidator.cpp
#include "TrenchCoatValidator.h"

void TrenchCoatValidator::validate(const TrenchCoat& trenchCoat) {
    validateID(trenchCoat.getTrenchID());
    validateSize(trenchCoat.getTrenchSize());
    validateColour(trenchCoat.getTrenchColour());
    validatePrice(trenchCoat.getTrenchPrice());
    validateQuantity(trenchCoat.getTrenchQuantity());
    validatePhotographyLink(trenchCoat.getTrenchPhotographyLink());
}

void TrenchCoatValidator::validateID(int id) {
    if (id <= 0) {
        throw ValidatorException("ID must be positive");
    }
}

void TrenchCoatValidator::validateSize(int size) {
    if (size <= 0) {
        throw ValidatorException("Size must be positive");
    }
}

void TrenchCoatValidator::validateColour(const std::string& colour) {
    if (colour.empty()) {
        throw ValidatorException("Colour cannot be empty");
    }
}

void TrenchCoatValidator::validatePrice(float price) {
    if (price <= 0) {
        throw ValidatorException("Price must be positive");
    }
}

void TrenchCoatValidator::validateQuantity(int quantity) {
    if (quantity < 0) {
        throw ValidatorException("Quantity must be non-negative");
    }
}

void TrenchCoatValidator::validatePhotographyLink(const std::string& photographyLink) {
    // Add validation rule for photography link
    // Here I am just checking if it is empty
    if (photographyLink.empty()) {
        throw ValidatorException("Photography link cannot be empty");
    }
}

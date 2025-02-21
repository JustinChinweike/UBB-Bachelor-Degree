//Domain.h
#pragma once
#include <string>
#include <iostream>
#include <fstream>

class TrenchCoat {
private:
    int id;
    int size;
    std::string colour;
    float price;
    int quantity;
    std::string photographyLink;

public:
    // Constructors
    TrenchCoat();
    TrenchCoat(
        int id,
        int sizeOfTrench,
        const std::string& colourOfTrench,
        float priceOfTrench,
        int quantityOfTrench,
        const std::string& photography_linkOfTrench
    );

    // Getter methods
    int getTrenchID() const;
    int getTrenchSize() const;
    std::string getTrenchColour() const;
    float getTrenchPrice() const;
    int getTrenchQuantity() const;
    std::string getTrenchPhotographyLink() const;


    // Comparison operator
    bool operator==(const TrenchCoat& trenchToCompare);


    // Setter methods
    void setTrenchID(int newID);
    void setTrenchSize(int newSize);
    void setTrenchColour(const std::string& newColour);
    void setTrenchPrice(float newPrice);
    void setTrenchQuantity(int newQuantity);
    void setTrenchPhotographyLink(const std::string& newPhotographyLink);



    // Insertion operator
    friend std::ostream& operator<<(std::ostream& out, const TrenchCoat& trench);

    // Extraction operator
    friend std::istream& operator>>(std::istream& in, TrenchCoat& trench);


};
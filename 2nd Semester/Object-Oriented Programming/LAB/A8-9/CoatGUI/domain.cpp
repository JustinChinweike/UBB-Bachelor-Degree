
#include <cstring>
#include "domain.h"
#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <sstream>


/**
* Constructor
*/
//



Coat::Coat() : size(""), color(""), price(0), quantity(0), photograph("") {}

/**
* Constructor
* @param size the size of the coat
* @param color the color of the coat
* @param price the price of the coat
* @param quantity the quantity of the coat
* @param photograph the link to the photograph of the coat
*/
Coat::Coat(std::string size, std::string color,
    int price, int quantity,
    std::string photograph) :
    size{ std::move(size) },
    color{ std::move(color) },
    price{ price },
    quantity{ quantity },
    photograph{ std::move(photograph) } {
}




/**
* With this function we set the quantity of the coat
* @param quantity the quantity we want to set
*/
void Coat::SetQuantity(int quantity) {
    this->quantity = quantity;
}


/**
* With this function we set the price of the coat
* @param price the price we want to set
*/
void Coat::SetPrice(int price) {
    this->price = price;
}


/**
* With this function we get the size of the coat
* @return returns the size of the coat
*/
const std::string& Coat::GetSize() const {
    return this->size;
}

/**
* With this function we get the color of the coat
* @return returns the color of the coat
*/
const std::string& Coat::GetColor() const {
    return this->color;
}


/**
* With this function we get the price of the coat
* @return returns the price of the coat
*/
const int& Coat::GetPrice() const {
    return this->price;
}


/**
* With this function we get the quantity of the coat
* @return returns the quantity of the goat
*/
int Coat::GetQuantity() const {
    return this->quantity;
}



/**
* With this function we get the link to the photograph of the coat
* @return returns the the link to the photograph of the coat
*/
const std::string& Coat::GetPhotograph() const {
    return this->photograph;
}


/**
* With this function we get the link to the photograph of the coat
*   @return returns the the link to the photograph of the coat
*/

Coat& Coat::operator=(const Coat& coat) {
    this->size = coat.size;
    this->color = coat.color;
    this->price = coat.price;
    this->quantity = coat.quantity;
    this->photograph = coat.photograph;
    return *this;
}

/**
* With this function we split a string into tokens
* @param str the string we want to split
* @param delimiter the delimiter we want to split by
* @return returns a vector of strings
*/
std::vector<std::string> Coat::tokenize(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

/**
* Overloading the << operator
*   @param output the output stream
*   @param coat the coat we want to print
*  @return returns the output stream
*/
std::ostream& operator<<(std::ostream& output, const Coat& coat) {
    output << coat.size << "," << coat.color << "," << coat.price << "," << coat.quantity << "," << coat.photograph;
    return output;
}


/**
* Overloading the >> operator
*   @param input the input stream
*   @param coat the coat we want to read
* @return returns the input stream
*/
std::istream& operator>>(std::istream& input, Coat& coat) {
    std::string line;
    getline(input, line);
    std::vector<std::string> tokens = Coat::tokenize(line, ',');
    if (tokens.size() != 5)
        return input;
    coat.size = tokens[0];
    coat.color = tokens[1];
    coat.price = stoi(tokens[2]);
    coat.quantity = stoi(tokens[3]);
    coat.photograph = tokens[4];
    return input;
}
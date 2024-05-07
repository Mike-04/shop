//
// Created by White Fox on 3/31/2024.
//

#include "domain.h"
#include <iostream>
#include "myexception.h"
//Description: Default constructor for the Product class
//Input: -
//Output: A Product object with default values
Product::Product() : id(0), price(0){
}

//Description: Constructor for the Product class
//Input: an integer representing the id of the product, a string representing the name of the product, a string representing the type of the product, a double representing the price of the product, a string representing the producer of the product
//Output: A Product object with the given values
Product::Product(int id, string name, string type, double price, string producer) : id(id), name(name), type(type), price(price), producer(producer) {
}

//Description: This function returns the id of the product
//Input: -
//Output: an integer representing the id of the product
int Product::getId() const {
    return this->id;
}

//Description: This function returns the name of the product
//Input: -
//Output: a string representing the name of the product
string Product::getName() const{
    return this->name;
}

//Description: This function returns the type of the product
//Input: -
//Output: a string representing the type of the product
string Product::getType() const {
    return this->type;
}


//Description: This function returns the price of the product
//Input: -
//Output: a double representing the price of the product
double Product::getPrice() const {
    return this->price;
}

//Description: This function returns the producer of the product
//Input: -
//Output: a string representing the producer of the product
string Product::getProducer() const {
    return this->producer;
}

//Description: This function sets the id of the product
//Input: an integer representing the id of the product
//Output: -
void Product::setId(const int &id) {
    this->id = id;
}

//Description: This function sets the name of the product
//Input: a string representing the name of the product
//Output: -
void Product::setName(const string &name) {
    this->name = name;
}

//Description: This function sets the type of the product
//Input: a string representing the type of the product
//Output: -
void Product::setType(const string &type) {
    this->type = type;
}

//Description: This function sets the price of the product
//Input: a double representing the price of the product
//Output: -
void Product::setPrice(const double &price) {
    this->price = price;
}

//Description: This function sets the producer of the product
//Input: a string representing the producer of the product
//Output: -
void Product::setProducer(const string &producer) {
    this->producer = producer;
}

//Description: Copy constructor for the Product class
//Input: a Product object
//Output: A Product object with the same values as the given object
Product::Product(Product const &p) : id(p.id), name(p.name), type(p.type), price(p.price), producer(p.producer) {
    //cout<< "Copy constructor called" << endl;
}

//Description: This function returns a string representation of the product
//Input: -
//Output: a string representing the product
string Product::toString() {
    char new_price[100];
    sprintf(new_price, "%.2f", this->price);
    return to_string(this->id) + ", " + this->name + ", " + this->type + ", " + new_price + ", " + this->producer;
}

//Description: Overloaded assignment operator for the Product class
//Input: a Product object
//Output: a Product object with the same values as the given object
Product& Product::operator = (Product const &p) {
    this->id = p.id;
    this->name = p.name;
    this->type = p.type;
    this->price = p.price;
    this->producer = p.producer;
    return *this;
}

//Description: Overloaded equality operator for the Product class
//Input: a Product object
//Output: a boolean value, true if the products are equal, false otherwise
bool Product::operator==(Product const &p) {
    return this->name == p.name && this->type == p.type && this->price == p.price && this->producer == p.producer;
}

//Description: Destructor for the Product class
//Input: -
//Output: -
Product::~Product() = default;

//Description: This function validates the product
//Input: -
//Output: a boolean value, true if the product is valid, false otherwise
void Product::validate() {
    if (this->name.empty() || this->type.empty() || this->producer.empty() || this->price < 0) {
    throw ValidationException("Invalid product!\n");
    }
}
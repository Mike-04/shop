//
// Created by White Fox on 3/31/2024.
//

#include "domain.h"
#include <iostream>
#include <utility>

Product::Product() {
    this->id = 0;
    this->name = "";
    this->type = "";
    this->price = 0;
    this->producer = "";
}

Product::Product(int id, string name, string type, double price, string producer) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->price = price;
    this->producer = producer;
}

int Product::getId() const {
    return this->id;
}

string Product::getName() const{
    return this->name;
}

string Product::getType() const {
    return this->type;
}

double Product::getPrice() const {
    return this->price;
}

string Product::getProducer() const {
    return this->producer;
}

void Product::setId(const int id) {
    this->id = id;
}

void Product::setName(const string name) {
    this->name = name;
}

void Product::setType(const string type) {
    this->type = type;
}

void Product::setPrice(const double price) {
    this->price = price;
}

void Product::setProducer(const string producer) {
    this->producer = producer;
}

string Product::toString() {
    char new_price[100];
    sprintf(new_price, "%.2f", this->price);
    return to_string(this->id) + ", " + this->name + ", " + this->type + ", " + new_price + ", " + this->producer;
}

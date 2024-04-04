//
// Created by White Fox on 3/31/2024.
//
#pragma once
#ifndef SHOP_DOMAIN_H
#define SHOP_DOMAIN_H

#endif //SHOP_DOMAIN_H
#include <string>

using namespace std;

class Product {
private:


    int id;
    string name;
    string type;
    double price;
    string producer;

public:

    Product();
    Product(int id, string name, string type, double price, string producer);
    Product(Product const &p);
    int getId() const;
    string getName() const;
    string getType() const;
    double getPrice() const;
    string getProducer() const;
    void setId(int const &id);
    void setName(string const &name);
    void setType(string const &type);
    void setPrice(double const &price);
    void setProducer(string const &producer);
    string toString();
};
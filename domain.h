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
    int getId() const;
    string getName() const;
    string getType() const;
    double getPrice() const;
    string getProducer() const;
    void setId(int id);
    void setName(string name);
    void setType(string type);
    void setPrice(double price);
    void setProducer(string producer);
    string toString();
};
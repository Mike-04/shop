//
// Created by White Fox on 3/31/2024.
//
#pragma once
#ifndef SHOP_SERVICE_H
#define SHOP_SERVICE_H

#endif //SHOP_SERVICE_H

#include "repo.h"

class Service {
private:
    Repository repo;
public:
    Service();
    Service(Repository repo);
    void addProduct(string name, string type, double price, string producer);
    void removeProduct(int id);
    void updateProduct(int id, string name, string type, double price, string producer);
    vector<Product> getProducts();
    Product getProductById(int id);
    int getSize();

    int generateId();
};

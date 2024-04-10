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
    explicit Service(Repository repo);
    void addProduct(string name, string type, double price, string producer);
    void removeProduct(int id);
    void updateProduct(int id, string name, string type, double price, string producer);
    List<Product>* getProducts();
    Product getProductById(int id);
    unsigned long getSize();
    void filterProducts(List<Product>* filteredProducts,string name, string type,int minPrice,int maxPrice);
    void sortProducts(List<Product>* sortedProducts,int command);
    int generateId();
};

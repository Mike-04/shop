//
// Created by White Fox on 3/31/2024.
//
#pragma once
#ifndef SHOP_SERVICE_H
#define SHOP_SERVICE_H

#endif //SHOP_SERVICE_H

#include "repo.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <map>


class Service {
private:
    Repository repo;
public:
    Service();
    explicit Service(Repository repo);
    void addProduct(string name, string type, double price, string producer);
    void removeProduct(int id);
    void updateProduct(int id, string name, string type, double price, string producer);
    vector<Product> & getProducts();
    Product getProductById(int id);
    unsigned long getSize();
    int getPosition(Product &p);
    void filterProducts(vector<Product>& filteredProducts,string name, string type,int minPrice,int maxPrice);
    static void sortProducts(vector<Product>& sortedProducts,int command);
    static map<string,vector<Product>> groupProductsByProducer(vector<Product> & products);
    int generateId();
    void addProductToBasket(int id);
    vector<Product> & getBasket();
    void emptyBasket();
    void generateRandomBasket(int n);
    void exportBasketToCSV(string filename);
    void exportBasketToHTML(string filename);
};

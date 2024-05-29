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
#include <memory>
#include <iterator>
#include <vector>
#include "undo.h"
#include "observer.h"
using std::unique_ptr;

int rand(int min,int max);

class Service : public Observable{
private:
    Repo& repo;
    std::vector<unique_ptr<UndoAction>> undoActions;
public:
    explicit Service(Repo& repo): repo{repo} {}
    ~Service() = default;
    Service(const Service &s) = delete;
    void operator=(const Service &s) = delete;
    void addProduct(string name, string type, double price, string producer);
    void removeProduct(int id);
    void updateProduct(int id, string name, string type, double price, string producer);
    void undo();
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

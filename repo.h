//
// Created by White Fox on 3/31/2024.
//

#ifndef SHOP_REPO_H
#define SHOP_REPO_H

#endif //SHOP_REPO_H
#pragma once
#include "domain.h"
#include <vector>

class Repository {
private:
    vector<Product> products;
public:
    Repository();
    void addProduct(Product p);
    void removeProduct(int id);
    void updateProduct(int id, Product p);
    vector<Product> getProducts();
    Product getProductById(int id);
    int getSize();
};
//
// Created by White Fox on 3/31/2024.
//

#include "repo.h"

Repository::Repository() {
    this->products = {};
}

void Repository::addProduct(const Product p) {
    this->products.push_back(p);
}

void Repository::removeProduct(int id) {
    for (int i = 0; i < this->products.size(); i++) {
        if (this->products[i].getId() == id) {
            this->products.erase(this->products.begin() + i);
            return;
        }
    }
}

void Repository::updateProduct(int id, Product p) {
    for (auto & product : this->products) {
        if (product.getId() == id) {
            product = p;
            return;
        }
    }
}

vector<Product> Repository::getProducts() {
    return this->products;
}

Product Repository::getProductById(int id) {
    for (auto & product : this->products) {
        if (product.getId() == id) {
            return product;
        }
    }
    return Product();
}

int Repository::getSize() {
    return this->products.size();
}




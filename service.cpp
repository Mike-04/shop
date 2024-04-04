//
// Created by White Fox on 3/31/2024.
//

#include "service.h"
#include <iostream>

Service::Service() {
    this->repo = Repository();
}

Service::Service(Repository repo) {
    this->repo = repo;
}

int Service::generateId() {
    //generate the new available id in the list
    int id = 0;
for (auto & product : this->repo.getProducts()) {
        if (product.getId() > id) {
            id = product.getId();
        }
    }
    return id + 1;
}


void Service::addProduct(string name, string type, double price, string producer) {
    Product p = Product(generateId(), name, type, price, producer);
    this->repo.addProduct(p);
}

void Service::removeProduct(int id) {
    this->repo.removeProduct(id);
}

void Service::updateProduct(int id, string name, string type, double price, string producer) {
    Product p = Product(id, name, type, price, producer);
    this->repo.updateProduct(id, p);
}

vector<Product> Service::getProducts() {
    return this->repo.getProducts();
}

Product Service::getProductById(int id) {
    return this->repo.getProductById(id);
}

int Service::getSize() {
    return this->repo.getSize();
}


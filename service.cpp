//
// Created by White Fox on 3/31/2024.
//

#include "service.h"

//Description: This function creates a service object
//Input: -
//Output: a service object
Service::Service() {
    this->repo = Repository();
}

//Description: This function creates a service object
//Input: a repository object
//Output: a service object
Service::Service(Repository repo) : repo(repo) {

}

//Description: This function generates the new available id in the list
//Input: -
//Output: an integer representing the new available id in the list
int Service::generateId() {
    //generate the new available id in the list
    //cout<<"Service generateId";
    int id = 0;
    vector<Product>* products = this->repo.getProducts();
for (auto & product : *products) {
        if (product.getId() > id) {
            id = product.getId();
        }
    }
    return id + 1;
}

//Description: This function adds a product to the list
//Input: a string representing the name of the product, a string representing the type of the product, a double representing the price of the product, a string representing the producer of the product
//Output: -
void Service::addProduct(string name, string type, double price, string producer) {
    //cout<<"Service addProduct";
    Product p = Product(generateId(), name, type, price, producer);
    this->repo.addProduct(p);
}

//Description: This function removes a product from the list
//Input: an integer representing the id of the product
//Output: -
void Service::removeProduct(int id) {
    this->repo.removeProduct(id);
}

//Description: This function updates a product from the list
//Input: an integer representing the id of the product, a string representing the name of the product, a string representing the type of the product, a double representing the price of the product, a string representing the producer of the product
//Output: -
void Service::updateProduct(int id, string name, string type, double price, string producer) {
    Product p = Product(id, name, type, price, producer);
    this->repo.updateProduct(id, p);
}

//Description: This function returns the list of products
//Input: -
//Output: a pointer to the list of products
vector<Product>* Service::getProducts() {
    return this->repo.getProducts();
}

//Description: This function returns a product from the list
//Input: an integer representing the id of the product
//Output: a product object
Product Service::getProductById(int id) {
    return this->repo.getProductById(id);
}

//Description: This function returns the size of the list
//Input: -
//Output: an integer representing the size of the list
unsigned long Service::getSize() {
    return this->repo.getSize();
}


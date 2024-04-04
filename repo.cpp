//
// Created by White Fox on 3/31/2024.
//

#include "repo.h"


//Description: Default constructor for the Repository class
//Input: -
//Output: A Repository object with an empty vector of products
Repository::Repository() : products({}) {

}

//Description: This function adds a product to the list
//Input: a Product object
//Output: -
void Repository::addProduct(const Product& p) {
    //cout<<"Repository addProduct";
    this->products.push_back(p);
}

//Description: This function removes a product from the list
//Input: an integer representing the id of the product
//Output: -
void Repository::removeProduct(int id) {
    for (int i = 0; i < this->products.size(); i++) {
        if (this->products[i].getId() == id) {
            this->products.erase(this->products.begin() + i);
            return;
        }
    }
}

//Description: This function updates a product from the list
//Input: an integer representing the id of the product, a Product object
//Output: -
void Repository::updateProduct(int id, const Product& p) {
    for (auto & product : this->products) {
        if (product.getId() == id) {
            product = p;
            return;
        }
    }
}

//Description: This function returns a pointer to the vector of products
//Input: -
//Output: a pointer to the vector of products
vector<Product>* Repository::getProducts() {
    //return pointer to the vector
    return &this->products;
}

//Description: This function returns a product from the list
//Input: an integer representing the id of the product
//Output: a Product object
Product Repository::getProductById(int id) {
    for (auto & product : this->products) {
        if (product.getId() == id) {
            return product;
        }
    }
    return {};
}

//Description: This function returns the size of the list
//Input: -
//Output: an integer representing the size of the list
unsigned long Repository::getSize() {
    return this->products.size();
}




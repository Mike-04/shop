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
void Repository::addProduct(Product &p) {
    //cout<<"Repository addProduct";
    this->products_list.append(p);
}

//Description: This function removes a product from the list
//Input: an integer representing the id of the product
//Output: -
void Repository::removeProduct(int id) {
    for (int i = 0; i < this->products_list.getSize(); i++) {
        if (this->products_list.element(i).getId() == id) {
            this->products_list.remove(i);
            return;
        }
    }
}

//Description: This function updates a product from the list
//Input: an integer representing the id of the product, a Product object
//Output: -
void Repository::updateProduct(int id, Product &p) {
    for(int i=0;i<this->products_list.getSize();i++){
        if (products_list.element(i).getId() == id) {
            products_list.update(i,p);
            return;
        }
    }
}

//Description: This function returns a pointer to the vector of products
//Input: -
//Output: a pointer to the vector of products
List<Product>* Repository::getProducts() {
    //return pointer to the vector
    return &this->products_list;
}

//Description: This function returns a product from the list
//Input: an integer representing the id of the product
//Output: a Product object
Product Repository::getProductById(int id) {
    for(int i=0;i<this->products_list.getSize();i++) {
        if (products_list.element(i).getId() == id) {
            return products_list.element(i);
        }
    }
    return {};
}

//Description: This function returns the size of the list
//Input: -
//Output: an integer representing the size of the list
unsigned long Repository::getSize() {
    return this->products_list.getSize();
}

//Description: Destructor for the Repository class
//Input: -
//Output: -
Repository::~Repository() {
    //delete the vector
    //delete this->products;
}




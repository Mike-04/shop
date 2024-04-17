//
// Created by White Fox on 3/31/2024.
//

#include "repo.h"


//Description: Default constructor for the Repository class
//Input: -
//Output: A Repository object with an empty vector of products
Repository::Repository() : products_list({}) {

}

//Description: This function adds a product to the list
//Input: a Product object
//Output: -
void Repository::addProduct(Product &p) {
    //cout<<"Repository addProduct";
    this->products_list.push_back(p);
}

//Description: This function removes a product from the list
//Input: an integer representing the id of the product
//Output: -
void Repository::removeProduct(int id) {
    for (int i = 0; i < this->products_list.size(); i++) {
        if (this->products_list.at(i).getId() == id) {
            this->products_list.erase(products_list.begin()+i);
            return;
        }
    }
}

//Description: This function updates a product from the list
//Input: an integer representing the id of the product, a Product object
//Output: -
void Repository::updateProduct(int id, Product &p) {
    for(int i=0;i<this->products_list.size();i++){
        if (products_list.at(i).getId() == id) {
            products_list[i]=p;
            return;
        }
    }
}

//Description: This function returns a pointer to the vector of products
//Input: -
//Output: a pointer to the vector of products
vector<Product>* Repository::getProducts() {
    //return pointer to the vector
    return &this->products_list;
}

//Description: This function returns a product from the list
//Input: an integer representing the id of the product
//Output: a Product object
Product Repository::getProductById(int id) {
    for(int i=0;i<this->products_list.size();i++) {
        if (products_list.at(i).getId() == id) {
            return products_list.at(i);
        }
    }
    return {};
}

//Description: This function returns the size of the list
//Input: -
//Output: an integer representing the size of the list
unsigned long Repository::getSize() {
    return this->products_list.size();
}

//Description: Destructor for the Repository class
//Input: -
//Output: -
Repository::~Repository() {
    //delete the vector
    //delete this->products;
}

//Description: This function returns the position of a product in the list
//Input: a Product object
//Output: an integer representing the position of the product in the list
int Repository::getPosition(Product &p) {
    for(int i=0;i<this->products_list.size();i++){
        if(products_list.at(i)==p){
            return i;
        }
    }
    return -1;
}

//Description: This function adds a product to the basket
//Input: an intiger representing the id of the product
//Output: -
void Repository::addProductToBasket(int id) {
    for (int i = 0; i < this->products_list.size(); i++) {
        if (this->products_list.at(i).getId() == id) {
            this->basket.push_back(this->products_list.at(i));
            return;
        }
    }
}





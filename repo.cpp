//
// Created by White Fox on 3/31/2024.
//

#include "repo.h"
#include <iostream>
#include <algorithm>


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
    for (unsigned long i = 0; i < this->products_list.size(); i++) {
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
    for(unsigned long i=0;i<this->products_list.size();i++){
        if (products_list.at(i).getId() == id) {
            products_list[i]=p;
            return;
        }
    }
}

//Description: This function returns a pointer to the vector of products
//Input: -
//Output: a pointer to the vector of products
vector<Product> & Repository::getProducts() {
    //return pointer to the vector
    return this->products_list;
}

//Description: This function returns a product from the list
//Input: an integer representing the id of the product
//Output: a Product object
Product Repository::getProductById(int id) {
    for(unsigned long i=0;i<this->products_list.size();i++) {
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
unsigned long Repository::getPosition(Product &p) {
    for(unsigned long i=0;i < this->products_list.size();i++){
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
    for(const auto & i : this->products_list) {
        if (i.getId() == id) {
            this->basket.push_back(i);
            return;
        }
    }
}

//Description: This function removes a product from the basket
//Input: an integer representing the id of the product
//Output: -
void Repository::emptyBasket() {
     this->basket.clear();
}


//Description: This function returns the basket
//Input: -
//Output: a vector of Product objects representing the basket
vector<Product> & Repository::getBasketRepo() {
    return this->basket;
}

//Description: Default constructor for the Repository_Map class
//Input: -
//Output: A Repository_Map object with an empty map of products
Repository_Map::Repository_Map(double maximus_crapatos) : products_map({}) {
    this->maximus_crapatos = maximus_crapatos;
}

//Description: This function adds a product to the map
//Input: a Product object
//Output: -
void Repository_Map::addProduct(Product &p) {
    procesus_destructos();
    this->products_map.insert({p.getId(),p});
}

//Description: This function removes a product from the map
//Input: an integer representing the id of the product
//Output: -
void Repository_Map::removeProduct(int id) {
    procesus_destructos();
    this->products_map.erase(id);
}

//Description: This function updates a product from the map
//Input: an integer representing the id of the product, a Product object
//Output: -
void Repository_Map::updateProduct(int id, Product &p) {
    procesus_destructos();
    this->products_map[id]=p;
}

//Description: This function returns a pointer to the vector of products
//Input: -
//Output: a pointer to the vector of products
vector<Product> & Repository_Map::getProducts() {
    procesus_destructos();
    static std::vector<Product> products;
    products.clear();  // Clear the vector to ensure it's empty

    products.reserve(products_map.size());  // optional: reserve space to avoid reallocations
    std::transform(products_map.begin(), products_map.end(), std::back_inserter(products),
                   [](const auto& pair) { return pair.second; });

    return products;
}

//Description: This function returns a product from the map
//Input: an integer representing the id of the product
//Output: a Product object
Product Repository_Map::getProductById(int id) {
    procesus_destructos();
    return this->products_map[id];
}

//Description: This function returns the size of the map
//Input: -
//Output: an integer representing the size of the map
unsigned long Repository_Map::getSize() {
    procesus_destructos();
    return this->products_map.size();
}

//Description: Destructor for the Repository_Map class
//Input: -
//Output: -
Repository_Map::~Repository_Map() {
    //delete the map
    //delete this->products;
}

//Description: This function returns the position of a product in the map
//Input: a Product object
//Output: an integer representing the position of the product in the map
unsigned long Repository_Map::getPosition(Product &p) {
    procesus_destructos();
    unsigned long index=0;
    for(const auto & product : this->products_map){
        if(static_cast<Product>(product.second) == p){
            return index;
        }
        index++;
    }
    return -1;
}

//Description: This function adds a product to the basket
//Input: an integer representing the id of the product
//Output: -
void Repository_Map::addProductToBasket(int id) {
    procesus_destructos();
    for(const auto & i : this->products_map) {
        if (i.second.getId() == id) {
            this->basket.push_back(i.second);
            return;
        }
    }
}

//Description: This function removes a product from the basket
//Input: an integer representing the id of the product
//Output: -
void Repository_Map::emptyBasket() {
    procesus_destructos();
    this->basket.clear();
}

//Description: This function returns the basket
//Input: -
//Output: a vector of Product objects representing the basket
vector<Product> & Repository_Map::getBasketRepo() {
    procesus_destructos();
    return this->basket;
}

//Description: This function generates a random number
//Input: -
//Output: an integer representing the random number
int Repository_Map::randomus_crapatos() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 100);
    return dist6(rng);
}

//Description: This function generates a random number and if that number is more than the maximus_crapatos, it throws an exception
//Input: -
//Output: -
void Repository_Map::procesus_destructos() const {
    double maximus_destructos = randomus_crapatos()/100.0;
    if(maximus_destructos<maximus_crapatos){throw SkillDiffLRatioException("Procesus destructos has maximus crapatos your programus\n");}
}









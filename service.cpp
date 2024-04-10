//
// Created by White Fox on 3/31/2024.
//

#include "service.h"
#include <iostream>
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
    List<Product>* products = this->repo.getProducts();
for (int i = 0; i < products->getSize(); i++) {
        if (products->element(i).getId() > id) {
            id = products->element(i).getId();
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
    if(p.validate())
    this->repo.addProduct(p);
    else
        std::cout<<"Invalid product";
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
    if(p.validate())
    this->repo.updateProduct(id, p);
    else
        std::cout<<"Invalid product";
}

//Description: This function returns the list of products
//Input: -
//Output: a pointer to the list of products
List<Product>* Service::getProducts() {
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

//Description: This function filters the products by name, type, minPrice and maxPrice
//Input: a string representing the string match of the name, a string representing  string match of the product, an integer representing the minPrice of the product, an integer representing the maxPrice of the product
//Output: a pointer to the list of products
void Service::filterProducts(List<Product>* filteredProducts,std::string name, std::string type, int minPrice, int maxPrice) {
    List<Product>* products = this->repo.getProducts();
    for (int i = 0; i < products->getSize(); i++) {
        Product p = products->element(i);
        if (p.getName().find(name) != string::npos && p.getType().find(type) != string::npos && p.getPrice() >= minPrice && p.getPrice() <= maxPrice){
            filteredProducts->append(p);
        }
    }
}

//Description: This function sorts the products by name
//Input: a pointer to the list of products
//Output: -

void sort_prod(List<Product>* products, bool (*compare)(const Product&, const Product&)){
    for (int i = 0; i < products->getSize() - 1; i++) {
        for (int j = i + 1; j < products->getSize(); j++) {
            if (!compare(products->element(i), products->element(j))) {
                Product aux = products->element(i);
                products->update(i, products->element(j));
                products->update(j, aux);
            }
        }
    }
}

bool compareName(const Product& p1, const Product& p2) {
    return p1.getName() < p2.getName();
}

bool comparePrice(const Product& p1, const Product& p2) {
    return p1.getPrice() < p2.getPrice();
}

bool compareNameType(const Product& p1, const Product& p2) {
    if (p1.getName() == p2.getName()) {
        return p1.getType() < p2.getType();
    }
    return p1.getName() < p2.getName();
}

void Service::sortProducts(List<Product>* sortedProducts,int command) {
    //create a copy of the list of products
    //command 1 - sort by name
    //command 2 - sort by price
    //command 3 - sort by name and type
    if (command == 1) {
        sort_prod(sortedProducts, compareName);
    } else if (command == 2) {
        sort_prod(sortedProducts, comparePrice);
    } else if (command == 3) {
        sort_prod(sortedProducts, compareNameType);
    }


}





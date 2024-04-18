//
// Created by White Fox on 3/31/2024.
//

#include "service.h"
#include <iostream>
#include "myexception.h"

int rand(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
    return dist6(rng);
}

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
    int id = 1;
    vector<Product> & products = this->repo.getProducts();
    if(products.empty())
        return id;
    for (const auto& product : products) {
        if (product.getId() != id) {
            return id;
        }
        id++;
    }
    return id;
}

//Description: This function adds a product to the list
//Input: a string representing the name of the product, a string representing the type of the product, a double representing the price of the product, a string representing the producer of the product
//Output: -
void Service::addProduct(string name, string type, double price, string producer) {
    //cout<<"Service addProduct";
    Product p = Product(generateId(), name, type, price, producer);
    p.validate();
    if(this->getPosition(p)!=-1)
        throw RepoException("Product already exists\n");
    this->repo.addProduct(p);

}

//Description: This function removes a product from the list
//Input: an integer representing the id of the product
//Output: -
void Service::removeProduct(int id) {
    //check if id exists
    vector<Product> & products = this->repo.getProducts();
        for (const auto& product : products) {
            if (product.getId() == id) {
                this->repo.removeProduct(id);
                return;
            }
        }
    throw RepoException("Product does not exist\n");

}

//Description: This function updates a product from the list
//Input: an integer representing the id of the product, a string representing the name of the product, a string representing the type of the product, a double representing the price of the product, a string representing the producer of the product
//Output: -
void Service::updateProduct(int id, string name, string type, double price, string producer) {
    Product p = Product(id, name, type, price, producer);
    p.validate();
    if(this->getPosition(p)!=-1)
        throw RepoException("Product already exists\n");
    this->repo.updateProduct(id, p);
}

//Description: This function returns the list of products
//Input: -
//Output: a pointer to the list of products
vector<Product> & Service::getProducts() {
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
void Service::filterProducts(vector<Product>& filteredProducts,std::string name, std::string type, int minPrice, int maxPrice) {
    vector<Product>& products = this->repo.getProducts();
    //use copy_if to filter the products
//    for (const auto& product : *products) {
//        Product p = product;
//        if (p.getName().find(name) != string::npos && p.getType().find(type) != string::npos && p.getPrice() >= minPrice && p.getPrice() <= maxPrice){
//            filteredProducts->push_back(p);
//        }
//    }
    std::copy_if(products.begin(), products.end(), std::back_inserter(filteredProducts), [name, type, minPrice, maxPrice](const Product& p) {
        return p.getName().find(name) != string::npos && p.getType().find(type) != string::npos && p.getPrice() >= minPrice && p.getPrice() <= maxPrice;
    });
}

//Description: This function sorts the products by name
//Input: a pointer to the list of products
//Output: -
void sort_prod(vector<Product>& products, bool (*compare)(const Product&, const Product&)){
    std::sort(products.begin(), products.end(), compare);
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

void Service::sortProducts(vector<Product>& sortedProducts,int command) {
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

//Description: This function returns the position of a product in the list
//Input: a product object
//Output: an integer representing the position of the product in the list
int Service::getPosition(Product &p) {
    return this->repo.getPosition(p);
}

//Description: This function returns the basket
//Input: -
//Output: a pointer to the list of products
vector<Product> & Service::getBasket() {
    return this->repo.getBasketRepo();
}

//Description: This function adds a product to the basket
//Input: an integer representing the id of the product
//Output: -
void Service::addProductToBasket(int id) {
    this->repo.addProductToBasket(id);
}

//Description: This function empties the basket
//Input: -
//Output: -
void Service::emptyBasket() {
    this->repo.emptyBasket();
}

//Description: This function generates a random basket
//Input: an integer representing the number of products in the basket
//Output: -
void Service::generateRandomBasket(int n) {
    vector<Product> & allProducts = this->repo.getProducts();
    for (int i = 0; i < n; i++) {
        int randomIndex = rand(0, allProducts.size() - 1);
        Product & p = allProducts.at(randomIndex);
        this->repo.addProductToBasket(p.getId());
    }
}

//Description: This function exports the basket to a CSV file
//Input: a string representing the filename
//Output: -
void Service::exportBasketToCSV(string filename) {
    vector<Product> & products = this->repo.getBasketRepo();
    std::ofstream file;
    file.open(filename);
    file<<"Id,Name,Type,Price,Producer\n";
    for (const auto& product : products) {
        file << product.getId() << "," << product.getName() << "," << product.getType() << "," << product.getPrice() << "," << product.getProducer() << "\n";
    }
}

//Description: This function exports the basket to a HTML file
//Input: a string representing the filename
//Output: -
void Service::exportBasketToHTML(string filename) {
    vector<Product>  products = this->repo.getBasketRepo();
    std::ofstream file;
    file.open(filename);
    file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Shopping Basket</title>\n</head>\n<body>\n<table border=\"1\">\n<tr>\n<th>Id</th>\n<th>Name</th>\n<th>Type</th>\n<th>Price</th>\n<th>Producer</th>\n</tr>\n";
    for (const auto& product : products) {
        file << "<tr>\n<td>" << product.getId() << "</td>\n<td>" << product.getName() << "</td>\n<td>" << product.getType() << "</td>\n<td>" << product.getPrice() << "</td>\n<td>" << product.getProducer() << "</td>\n</tr>\n";
    }
    file << "</table>\n</body>\n</html>";
}

map<string, vector<Product>> Service::groupProductsByProducer(vector<Product> & products) {
    map<string, vector<Product>> groupedProducts;
    for (const auto& product : products) {
        string producer = product.getProducer();
        if (groupedProducts.find(producer) == groupedProducts.end()) {
            groupedProducts[producer] = vector<Product>();
        }
        groupedProducts[producer].push_back(product);
    }
    return groupedProducts;}





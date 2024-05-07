//
// Created by White Fox on 3/31/2024.
//

#include "ui.h"

#include <cmath>
#include <iostream>
#include "utils.h"
//Description: This function runs the user interface
//Input: -
//Output: -
void UI::run() {

        while (true) {
            try {
            printMenu();
            int command = 0;
            cout << "Enter command: ";
            command = readInt();
            if (command == 0) {
                break;
            }
            switch (command) {
                case 1:
                    addProduct();
                    break;
                case 2:
                    removeProduct();
                    break;
                case 3:
                    updateProduct();
                    break;
                case 4:
                    printProducts();
                    break;
                case 5:
                    undo();
                    break;
                case 6:
                    filterProducts();
                    break;
                case 7:
                    sortProducts();
                    break;
                case 8:
                    groupProductsByProducer();
                    break;
                case 9:
                    addProductToBasket();
                    break;
                case 10:
                    printBasket();
                    break;
                case 11:
                    emptyBasket();
                    break;
                case 12:
                    generateRandomBasket();
                    break;
                case 13:
                    exportBasketToCSV();
                    break;
                case 14:
                    exportBasketToHTML();
                    break;
                default:
                    cout << "Invalid command!" << endl;
                    break;
            }
        }
        catch (exception& e) {
            cout << e.what();
        }
    }

}

//Description: This function prints the menu
//Input: -
//Output: -

void UI::printMenu() {
    cout << "1. Add product" << endl;
    cout << "2. Remove product" << endl;
    cout << "3. Update product" << endl;
    cout << "4. Print products" << endl;
    cout << "5. Undo ur mistakes u dummy" << endl;
    cout << "6. Filter products" << endl;
    cout << "7. Sort products" << endl;
    cout << "8. Group products by producer" << endl;
    cout << "9. Add product to basket" << endl;
    cout << "10. Print basket" << endl;
    cout << "11. Empty basket" << endl;
    cout << "12. Generate random basket" << endl;
    cout << "13. Export basket to CSV" << endl;
    cout << "14. Export basket to HTML" << endl;
    cout << "0. Exit" << endl;
}

//Description: This function adds a product
//Input: -
//Output: -
void UI::addProduct() {
    string name;
    string type;
    double price = NAN;
    string producer;
    cout << "Enter name: ";
    name=readString();
    cout << "Enter type: ";
    type=readString();
    cout << "Enter price: ";
    price = readDouble();
    cout << "Enter producer: ";
    producer=readString();
    try {
        this->service.addProduct(name, type, price, producer);
    } catch (exception& e) {
        cout << e.what();
    }
}

//Description: This function removes a product
//Input: -
//Output: -
void UI::removeProduct() {
    int id = 0;
    cout << "Enter id: ";
    id=readInt();
    try {
        this->service.removeProduct(id);
    }
    catch (exception& e) {
        cout << e.what();
    }
}
//Description: This function updates a product
//Input: -
//Output: -
void UI::updateProduct() {
    int id = 0;
    string name;
    string type;
    double price = NAN;
    string producer;
    cout << "Enter id: ";
    id=readInt();
    cin.ignore();
    cout << "Enter name: ";
    name=readString();
    cout << "Enter type: ";
    type=readString();
    cout << "Enter price: ";
    price = readDouble();
    cout << "Enter producer: ";
    producer=readString();
    try {
        this->service.updateProduct(id,name, type, price, producer);
    } catch (exception& e) {
        cout << e.what();
    }
}

//Description: This function prints the products
//Input: -
//Output: -
void UI::printProducts() {
    cout<< "UI print products" << endl;
    vector<Product> & products = this->service.getProducts();
    //use range based for
    for (auto &product : products) {
        cout << product.toString() << endl;
    }
}

//Description: This function filters the products
//Input: -
//Output: -
void UI::filterProducts() {
    int minPrice = 0,maxPrice = 0;
    string name, type;
    cout << "Enter name(or leave blank): ";
    name=readString();
    cout << "Enter type(or leave blank): ";
    type=readString();
    cout << "Enter min price(or leave blank): ";
    string minPriceString=readString();
    if (minPriceString.empty()) {
        minPrice = -1;
    } else {
        minPrice = stoi(minPriceString);
    }
    cout << "Enter max price(or leave blank): ";
    string maxPriceString=readString();
    if (maxPriceString.empty()) {
        maxPrice = 999999999;
    } else {
        maxPrice = stoi(maxPriceString);
    }
    vector<Product> filteredProducts;
    this->service.filterProducts(filteredProducts,name, type, minPrice, maxPrice);
    for (auto &product : filteredProducts) {
        cout << product.toString() << endl;
    }


}

//Description: This function sorts the products
//Input: -
//Output: -
void UI::sortProducts() {
    cout << "Sort products by:" << endl;
    cout << "1. Name" << endl;
    cout << "2. Price" << endl;
    cout << "3. Name+Type" << endl;
    int command = 0;
    cout << "Enter command: ";
    command= readInt();
    vector<Product> sortedproducts=this->service.getProducts();
    Service::sortProducts(sortedproducts, command);
    for (auto &product : sortedproducts) {
        cout << product.toString() << endl;
    }

}

void UI::groupProductsByProducer() {
    auto products = this->service.getProducts();
    map<string,vector<Product>> groupedProducts = Service::groupProductsByProducer(products);
    for (auto & group : groupedProducts) {
        cout << group.first << endl;
        for (auto &product : group.second) {
            cout << product.toString() << endl;
        }
    }

}

//Description: This function adds a product to the basket
//Input: -
//Output: -
void UI::addProductToBasket() {
    //print all products
    printProducts();
    int id = 0;
    cout << "Enter id: ";
    id=readInt();
    try {
        this->service.addProductToBasket(id);
    } catch (exception& e) {
        cout << e.what();
    }
}

//Description: This function prints the basket
//Input: -
//Output: -
void UI::emptyBasket() {
    this->service.emptyBasket();
}

//Description: This function generates a random basket
//Input: -
//Output: -
void UI::generateRandomBasket() {
    int n = 0;
    cout << "Enter number of products: ";
    n=readInt();
    this->service.generateRandomBasket(n);
}

//Description: This function exports the basket to a CSV file
//Input: -
//Output: -
void UI::exportBasketToCSV() {
    string filename;
    cout << "Enter filename: ";
    filename=readString();
    this->service.exportBasketToCSV(filename);
}

//Description: This function exports the basket to an HTML file
//Input: -
//Output: -
void UI::exportBasketToHTML() {
    string filename;
    cout << "Enter filename: ";
    filename=readString();
    this->service.exportBasketToHTML(filename);
}

//Description: This function prints the basket
//Input: -
//Output: -
void UI::printBasket() {
    vector<Product> & products = this->service.getBasket();
    for (auto &product : products) {
        cout << product.toString() << endl;
    }
}

void UI::undo(){
    try {
        this->service.undo();
    }
    catch(exception& e){
        cout << e.what();
    }
}


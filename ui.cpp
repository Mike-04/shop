//
// Created by White Fox on 3/31/2024.
//

#include "ui.h"
#include <iostream>
#include "utils.h"
UI::UI() {
    this->service = Service();
}

UI::UI(Service service) {
    this->service = service;
}

void UI::run() {
    try {
        while (true) {
            printMenu();
            int command;
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
                    filterProducts();
                    break;
                case 6:
                    sortProducts();
                    break;
                default:
                    cout << "Invalid command!" << endl;
                    break;
            }
        }
    }
    catch (exception& e) {
        cout << e.what();
    }
}

void UI::printMenu() {
    cout << "1. Add product" << endl;
    cout << "2. Remove product" << endl;
    cout << "3. Update product" << endl;
    cout << "4. Print products" << endl;
    cout << "5. Filter products" << endl;
    cout << "6. Sort products" << endl;
    cout << "0. Exit" << endl;
}

void UI::addProduct() {
    string name;
    string type;
    double price;
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

void UI::removeProduct() {
    int id;
    cout << "Enter id: ";
    id=readInt();
    this->service.removeProduct(id);
}

void UI::updateProduct() {
    int id;
    string name;
    string type;
    double price;
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

void UI::printProducts() {
    cout<< "UI print products" << endl;
    List<Product>* products = this->service.getProducts();
    for (int i = 0; i < products->getSize(); i++) {
        cout << products->element(i).toString() << endl;
    }
}

void UI::filterProducts() {
    int minPrice,maxPrice;
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
    List<Product> filteredProducts;
    this->service.filterProducts(&filteredProducts,name, type, minPrice, maxPrice);
    for (int i = 0; i < filteredProducts.getSize(); i++) {
        cout << filteredProducts.element(i).toString() << endl;
    }


}

void UI::sortProducts() {
    cout << "Sort products by:" << endl;
    cout << "1. Name" << endl;
    cout << "2. Price" << endl;
    cout << "3. Name+Type" << endl;
    int command;
    cout << "Enter command: ";
    command= readInt();
    List<Product> sortedproducts=*this->service.getProducts();
    this->service.sortProducts(&sortedproducts, command);
    for (int i = 0; i < sortedproducts.getSize(); i++) {
        cout << sortedproducts.element(i).toString() << endl;
    }

}

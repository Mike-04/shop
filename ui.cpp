//
// Created by White Fox on 3/31/2024.
//

#include "ui.h"
#include <iostream>

UI::UI() {
    this->service = Service();
}

UI::UI(Service service) {
    this->service = service;
}

void UI::run() {
    while (true) {
        printMenu();
        int command;
        cout << "Enter command: ";
        cin >> command;
        cin.ignore();
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
                printProductById();
                break;
            default:
                cout << "Invalid command!" << endl;
                break;
        }
    }
}

void UI::printMenu() {
    cout << "1. Add product" << endl;
    cout << "2. Remove product" << endl;
    cout << "3. Update product" << endl;
    cout << "4. Print products" << endl;
    cout << "0. Exit" << endl;
}

void UI::addProduct() {
    string name;
    string type;
    double price;
    string producer;
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter type: ";
    getline(cin, type);
    cout << "Enter price: ";
    cin >> price;
    cin.ignore();
    cout << "Enter producer: ";
    getline(cin, producer);
    this->service.addProduct(name, type, price, producer);
}

void UI::removeProduct() {
    int id;
    cout << "Enter id: ";
    cin >> id;
    cin.ignore();
    this->service.removeProduct(id);
}

void UI::updateProduct() {
    int id;
    string name;
    string type;
    double price;
    string producer;
    cout << "Enter id: ";
    cin >> id;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter type: ";
    getline(cin, type);
    cout << "Enter price: ";
    cin >> price;
    cin.ignore();
    cout << "Enter producer: ";
    getline(cin, producer);
    this->service.updateProduct(id, name, type, price, producer);
}

void UI::printProducts() {
    cout<< "UI printproducts" << endl;
    vector<Product>* products = this->service.getProducts();
    for (auto & product : *products) {
        cout << product.toString() << endl;
    }
}

void UI::printProductById() {
    int id;
    cout << "Enter id: ";
    cin >> id;
    cin.ignore();
    Product product = this->service.getProductById(id);
    cout << product.toString() << endl;
}

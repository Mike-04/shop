//
// Created by White Fox on 3/31/2024.
//

#ifndef SHOP_UI_H
#define SHOP_UI_H

#endif //SHOP_UI_H


#include "service.h"

class UI {
private:
    Service service;
public:
    UI();
    UI(Service service);
    void run();
    static void printMenu();
    void addProduct();
    void removeProduct();
    void updateProduct();
    void printProducts();
    void printProductById();
};
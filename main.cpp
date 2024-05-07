//
// Created by White Fox on 3/31/2024.
//

#include "tests.h"
#include "ui.h"
#include "repo.h"
#include "service.h"
#include <iostream>

int main() {
    test_all();

    cout<<"Tests passed\n";
    Repository_Map repo = Repository_Map(0);
    //add some products

    Product p1,p2,p3,p4,p5,p6;
    try {
        repo.addProduct(p1 = Product(1, "Laptop", "Electronics", 2000, "Asus"));
        repo.addProduct(p2 = Product(2, "PC", "Electronics", 3000, "Dell"));
        repo.addProduct(p3 = Product(3, "Phone", "Electronics", 1000, "Asus"));
        repo.addProduct(p4 = Product(4, "Tablet", "Electronics", 1500, "Apple"));
        repo.addProduct(p5 = Product(5, "Smartwatch", "Electronics", 500, "Xiaomi"));
        repo.addProduct(p6 = Product(6, "Headphones", "Electronics", 100, "Apple"));
    }
    catch (exception &e) {
        cout << e.what();
    }
    Service service(repo);

    UI ui(service);
    //system("clear");
    ui.run();


    return 0;
}

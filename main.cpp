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
    Repository repo = Repository();
    //add some products
    repo.addProduct(Product(1, "Laptop", "Electronics", 2000, "Asus"));
    repo.addProduct(Product(2, "PC", "Electronics", 3000, "Dell"));
    repo.addProduct(Product(3, "Phone", "Electronics", 1000, "Samsung"));
    repo.addProduct(Product(4, "Tablet", "Electronics", 1500, "Apple"));
    repo.addProduct(Product(5, "Smartwatch", "Electronics", 500, "Xiaomi"));
    repo.addProduct(Product(6, "Headphones", "Electronics", 100, "Sony"));
    Service service = Service(repo);

    UI ui = UI(service);
    system("clear");
    ui.run();

    return 0;
}

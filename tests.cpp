//
// Created by White Fox on 3/31/2024.
//

#include "tests.h"
#include "repo.h"
#include <cassert>
#include <iostream>
#include "domain.h"
#include "service.h"

void test_domain() {
    Product p1 = Product(1, "Laptop", "Electronics", 2000, "Asus");
    assert(p1.getId() == 1);
    assert(p1.getName() == "Laptop");
    assert(p1.getType() == "Electronics");
    assert(p1.getPrice() == 2000);
    assert(p1.getProducer() == "Asus");

    p1.setId(2);
    assert(p1.getId() == 2);

    p1.setName("PC");
    assert(p1.getName() == "PC");

    p1.setType("Electronics");
    assert(p1.getType() == "Electronics");

    p1.setPrice(3000);
    assert(p1.getPrice() == 3000);

    p1.setProducer("Dell");
    assert(p1.getProducer() == "Dell");


    cout << p1.toString() << endl;
    assert(p1.toString() == "2, PC, Electronics, 3000.00, Dell");
}

void test_repo() {
    Repository repo;
    Product p1 = Product(1, "Laptop", "Electronics", 2000, "Asus");
    Product p2 = Product(2, "PC", "Electronics", 3000, "Dell");

    repo.addProduct(p1);
    repo.addProduct(p2);

    assert(repo.getProducts().size() == 2);

    repo.removeProduct(1);
    assert(repo.getProducts().size() == 1);

    assert(repo.getProductById(2).getName() == "PC");
    assert(repo.getProductById(3).getName().empty());


    repo.updateProduct(2 , Product(2, "PC", "Electronics", 4000, "Dell"));
    assert(repo.getProducts()[0].getPrice() == 4000);
}

void test_service() {
    //test service with prebuild repo
    Repository repo;
    Service service(repo);

    service.addProduct("Laptop", "Electronics", 2000, "Asus");
    service.addProduct("PC", "Electronics", 3000, "Dell");

    assert(service.getSize() == 2);

    service.removeProduct(1);

    assert(service.getSize() == 1);

    service.updateProduct(2, "PC", "Electronics", 4000, "Dell");
    assert(service.getProductById(2).getPrice() == 4000);



    //test service with empty repo
    Service service2;
    service2.addProduct("Laptop", "Electronics", 2000, "Asus");
    service2.addProduct("PC", "Electronics", 3000, "Dell");

    assert(service2.getSize() == 2);

    service2.removeProduct(1);
    assert(service2.getSize() == 1);

    assert(service2.getProductById(2).getName() == "PC");


    service2.updateProduct(2, "PC", "Electronics", 4000, "Dell");
    assert(service2.getProductById(2).getPrice() == 4000);

}

void test_all() {
    test_domain();
    test_repo();
    test_service();
    std::cout << "All tests passed!\n";
}

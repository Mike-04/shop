//
// Created by White Fox on 3/31/2024.
//

#include "tests.h"
#include "repo.h"
#include <cassert>
#include <iostream>
#include "domain.h"
#include "service.h"
#include "list.h"

void test_list()
{
    //create a product list
    List<Product> list;
    //create a product
    Product p1 = Product(1, "Laptop", "Electronics", 2000, "Asus");
    //add the product to the list
    list.append(p1);
    //check if the product was added
    assert(list.getSize() == 1);
    //check if the product was added correctly
    assert(list.element(0).getId() == 1);
    assert(list.element(0).getName() == "Laptop");
    assert(list.element(0).getType() == "Electronics");
    assert(list.element(0).getPrice() == 2000);
    assert(list.element(0).getProducer() == "Asus");
    //try updating the product
    Product p2 = Product(2, "PC", "Electronics", 3000, "Dell");
    list.update(0,p2);
    //check if the product was updated correctly
    assert(list.element(0).getId() == 2);
    assert(list.element(0).getName() == "PC");
    assert(list.element(0).getType() == "Electronics");
    assert(list.element(0).getPrice() == 3000);
    assert(list.element(0).getProducer() == "Dell");
    //try inserting a product
    Product p4 = Product(3, "Phone", "Electronics", 1000, "Samsung");
    list.insert(0,p4);
    //check if the product was inserted correctly
    assert(list.element(0).getId() == 3);
    assert(list.element(0).getName() == "Phone");
    assert(list.element(0).getType() == "Electronics");
    assert(list.element(0).getPrice() == 1000);
    assert(list.element(0).getProducer() == "Samsung");
    //try removing the product
    Product p3=list.remove(1);
    //check if the product was removed correctly
    assert(p3.getId() == 2);
    assert(p3.getName() == "PC");
    assert(p3.getType() == "Electronics");
    assert(p3.getPrice() == 3000);
    assert(p3.getProducer() == "Dell");
    //check if the product was removed
    assert(list.getSize() == 1);
    //remove one more product
    list.remove(0);
    //check if the list is empty
    assert(list.getSize() == 0);
    //try removing from an empty list
    list.remove(0);
    //try forcing resize
    for (int i = 0; i < 100; i++)
    {
        Product p = Product(i, "Laptop", "Electronics", 2000, "Asus");
        list.append(p);
    }
    assert(list.getSize() == 100);
    //delete the list
    List<Product> list2;
    //try forcing resize with insert
    for (int i = 0; i < 100; i++)
    {
        Product p = Product(i, "Laptop", "Electronics", 2000, "Asus");
        list2.insert(0,p);
    }
    assert(list.getSize() == 100);
    //test = operator
    list = list2;
    assert(list.getSize() == 100);
    assert(list2.getSize() == 100);
    //try copying a list in the same list
    list = list;
    assert(list.getSize() == 100);

    //try a list of numbers
    List<int> list3;
    for (int i = 0; i < 100; i++)
    {
        list3.append(i);
    }
    assert(list3.getSize() == 100);
    for (int i = 0; i < 100; i++)
    {
        assert(list3.element(i) == i);
    }
    for (int i = 0; i < 100; i++)
    {
        list3.remove(0);
    }
    assert(list3.getSize() == 0);
}

void test_domain() {
    Product p1 = Product(69, "Laptop", "Electronics", 2000, "Asus");
    assert(p1.getId() == 69);
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

    assert(p1.toString() == "2, PC, Electronics, 3000.00, Dell");

    //test operator=
    Product p2 = Product(3, "Phone", "Electronics", 1000, "Samsung");

    //test operator==
    assert(p1 == p1);
    assert(!(p1 == p2));

    //test validate
    try {
        Product p3 = Product(4, "Phone", "Electronics", -1000, "Samsung");
        p3.validate();
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
}

void test_repo() {
    Repository repo;
    Product p1 = Product(1, "Laptop", "Electronics", 2000, "Asus");
    Product p2 = Product(2, "PC", "Electronics", 3000, "Dell");

    repo.addProduct(p1);
    assert(repo.getSize() == 1);
    repo.addProduct(p2);
    assert(repo.getSize()== 2);

    repo.removeProduct(1);
    assert(repo.getSize() == 1);

    assert(repo.getProductById(2).getName() == "PC");
    assert(repo.getProductById(3).getName().empty());

    Product p3 = Product(2, "PC", "Electronics", 4000, "Dell");

    repo.updateProduct(2 , p3);
    assert(repo.getProducts()[0].getPrice() == 4000);

    //test get position
    assert(repo.getPosition(p3) == 0);
}

void test_repo_map() {
    Repository_Map repo(0);
    Product p1 = Product(1, "Laptop", "Electronics", 2000, "Asus");
    Product p2 = Product(2, "PC", "Electronics", 3000, "Dell");

    repo.addProduct(p1);
    assert(repo.getSize() == 1);
    repo.addProduct(p2);
    assert(repo.getSize() == 2);

    repo.removeProduct(1);
    assert(repo.getSize() == 1);

    assert(repo.getProductById(2).getName() == "PC");
    assert(repo.getProductById(3).getName().empty());

    Product p3 = Product(2, "PC", "Electronics", 4000, "Dell");

    repo.updateProduct(2 , p3);
    assert(repo.getProducts().at(0).getPrice() == 4000);

    //test get position
    assert(repo.getPosition(p3) == 0);
}

void test_service() {
    //test service with prebuild repo
    Repository repo;
    Service service(repo);

    service.addProduct("Laptop", "Electronics", 2000, "Asus");
    service.addProduct("PC", "Electronics", 3000, "Dell");

//    for (auto & product : *service.getProducts()) {
//        cout<< product.toString() << endl;
//    }

    //try adding a product that already exists
    try {
        service.addProduct("PC", "Electronics", 3000, "Dell");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    //try adding a product with negative price
    try {
        service.addProduct("Phone", "Electronics", -1000, "Samsung");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    assert(service.getSize() == 2);

    service.removeProduct(1);

    //try removing a product that does not exist
    try {
        service.removeProduct(1);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    assert(service.getSize() == 1);

    service.updateProduct(2, "PC", "Electronics", 4000, "Dell");

//    for (auto & product : *service.getProducts()) {
//        cout<< product.toString() << endl;
//    }

    //try updating a product that already exists
    try {
        service.updateProduct(2, "PC", "Electronics", 4000, "Dell");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    //try updating a product with negative price
    try {
        service.updateProduct(2, "PC", "Electronics", -4000, "Dell");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    assert(service.getProductById(2).getPrice() == 4000);

    //test get products
    vector<Product> products = service.getProducts();
    assert(products.size() == 1);

    //test service with empty repo
    Repository repo2;
    Service service2(repo2);
    service2.addProduct("Laptop", "Electronics", 2000, "Asus");
    service2.addProduct("PC", "Electronics", 3000, "Dell");

    assert(service2.getSize() == 2);

    service2.removeProduct(1);
    assert(service2.getSize() == 1);

    assert(service2.getProductById(2).getName() == "PC");


    service2.updateProduct(2, "PC", "Electronics", 4000, "Dell");
    assert(service2.getProductById(2).getPrice() == 4000);

    //test get position
    Product p1 = Product(2, "PC", "Electronics", 4000, "Dell");
    assert(service2.getPosition(p1) == 0);


    //test filter
    Repository repo3;
    Service service3(repo3);
    service3.addProduct("Phone", "Gadget", 1000, "Samsung");
    service3.addProduct("Laptop", "Electronics", 2000, "Asus");
    service3.addProduct("PC", "Electronics", 3000, "Dell");


    vector<Product> filtered;
    service3.filterProducts(filtered,"", "Elec", 0, 2000);
    assert(filtered.size() == 1);

    //test sort
    vector<Product> sorted=service3.getProducts();
    Service::sortProducts(sorted, 1);
    assert(sorted.at(0).getName() == "Laptop");
    assert(sorted.at(1).getName() == "PC");
    assert(sorted.at(2).getName() == "Phone");

    sorted=service3.getProducts();
    Service::sortProducts(sorted, 2);
    assert(sorted.at(0).getName() == "Phone");
    assert(sorted.at(1).getName() == "Laptop");
    assert(sorted.at(2).getName() == "PC");


    service3.addProduct("PC", "Gadget", 3000, "Dell");

    sorted=service3.getProducts();
    Service::sortProducts(sorted, 3);
    assert(sorted.at(0).getName() == "Laptop");
    assert(sorted.at(1).getName() == "PC");
    assert(sorted.at(2).getName() == "PC");
    assert(sorted.at(3).getName() == "Phone");

    //test add product to basket
    service3.addProductToBasket(1);
    assert(service3.getBasket().size() == 1);

    //test empty basket
    service3.emptyBasket();
    assert(service3.getBasket().empty());


    //test generate random basket
    service3.generateRandomBasket(2);
    assert(service3.getBasket().size() == 2);

    //test export basket to csv
    service3.exportBasketToCSV("test.csv");

    //test export basket to html
    service3.exportBasketToHTML("test.html");

    //test generate id
    assert(service3.generateId() == 5);
    service3.removeProduct(1);
    assert(service3.generateId() == 1);

    //test group products by producer
    Repository repo4;
    Service service4(repo4);
    service4.addProduct("Phone", "Gadget", 1000, "Samsung");
    service4.addProduct("Laptop", "Electronics", 2000, "Asus");
    service4.addProduct("PC", "Electronics", 3000, "Dell");
    service4.addProduct("PC", "Gadget", 3000, "Dell");
    map<string,vector<Product>> grouped = Service::groupProductsByProducer(service4.getProducts());
    assert(grouped.size() == 3);
    assert(grouped["Samsung"].size() == 1);
    assert(grouped["Asus"].size() == 1);
    assert(grouped["Dell"].size() == 2);


    Repository_Map repo5(0);
    Service service5(repo5);
    service5.addProduct("Phone", "Gadget", 1000, "Samsung");
    service5.addProduct("Laptop", "Electronics", 2000, "Asus");
    service5.addProduct("PC", "Electronics", 3000, "Dell");
    service5.addProduct("PC", "Gadget", 3000, "Dell");

    //test basket repo
    service5.addProductToBasket(1);
    service5.addProductToBasket(2);
    service5.addProductToBasket(3);

    assert(service5.getBasket().size() == 3);

    service5.emptyBasket();

    assert(service5.getBasket().empty());

    service5.generateRandomBasket(2);

    assert(service5.getBasket().size() == 2);

    service5.exportBasketToCSV("test.csv");

    service5.exportBasketToHTML("test.html");
}

void test_undo()
{
    Repository repo;
    Service service(repo);
    //test add product
    service.addProduct("Laptop", "Electronics", 2000, "Asus");
    service.addProduct("PC", "Electronics", 3000, "Dell");
    assert(service.getSize() == 2);
    service.undo();
    assert(service.getSize() == 1);
    service.undo();
    assert(service.getSize() == 0);
    //try undo when there are no actions
    try{
        service.undo();
    }
    catch (const std::exception& e) {
        assert(true);
    }
    //test remove product
    service.addProduct("Laptop", "Electronics", 2000, "Asus");
    service.addProduct("PC", "Electronics", 3000, "Dell");
    service.removeProduct(1);
    assert(service.getSize() == 1);
    service.undo();
    assert(service.getSize() == 2);
    //check if the product was added back
    assert(service.getProductById(1).getName() == "Laptop");
    //test update product
    service.updateProduct(1, "PC", "Electronics", 4000, "Dell");
    assert(service.getProductById(1).getPrice() == 4000);
    service.undo();
    assert(service.getProductById(1).getPrice() == 2000);
}

void test_all() {
    test_list();
    test_domain();
    test_repo();
    test_repo_map();
    test_service();
    test_undo();
}

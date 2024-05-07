//
// Created by White Fox on 3/31/2024.
//

#ifndef SHOP_REPO_H
#define SHOP_REPO_H

#endif //SHOP_REPO_H
#pragma once
#include "domain.h"
#include <vector>
#include "list.h"
#include <map>
#include <random>
#include <algorithm>
#include "myexception.h"


class Repo{
public:
    virtual void addProduct(Product &p) = 0;
    virtual void removeProduct(int id) = 0;
    virtual void updateProduct(int id, Product &p) = 0;
    virtual vector<Product> & getProducts() = 0;
    virtual Product getProductById(int id) = 0;
    virtual unsigned long getPosition(Product &p) = 0;
    virtual unsigned long getSize() = 0;
    virtual ~Repo() = default;
    virtual void addProductToBasket(int id) = 0;
    virtual void emptyBasket() = 0;
    virtual vector<Product> & getBasketRepo() = 0;
};

class Repository : public Repo{
private:
    vector<Product> products_list;
    vector<Product> basket;
public:
    Repository();
    void addProduct(Product &p) override;
    void removeProduct(int id) override;
    void updateProduct(int id, Product &p) override;
    vector<Product> & getProducts() override;
    Product getProductById(int id) override;
    unsigned long getPosition(Product &p) override;
    unsigned long getSize() override;
    ~Repository() override;
    void addProductToBasket(int id) override;
    void emptyBasket() override;
    vector<Product> & getBasketRepo() override;
};

class Repository_Map: public Repo{
private:
    map<int,Product> products_map;
    vector<Product> basket;
    double maximus_crapatos = 0;
public:
    explicit Repository_Map(double maximus_crapatos);
    void addProduct(Product &p) override;
    void removeProduct(int id) override;
    void updateProduct(int id, Product &p) override;
    vector<Product> & getProducts() override;
    Product getProductById(int id) override;
    unsigned long getPosition(Product &p) override;
    unsigned long getSize() override;
    ~Repository_Map() override;
    void addProductToBasket(int id) override;
    void emptyBasket() override;
    vector<Product> & getBasketRepo() override;
    static int randomus_crapatos();
    void procesus_destructos() const;
};
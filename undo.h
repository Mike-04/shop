#pragma once
#include "domain.h"
#include "repo.h"

class UndoAction {
public:
    virtual void executeUndo() = 0;
    virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
    private:
        Product addedProduct;
        Repo &repo;
    public:
        UndoAdd(Repo &repo, const Product &p) : addedProduct{p}, repo{repo} {}
        void executeUndo() override {
            repo.removeProduct(addedProduct.getId());
        }

};

class UndoRemove : public UndoAction {
private:
    Product removedProduct;
    Repo &repo;
public:
    UndoRemove(Repo &repo, const Product &p) : removedProduct{p}, repo{repo} {}
    void executeUndo() override {
        repo.addProduct(removedProduct);
    }

};

class UndoUpdate : public UndoAction {
private:
    Product updatedProduct;
    Repo &repo;
public:
    UndoUpdate(Repo &repo,const Product &p) : updatedProduct{p}, repo{repo} {}
    void executeUndo() override {
        repo.updateProduct(updatedProduct.getId(), updatedProduct);
    }

};

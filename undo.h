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
        Repository &repo;
    public:
        UndoAdd(Repository &repo, const Product &p) : repo{repo}, addedProduct{p} {}
        void executeUndo() override {
            repo.removeProduct(addedProduct.getId());
        }

};

class UndoRemove : public UndoAction {
private:
    Product removedProduct;
    Repository &repo;
public:
    UndoRemove(Repository &repo, const Product &p) : repo{repo}, removedProduct{p} {}
    void executeUndo() override {
        repo.addProduct(removedProduct);
    }

};

class UndoUpdate : public UndoAction {
private:
    Product updatedProduct;
    Repository &repo;
public:
    UndoUpdate(Repository &repo, const Product &p) : repo{repo}, updatedProduct{p} {}
    void executeUndo() override {
        repo.updateProduct(updatedProduct.getId(), updatedProduct);
    }

};

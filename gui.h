#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include "service.h"
#include <QDebug>
#include <QMessageBox>

class GUI: public QWidget{
friend class FilterWindow;
private:
    Service& service;
    int current_id=-1;
protected:
    string nameStr;
    string typeStr;
    int minPriceVal;
    int maxPriceVal;
public:
    GUI(Service& service);
    void initGUI();

    QHBoxLayout* MainBox = new QHBoxLayout;
    QListWidget *ProductList;
    QVBoxLayout* Commands = new QVBoxLayout;
    QFormLayout* ProductDetails = new QFormLayout;

    QHBoxLayout* Actions = new QHBoxLayout;
    QPushButton *AddButton;
    QPushButton *RemoveButton;
    QPushButton *UpdateButton;
    QPushButton *UndoButton;

    QHBoxLayout *SortActions = new QHBoxLayout;
    QPushButton *SortNameButton;
    QPushButton *SortPriceButton;
    QPushButton *SortNameTypeButton;
    QPushButton *SortIdButton;

    QPushButton *FilterButton = new QPushButton("Filter");
    QPushButton *GroupButton = new QPushButton("Group");

    QPushButton *AddToBasketButton = new QPushButton("Add to basket");
    QPushButton *ViewBasketButton = new QPushButton("View basket");


    QLineEdit *Name;
    QLineEdit *Type;
    QLineEdit *Price;
    QLineEdit *Producer;

    void connectSignals();
    void populateList();
    void addProduct();
    void removeProduct();
    void updateProduct();
    void undo();
    void sortProducts(int command);
    void handleFilter();
    void setFilter(string name, string type, int minPrice, int maxPrice);
    void groupProducts();
    void addProductToBasket();
    void viewBasket();

public slots:
    void handleclickedItem();
};

class FilterWindow: public QWidget{
friend class GUI;
public:
    FilterWindow(GUI& gui);
    QVBoxLayout* MainBox = new QVBoxLayout;
    QFormLayout* FilterDetails = new QFormLayout;
    QLineEdit *Name;
    QLineEdit *Type;
    QLineEdit *MinPrice;
    QLineEdit *MaxPrice;
    QPushButton *FilterButton = new QPushButton("Filter");
private:
    GUI& gui;
    void filter();
};
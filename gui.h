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
#include <QFileDialog>
#include <QTableWidget>
#include "observer.h"
#include <QPainter>

class GUI: public QWidget{
friend class FilterWindow;
private:
    Service& service;
    int current_id=-1;
protected:
    string nameStr;
    string typeStr;
    int minPriceVal{};
    int maxPriceVal{};
public:
    GUI(Service& service);
    void initGUI();

    QHBoxLayout* MainBox = new QHBoxLayout;
    QListWidget *ProductList{};
    QTableWidget *ProductTable{};
    QVBoxLayout* Commands = new QVBoxLayout;
    QFormLayout* ProductDetails = new QFormLayout;

    QHBoxLayout* Actions = new QHBoxLayout;
    QPushButton *AddButton{};
    QPushButton *RemoveButton{};
    QPushButton *UpdateButton{};
    QPushButton *UndoButton{};

    QHBoxLayout *SortActions = new QHBoxLayout;
    QPushButton *SortNameButton{};
    QPushButton *SortPriceButton{};
    QPushButton *SortNameTypeButton{};
    QPushButton *SortIdButton{};

    QPushButton *FilterButton = new QPushButton("Filter");
    QPushButton *GroupButton = new QPushButton("Group");
    QPushButton *GenerateRandomBasketButton = new QPushButton("Generate random basket");
    QPushButton *AddToBasketButton = new QPushButton("Add to basket");
    QPushButton *EmptyBasketButton = new QPushButton("Empty basket");
    QPushButton *ViewBasketButton = new QPushButton("View basket");

    QVBoxLayout* CountButtons = new QVBoxLayout;




    QLineEdit *Name{};
    QLineEdit *Type{};
    QLineEdit *Price{};
    QLineEdit *Producer{};

    void connectSignals();
    void populateList();
    void populateTable();
    void addProduct();
    void removeProduct();
    void updateProduct();
    void undo();
    void sortProducts(int command);
    void handleFilter();
    void setFilter(string name, string type, int minPrice, int maxPrice);
    void groupProducts();
    void addProductToBasket();
    void emptyBasket();
    void viewBasket();
    void addCountButtons();
    void removeCountButtons();
    void generateRandomBasket();

public slots:
    void handleclickedItem();
    void handleTableclickedItem();
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

class BasketWindow: public QWidget , public Observer{
friend class GUI;
private:
    Service &service;
public:
    void update() override;
    explicit BasketWindow(Service& service);
    QVBoxLayout* MainBox = new QVBoxLayout;
    QListWidget *BasketList;
    QPushButton *ExportCSVButton = new QPushButton("Export to CSV");
    QPushButton *ExportHTMLButton = new QPushButton("Export to HTML");
    QPushButton *EmptyButton = new QPushButton("Empty basket");
    void populateList();
    void exportToCSV();
    void exportToHTML();
};

class GenerateRandomBasketWindow: public QWidget{
friend class GUI;
private:
    Service &service;
public:
    GenerateRandomBasketWindow(Service& service);
    QVBoxLayout* MainBox = new QVBoxLayout;
    QFormLayout* BasketDetails = new QFormLayout;
    QLineEdit *Count;
    QPushButton *GenerateButton = new QPushButton("Generate");
    void generate();
};

//overide paintEvent to draw a image



class BasketWindowReadOnly: public QWidget, public Observer, public QPainter{
    friend class GUI;
private:
    Service &service;
public:
    void update() override;
    explicit BasketWindowReadOnly(Service& service);
    void paintEvent(QPaintEvent *event) override;
    QVBoxLayout* MainBox = new QVBoxLayout;
};
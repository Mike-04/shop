#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include "service.h"


class GUI: public QWidget{
private:
    Service& service;

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
    QLineEdit *Name;
    QLineEdit *Type;
    QLineEdit *Price;
    QLineEdit *Producer;
};
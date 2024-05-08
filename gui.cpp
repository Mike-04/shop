
#include "gui.h"



void GUI::initGUI() {
    //add list
    setLayout(MainBox);
    this->ProductList = new QListWidget{};
    MainBox->addWidget(ProductList);
    //add buttons

    this->Actions = new QHBoxLayout{};
    this->AddButton = new QPushButton("Add");
    this->RemoveButton = new QPushButton("Remove");
    this->UpdateButton = new QPushButton("Update");
    Actions->addWidget(AddButton);
    Actions->addWidget(RemoveButton);
    Actions->addWidget(UpdateButton);

    //add form
    this->ProductDetails = new QFormLayout{};
    this->Name = new QLineEdit{};
    this->Type = new QLineEdit{};
    this->Price = new QLineEdit{};
    this->Producer = new QLineEdit{};

    ProductDetails->addRow("Name", Name);
    ProductDetails->addRow("Type", Type);
    ProductDetails->addRow("Price", Price);
    ProductDetails->addRow("Producer", Producer);

    Commands->addLayout(ProductDetails);
    Commands->addLayout(Actions);
    MainBox->addLayout(Commands);




}

GUI::GUI(Service& service) : service{ service } {
    initGUI();
}
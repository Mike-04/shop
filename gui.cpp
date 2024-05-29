
#include "gui.h"



void GUI::initGUI() {
    //add list
    setLayout(MainBox);

    //make the left panel

    QVBoxLayout *LeftPanel = new QVBoxLayout{};
    MainBox->addLayout(LeftPanel);

    this->ProductList = new QListWidget{};
    LeftPanel->addWidget(ProductList);
    this->ProductTable = new QTableWidget{};
    LeftPanel->addWidget(ProductTable);
    //add buttons

    AddButton= new QPushButton("Add");
    RemoveButton= new QPushButton("Remove");
    UpdateButton= new QPushButton("Update");
    UndoButton= new QPushButton("Undo");

    SortNameButton= new QPushButton("Sort by name");
    SortPriceButton= new QPushButton("Sort by price");
    SortNameTypeButton= new QPushButton("Sort by name and type");
    SortIdButton= new QPushButton("Default");

    // Find the maximum width required by any button
    int maxWidth = std::max({AddButton->sizeHint().width(), RemoveButton->sizeHint().width(),
                             UpdateButton->sizeHint().width(), UndoButton->sizeHint().width(),
                             SortNameButton->sizeHint().width(), SortPriceButton->sizeHint().width(),
                             SortNameTypeButton->sizeHint().width(), SortIdButton->sizeHint().width()});

    // Set all buttons to the same width
    AddButton->setFixedWidth(maxWidth);
    RemoveButton->setFixedWidth(maxWidth);
    UpdateButton->setFixedWidth(maxWidth);
    UndoButton->setFixedWidth(maxWidth);
    SortNameButton->setFixedWidth(maxWidth);
    SortPriceButton->setFixedWidth(maxWidth);
    SortNameTypeButton->setFixedWidth(maxWidth);
    SortIdButton->setFixedWidth(maxWidth);

    // Add buttons to layouts
    Actions->addWidget(AddButton);
    Actions->addWidget(RemoveButton);
    Actions->addWidget(UpdateButton);
    Actions->addWidget(UndoButton);

    SortActions->addWidget(SortNameButton);
    SortActions->addWidget(SortPriceButton);
    SortActions->addWidget(SortNameTypeButton);
    SortActions->addWidget(SortIdButton);

    // Add layouts to the panel
    LeftPanel->addLayout(Actions);
    LeftPanel->addLayout(SortActions);
    //add form
    QVBoxLayout *RightPanel = new QVBoxLayout{};
    MainBox->addLayout(RightPanel);
    this->ProductDetails = new QFormLayout{};
    this->Name = new QLineEdit{};
    this->Type = new QLineEdit{};
    this->Price = new QLineEdit{};
    this->Producer = new QLineEdit{};

    ProductDetails->addRow("Name", Name);
    ProductDetails->addRow("Type", Type);
    ProductDetails->addRow("Price", Price);
    ProductDetails->addRow("Producer", Producer);

    RightPanel->addLayout(ProductDetails);
    RightPanel->addWidget(FilterButton);
    RightPanel->addWidget(GroupButton);
    RightPanel->addWidget(AddToBasketButton);
    RightPanel->addWidget(EmptyBasketButton);
    RightPanel->addWidget(ViewBasketButton);
    RightPanel->addWidget(GenerateRandomBasketButton);

    MainBox->addLayout(CountButtons);

}

GUI::GUI(Service& service) : service{service} {
    initGUI();
    connectSignals();
    populateList();
    populateTable();
}

void GUI::connectSignals(){
    QObject::connect(AddButton, &QPushButton::clicked, this, &GUI::addProduct);
    QObject::connect(RemoveButton, &QPushButton::clicked, this, &GUI::removeProduct);
    QObject::connect(UpdateButton, &QPushButton::clicked, this, &GUI::updateProduct);
    QObject::connect(UndoButton, &QPushButton::clicked, this, &GUI::undo);
    QObject::connect(ProductList, &QListWidget::itemClicked, this, &GUI::handleclickedItem);
    QObject::connect(ProductTable, &QTableWidget::itemClicked, this, &GUI::handleTableclickedItem);
    QObject::connect(SortNameButton, &QPushButton::clicked, [this](){sortProducts(1);});
    QObject::connect(SortPriceButton, &QPushButton::clicked, [this](){sortProducts(2);});
    QObject::connect(SortNameTypeButton, &QPushButton::clicked, [this](){sortProducts(3);});
    QObject::connect(SortIdButton, &QPushButton::clicked, [this](){populateList();populateTable();});
    QObject::connect(FilterButton, &QPushButton::clicked, this, &GUI::handleFilter);
    QObject::connect(GroupButton, &QPushButton::clicked, this, &GUI::groupProducts);
    QObject::connect(AddToBasketButton, &QPushButton::clicked, this, &GUI::addProductToBasket);
    QObject::connect(ViewBasketButton, &QPushButton::clicked, this, &GUI::viewBasket);
    QObject::connect(GenerateRandomBasketButton, &QPushButton::clicked, this, &GUI::generateRandomBasket);
    QObject::connect(EmptyBasketButton, &QPushButton::clicked, this, &GUI::emptyBasket);

}

void GUI::handleclickedItem() {
    string product = ProductList->currentItem()->text().toStdString();
    try {
        this->current_id = stoi(product.substr(0, product.find(',')));
    }
    catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    qDebug() << "Current id: " << current_id;
    Product p = this->service.getProductById(current_id);
    Name->setText(QString::fromStdString(p.getName()));
    Type->setText(QString::fromStdString(p.getType()));
    Price->setText(QString::number(p.getPrice()));
    Producer->setText(QString::fromStdString(p.getProducer()));
}

void GUI::handleTableclickedItem() {
    int row = ProductTable->currentRow();
    int id = ProductTable->item(row, 0)->text().toInt();
    this->current_id = id;
    Product p = this->service.getProductById(id);
    Name->setText(QString::fromStdString(p.getName()));
    Type->setText(QString::fromStdString(p.getType()));
    Price->setText(QString::number(p.getPrice()));
    Producer->setText(QString::fromStdString(p.getProducer()));
}

void GUI::populateList() {
    qDebug() << "Populating list";
    ProductList->clear();
    for (auto &product : this->service.getProducts()) {
        qDebug() << QString::fromStdString(product.toString());
        ProductList->addItem(QString::fromStdString(product.toString()));
    }
    removeCountButtons();
}

void GUI::populateTable() {
    qDebug() << "Populating table";
    ProductTable->clear();
    ProductTable->setColumnCount(5);
    ProductTable->setHorizontalHeaderLabels(QStringList() << "Id" << "Name" << "Type" << "Price" << "Producer");
    ProductTable->setRowCount(this->service.getSize());
    int row = 0;
    for (auto &product : this->service.getProducts()) {
        ProductTable->setItem(row, 0, new QTableWidgetItem(QString::number(product.getId())));
        ProductTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(product.getName())));
        ProductTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(product.getType())));
        ProductTable->setItem(row, 3, new QTableWidgetItem(QString::number(product.getPrice())));
        ProductTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(product.getProducer())));
        row++;
    }
    removeCountButtons();
}

void GUI::addProduct() {
    string name = Name->text().toStdString();
    string type = Type->text().toStdString();
    double price = Price->text().toDouble();
    string producer = Producer->text().toStdString();
    try {
        this->service.addProduct(name, type, price, producer);
        populateList();
        populateTable();
    }
    catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void GUI::removeProduct() {
    int id = this->current_id;
    try {
        this->service.removeProduct(id);
        populateList();
        populateTable();
    }
    catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void GUI::updateProduct() {
    int id = this->current_id;
    string name = Name->text().toStdString();
    string type = Type->text().toStdString();
    double price = Price->text().toDouble();
    string producer = Producer->text().toStdString();
    try {
        this->service.updateProduct(id, name, type, price, producer);
        populateList();
        populateTable();
    }
    catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void GUI::undo() {
    try {
        this->service.undo();
        populateList();
        populateTable();
    }
    catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void GUI::sortProducts(int command) {
    vector<Product> sortedProducts = this->service.getProducts();
    Service::sortProducts(sortedProducts, command);
    ProductList->clear();
    for (auto &product : sortedProducts) {
        ProductList->addItem(QString::fromStdString(product.toString()));
    }
    //populateTable();
    ProductTable->clear();
    ProductTable->setColumnCount(5);
    ProductTable->setHorizontalHeaderLabels(QStringList() << "Id" << "Name" << "Type" << "Price" << "Producer");
    ProductTable->setRowCount(sortedProducts.size());
    int row = 0;
    for (auto &product : sortedProducts) {
        ProductTable->setItem(row, 0, new QTableWidgetItem(QString::number(product.getId())));
        ProductTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(product.getName())));
        ProductTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(product.getType())));
        ProductTable->setItem(row, 3, new QTableWidgetItem(QString::number(product.getPrice())));
        ProductTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(product.getProducer())));
        row++;
    }


}

void GUI::handleFilter() {
    //display the filter window
    FilterWindow* filterWindow = new FilterWindow(*this);
    filterWindow->show();
}

void GUI::setFilter(string name, string type, int minPrice, int maxPrice) {
    this->nameStr = name;
    this->typeStr = type;
    this->minPriceVal = minPrice;
    this->maxPriceVal = maxPrice;
    vector<Product> filteredProducts;
    this->service.filterProducts(filteredProducts, name, type, minPrice, maxPrice);
    ProductList->clear();
    for (auto &product : filteredProducts) {
        ProductList->addItem(QString::fromStdString(product.toString()));
    }
    //populateTable();
    ProductTable->clear();
    ProductTable->setColumnCount(5);
    ProductTable->setHorizontalHeaderLabels(QStringList() << "Id" << "Name" << "Type" << "Price" << "Producer");
    ProductTable->setRowCount(filteredProducts.size());
    int row = 0;
    for (auto &product : filteredProducts) {
        ProductTable->setItem(row, 0, new QTableWidgetItem(QString::number(product.getId())));
        ProductTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(product.getName())));
        ProductTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(product.getType())));
        ProductTable->setItem(row, 3, new QTableWidgetItem(QString::number(product.getPrice())));
        ProductTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(product.getProducer())));
        row++;
    }
}

void GUI::groupProducts() {
    addCountButtons();
    map<string, vector<Product>> groupedProducts = Service::groupProductsByProducer(this->service.getProducts());
    //display the grouped products in the list leaving a space between each group
    ProductList->clear();
    for (auto &group : groupedProducts) {
        ProductList->addItem(QString::fromStdString(group.first));
        for (auto &product : group.second) {
            ProductList->addItem(QString::fromStdString(product.toString()));
        }
    }
    //populateTable();
    ProductTable->clear();
    ProductTable->setColumnCount(5);
    ProductTable->setHorizontalHeaderLabels(QStringList() << "Id" << "Name" << "Type" << "Price" << "Producer");
    //calculate the number of rows needed
    int rows = 0;
    for (auto &group : groupedProducts) {
        rows += group.second.size() + 1;
    }
    ProductTable->setRowCount(rows);
    int row = 0;
    for (auto &group : groupedProducts) {
        ProductTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(group.first)));
        row++;
        for (auto &product : group.second) {
            ProductTable->setItem(row, 0, new QTableWidgetItem(QString::number(product.getId())));
            ProductTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(product.getName())));
            ProductTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(product.getType())));
            ProductTable->setItem(row, 3, new QTableWidgetItem(QString::number(product.getPrice())));
            ProductTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(product.getProducer())));
            row++;
        }
    }
}

void GUI::addCountButtons(){
    removeCountButtons();
    //dinamically add buttons for each product type from the grouped products
    //each button will display a message box with the number of products of that type
    map<string, vector<Product>> groupedProducts = Service::groupProductsByProducer(this->service.getProducts());
    for (auto &group : groupedProducts) {
        QPushButton *button = new QPushButton(QString::fromStdString(group.first));
        CountButtons->addWidget(button);
        connect(button, &QPushButton::clicked, [this, group](){
            QMessageBox::information(this, "Number of products", QString::number(group.second.size()));
        });
    }
}

void GUI::removeCountButtons() {
    QLayoutItem *child;
    while ((child = CountButtons->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}

void GUI::addProductToBasket() {
    int id = this->current_id;
    try {
        this->service.addProductToBasket(id);
        //show basket in qDebug
        qDebug() << "Basket:";
        for (auto &product : this->service.getBasket()) {
            qDebug() << QString::fromStdString(product.toString());
        }
    }
    catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void GUI::emptyBasket() {
    this->service.emptyBasket();
}

void GUI::viewBasket() {
    auto* basketWindow = new BasketWindow(this->service);
    basketWindow->show();
    auto* basketWindowReadOnly = new BasketWindowReadOnly(this->service);
    basketWindowReadOnly->show();
}

void GUI::generateRandomBasket() {
    //open random basket window
    auto* randomBasketWindow = new GenerateRandomBasketWindow(this->service);
    randomBasketWindow->show();
}

FilterWindow::FilterWindow(GUI& gui) : gui{gui} {
    setLayout(MainBox);
    auto *NameLabel = new QLabel("Name");
    auto TypeLabel = new QLabel("Type");
    auto *MinPriceLabel = new QLabel("Min Price");
    auto *MaxPriceLabel = new QLabel("Max Price");

    Name= new QLineEdit{};
    Type= new QLineEdit{};
    MinPrice= new QLineEdit{};
    MaxPrice= new QLineEdit{};

    FilterDetails->addRow(NameLabel, Name);
    FilterDetails->addRow(TypeLabel, Type);
    FilterDetails->addRow(MinPriceLabel, MinPrice);
    FilterDetails->addRow(MaxPriceLabel, MaxPrice);

    MainBox->addLayout(FilterDetails);

    FilterButton= new QPushButton("Filter");
    MainBox->addWidget(FilterButton);
    connect(FilterButton, &QPushButton::clicked, this, &FilterWindow::filter);
}

void FilterWindow::filter() {
    string name = Name->text().toStdString();
    string type = Type->text().toStdString();
    //check if the price fields are empty
    if (MinPrice->text().isEmpty()) {
        MinPrice->setText("-1");
    }
    if (MaxPrice->text().isEmpty()) {
        MaxPrice->setText("999999999");
    }
    int minPrice = MinPrice->text().toInt();
    int maxPrice = MaxPrice->text().toInt();
    gui.setFilter(name, type, minPrice, maxPrice);
    close();
}

BasketWindow::BasketWindow(Service& service) : service{service} {
    service.addObserver(this);
    setLayout(MainBox);
    BasketList = new QListWidget{};
    MainBox->addWidget(BasketList);
    populateList();

    EmptyButton= new QPushButton("Empty basket");
    MainBox->addWidget(EmptyButton);
    connect(EmptyButton, &QPushButton::clicked, [this](){
        this->service.emptyBasket();
        close();
    });

    ExportCSVButton= new QPushButton("Export to CSV");
    MainBox->addWidget(ExportCSVButton);
    connect(ExportCSVButton, &QPushButton::clicked, this, &BasketWindow::exportToCSV);

    ExportHTMLButton= new QPushButton("Export to HTML");
    MainBox->addWidget(ExportHTMLButton);
    connect(ExportHTMLButton, &QPushButton::clicked, this, &BasketWindow::exportToHTML);
}

void BasketWindow::populateList() {
    for (auto &product : this->service.getBasket()) {
        BasketList->addItem(QString::fromStdString(product.toString()));
    }
}

void BasketWindow::exportToCSV() {
    string filename = "Basket.csv";
    this->service.exportBasketToCSV(filename);
}

void BasketWindow::exportToHTML() {
    string filename = "Basket.html";
    this->service.exportBasketToHTML(filename);
}

void BasketWindow::update() {
    BasketList->clear();
    populateList();
}


GenerateRandomBasketWindow::GenerateRandomBasketWindow(Service& service) : service{service} {
    setLayout(MainBox);
    Count = new QLineEdit{};
    BasketDetails->addRow("Count", Count);
    MainBox->addLayout(BasketDetails);
    auto *GenerateButton = new QPushButton("Generate random basket");
    MainBox->addWidget(GenerateButton);
    connect(GenerateButton, &QPushButton::clicked, this, &GenerateRandomBasketWindow::generate);
}

void GenerateRandomBasketWindow::generate() {
    int n = Count->text().toInt();
    this->service.generateRandomBasket(n);
    close();
}

BasketWindowReadOnly::BasketWindowReadOnly(Service &service) : service(service) {
    service.addObserver(this);
    setLayout(MainBox);
    //set the window size
    setFixedSize(600, 600);

}

void BasketWindowReadOnly::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.setPen(Qt::black);
    for (auto &product : this->service.getBasket()) {
        //draw a circle for each product at a random position
        //get window size
        int x = rand(0,this->width() - 100);
        int y = rand(0,this->height() - 50);
        painter.drawEllipse(x, y, 100, 50);
        //draw the product name inside the circle
        painter.drawText(x, y, 100, 50, Qt::AlignCenter, QString::fromStdString(product.getName()));
    }
}

void BasketWindowReadOnly::update() {
    repaint();
}

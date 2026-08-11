#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto switchPage = [this](int index) {
        ui->stackedWidget->setCurrentIndex(index);
    };

    connect(ui->pushButton, &QPushButton::clicked, this, [=]{switchPage(1);});
    connect(ui->pushButton_2, &QPushButton::clicked, this, [=]{switchPage(0);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

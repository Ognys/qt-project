#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textmanager.h"

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

    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::writeText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeText() {
    TextManager::WriteInFile(ui->plainTextEdit->toPlainText());
}

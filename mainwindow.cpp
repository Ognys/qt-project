#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textmanager.h"

#include <QStandardPaths>
#include <QFile>

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
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [=](int index){if(index == 1) MainWindow::showNotes();});

    ui->verticalLayout_9->setAlignment(Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeText() {
    TextManager::WriteInFile(ui->setTitleNote->text(),ui->plainTextEdit->toPlainText());
}

void MainWindow::switchText(QString fileName) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QFile f(path + "/" + fileName);
    bool isOpen = f.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!isOpen) {
        qDebug() << "Не удалось открыть " << fileName;
    }

    QString text = QString::fromUtf8(f.readAll());
    ui->plainTextEdit->setPlainText(text);
}


void MainWindow::showNotes() {
    QStringList list = TextManager::getFiles();

    while(auto item = ui->verticalLayout_9->takeAt(0))
    {
        if(item->widget())
            item->widget()->deleteLater();
        delete item;
    }

    for(int i = 0; i < list.size(); i++)
    {
        QString buttonName = list[i];
        auto *button = new QPushButton(buttonName.remove(".txt"), this);
        ui->verticalLayout_9->addWidget(button);
        connect(button, &QPushButton::clicked, this, [=]{switchText(list[i]);});
    }
}
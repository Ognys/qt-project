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

    ui->setTitleNote->setEnabled(false);
    ui->plainTextEdit->setEnabled(false);
    ui->verticalLayout_9->setContentsMargins(0, 0, 0, 0);

    auto switchPage = [this](int index) {
        ui->stackedWidget->setCurrentIndex(index);
    };

    connect(ui->pushButton, &QPushButton::clicked, this, [=]{switchPage(1);});
    connect(ui->pushButton_2, &QPushButton::clicked, this, [=]{switchPage(0);});

    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::writeText);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [=](int index){if(index == 1) MainWindow::showNotes();});
    connect(ui->checkBox, &QCheckBox::checkStateChanged, this, &MainWindow::editNote);

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
    ui->setTitleNote->setText(fileName.remove(".txt"));
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

        button->setFixedSize(150, 50);

        button->setStyleSheet(
                "QPushButton {"
                "    border: 1.3px solid gray;"
                "    border-bottom: none;"
                "    border-left: none;"
                "}"
                "QPushButton:hover {"
                "    background-color: lightgray;"
                "}"
                );

        if(i == list.size() - 1) {
            button->setStyleSheet(
                "QPushButton { border: 1.3px solid gray;"
                "border-left: none;"
                "}"
                "QPushButton:hover {"
                "    background-color: lightgray;"
                "}"
                );
        }


        ui->verticalLayout_9->addWidget(button);
        connect(button, &QPushButton::clicked, this, [=]{switchText(list[i]);});
    }

    switchText(list[0]);
}

void MainWindow::on_pushButton_5_clicked() {
    ui->setTitleNote->clear();
    ui->plainTextEdit->clear();
}

void MainWindow::editNote() {
    bool readOnly = ui->checkBox->isChecked();

    ui->setTitleNote->setEnabled(readOnly);
    ui->plainTextEdit->setEnabled(readOnly);
}
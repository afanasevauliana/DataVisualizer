#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadDataFromFile();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDataFromFile() {
    QFile file("data.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла!";
        return;
    }

    QTextStream in(&file);
    ui->tableWidget->setRowCount(0);  // Очистка таблицы

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < fields.size(); ++col) {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(fields[col]));
        }
    }
    file.close();
}

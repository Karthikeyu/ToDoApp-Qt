#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+ "\\toDoFile.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this, "Fail issue", file.errorString());

    }

    QTextStream InStream(&file);

    while(!InStream.atEnd())
    {
        QListWidgetItem* item = new QListWidgetItem(InStream.readLine(), ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->listWidget->addItem(item);
        ui->txtInput->setFocus();
    }

    file.close();
}

MainWindow::~MainWindow()
{


    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+ "\\toDoFile.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::WriteOnly | QIODevice::Truncate))
    {
       QMessageBox::information(this, "Fail issue", file.errorString());
    }else
    {

        QTextStream OutStream(&file);


        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            OutStream << ui->listWidget->item(i)->text() << "\n";
        }

    }

    file.close();
    delete ui;
}

void MainWindow::on_btnAddTask_clicked()
{

    if(ui->txtInput->text().trimmed().isEmpty())
    {   QMessageBox::warning(this, "Input Error", "Please enter valid Input!");

    }else
    {
        QListWidgetItem* item = new QListWidgetItem(ui->txtInput->text(), ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->listWidget->addItem(item);
        ui->txtInput->clear();
        ui->txtInput->setFocus();
    }

}


void MainWindow::on_btnRemove_clicked()
{
    auto item = ui->listWidget->takeItem(ui->listWidget->currentRow());

    ui->listWidget->removeItemWidget(item);
    delete item;
}


void MainWindow::on_btnRemoveAll_clicked()
{
    ui->listWidget->clear();
}


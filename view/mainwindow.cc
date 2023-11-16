#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(700, 600);
    lab_w_ = new LabirintWidget(this);
    lab_w_->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}




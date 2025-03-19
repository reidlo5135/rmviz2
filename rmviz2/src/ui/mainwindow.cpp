#include "ui/mainwindow.hpp"
#include "ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->rmviz2_ = std::make_shared<net::wavem::viz::RMViz2>();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
#ifndef UI_MAINWINDOW_HPP
#define UI_MAINWINDOW_HPP

#include <QMainWindow>
#include <QApplication>

#include "presentation/node.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    net::wavem::viz::RMViz2::SharedPtr rmviz2_;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif
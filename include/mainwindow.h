#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "define_container/define_container.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

    private:
        Ui::MainWindow * ui;
        QWidget * q_central_widget_ptr;
        QLayout * q_layout_ptr;
        QPushButton * q_mqtt_subsribe_push_btn_ptr;
        void on_push_btn_mqtt_subscribe_created();
        void on_push_btn_mqtt_subscribe_clicked();
        void register_q_push_btn(QPushButton * q_push_btn_ptr);
    public:
        MainWindow(QWidget * parent = nullptr);
        ~MainWindow();
};

#endif
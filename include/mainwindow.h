#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "define_container/define_container.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

    private:
        Ui::MainWindow * ui;
        QWidget * q_central_widget_ptr_;
        QLayout * q_layout_ptr_;
        QPushButton * q_mqtt_subsribe_push_btn_ptr_;
        void set_up_stylesheet();
        void on_mqtt_subscribe_push_btn_created();
        void on_mqtt_subscribe_push_btn_clicked();
        void register_q_push_btn(QPushButton * q_push_btn_ptr);
    public:
        explicit MainWindow(QWidget * parent = nullptr);
        virtual ~MainWindow();
};

#endif
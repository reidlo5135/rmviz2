#include "include/mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget * q_parent_ptr)
: QMainWindow(q_parent_ptr), 
ui(new Ui::MainWindow) {
    ui->setupUi(this);

    q_central_widget_ptr_ = ui->centralwidget;
    q_layout_ptr_ = q_central_widget_ptr_->layout();

    if (!q_layout_ptr_) {
        q_layout_ptr_ = new QVBoxLayout(q_central_widget_ptr_);
        q_central_widget_ptr_->setLayout(q_layout_ptr_);
    }

    this->set_up_stylesheet();
    this->on_mqtt_subscribe_push_btn_created();
    this->register_q_push_btn(q_mqtt_subsribe_push_btn_ptr_);
}

MainWindow::~MainWindow() {
    delete q_central_widget_ptr_;
    delete q_layout_ptr_;
    delete ui;
}

void MainWindow::set_up_stylesheet() {
    
}

void MainWindow::on_mqtt_subscribe_push_btn_created() {
    q_mqtt_subsribe_push_btn_ptr_ = new QPushButton(Q_MQTT_SUBSCRIBE_PUSH_BTN_TITLE);
    q_mqtt_subsribe_push_btn_ptr_->setObjectName("q_mqtt_subscribe_push_btn");
    q_mqtt_subsribe_push_btn_ptr_->setStyleSheet(Q_MQTT_SUBSCRIBE_PUSH_BTN_CSS);
    q_mqtt_subsribe_push_btn_ptr_->setFixedSize(Q_MQTT_SUBSCRIBE_PUSH_BTN_WIDTH, Q_MQTT_SUBSCRIBE_PUSH_BTN_HEIGHT);
    connect(q_mqtt_subsribe_push_btn_ptr_, &QPushButton::clicked, this, &MainWindow::on_mqtt_subscribe_push_btn_clicked);
}

void MainWindow::on_mqtt_subscribe_push_btn_clicked() {
    qDebug("q push button clicked");
}

void MainWindow::register_q_push_btn(QPushButton * q_push_btn_ptr) {
    q_layout_ptr_->addWidget(q_push_btn_ptr);
}
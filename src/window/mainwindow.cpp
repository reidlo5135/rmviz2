#include "include/mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget * q_parent_ptr)
: QMainWindow(q_parent_ptr), 
ui(new Ui::MainWindow) {
    ui->setupUi(this);

    q_central_widget_ptr = ui->centralwidget;
    q_layout_ptr = q_central_widget_ptr->layout();

    if (!q_layout_ptr) {
        q_layout_ptr = new QVBoxLayout(ui->centralwidget);
        q_central_widget_ptr->setLayout(q_layout_ptr);
    }

    this->on_push_btn_mqtt_subscribe_created();
    this->register_q_push_btn(q_mqtt_subsribe_push_btn_ptr);
}

MainWindow::~MainWindow() {
    delete q_central_widget_ptr;
    delete q_layout_ptr;
    delete ui;
}

void MainWindow::on_push_btn_mqtt_subscribe_created() {
    q_mqtt_subsribe_push_btn_ptr = new QPushButton(Q_PUSH_BTN_MQTT_SUBSCRIBE_TITLE);
    q_mqtt_subsribe_push_btn_ptr->setObjectName("q_push_btn_mqtt_subscribe");
    q_mqtt_subsribe_push_btn_ptr->setStyleSheet(Q_PUSH_BTN_MQTT_SUBSCRIBE_CSS_CLASS_NAME);
    q_mqtt_subsribe_push_btn_ptr->setFixedSize(Q_PUSH_BTN_MQTT_SUBSCRIBE_WIDTH, Q_PUSH_BTN_MQTT_SUBSCRIBE_HEIGHT);
    connect(q_mqtt_subsribe_push_btn_ptr, &QPushButton::clicked, this, &MainWindow::on_push_btn_mqtt_subscribe_clicked);
}

void MainWindow::on_push_btn_mqtt_subscribe_clicked() {
    qDebug("q push button clicked");
}

void MainWindow::register_q_push_btn(QPushButton * q_push_btn_ptr) {
    q_layout_ptr->addWidget(q_push_btn_ptr);
}
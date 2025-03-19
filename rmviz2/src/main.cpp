#include "ui/mainwindow.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    rclcpp::shutdown();
    return a.exec();
}
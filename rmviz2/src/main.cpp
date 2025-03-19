#include "ui/dashboard.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    const auto &node = std::make_shared<net::wavem::viz::Node>();

    std::thread ros_thread([node]()
    {
        rclcpp::executors::MultiThreadedExecutor executor;
        executor.add_node(node);
        executor.spin();
    });

    QApplication a(argc, argv);
    net::wavem::viz::DashBoard w(nullptr, node);
    w.show();

    int ret = a.exec();

    rclcpp::shutdown();

    if (ros_thread.joinable())
    {
        ros_thread.join();
    }

    return ret;
}
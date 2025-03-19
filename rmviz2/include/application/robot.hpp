#ifndef APPLICATION_ROBOT_HPP
#define APPLICATION_ROBOT_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

#include "domain/robot.hpp"

using std::placeholders::_1;

namespace net::wavem::viz
{
    class RobotService final
    {
    private:
        rclcpp::Node::SharedPtr node_;
        Robot::SharedPtr robot_;

        rclcpp::CallbackGroup::SharedPtr scan_subscription_cb_group_;
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_subscription_;
        void scan_subscription_cb(sensor_msgs::msg::LaserScan::SharedPtr scan);

    public:
        explicit RobotService(const rclcpp::Node::SharedPtr &node_ = nullptr);
        virtual ~RobotService();
        [[nodiscard]] Robot::SharedPtr get__robot() const;

    public:
        using SharedPtr = std::shared_ptr<RobotService>;

    };
}

#endif
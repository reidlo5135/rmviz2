#include "application/robot.hpp"

using namespace net::wavem::viz;

RobotService::RobotService(const rclcpp::Node::SharedPtr &node)
    : node_(node)
{
    this->robot_ = std::make_shared<Robot>();

    this->scan_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions scan_subscription_opts;
    scan_subscription_opts.callback_group = this->scan_subscription_cb_group_;
    this->scan_subscription_ = this->node_->create_subscription<sensor_msgs::msg::LaserScan>(
        "/scan",
        rclcpp::QoS(rclcpp::KeepLast(1)),
        std::bind(&RobotService::scan_subscription_cb, this, _1),
        scan_subscription_opts);
}

RobotService::~RobotService() = default;

void
RobotService::scan_subscription_cb(sensor_msgs::msg::LaserScan::SharedPtr scan)
{
    this->robot_->set__scan(scan);
}

Robot::SharedPtr
RobotService::get__robot() const
{
    if (!this->robot_) {
        RCLCPP_ERROR(this->node_->get_logger(), "Robot is nullptr!");
    }
    return this->robot_;
}
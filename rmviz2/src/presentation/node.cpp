#include "presentation/node.hpp"

using namespace net::wavem::viz;

Node::Node()
    : rclcpp::Node(NODE_NAME)
{
    this->node_ = std::shared_ptr<rclcpp::Node>(this, [](rclcpp::Node *){});

    this->can_service_ = std::make_shared<CanService>(this->node_);
    this->robot_service_ = std::make_shared<RobotService>(this->node_);
}

Node::~Node()
{
}

Robot::SharedPtr
Node::get__robot() const
{
    return this->robot_service_->get__robot();
}
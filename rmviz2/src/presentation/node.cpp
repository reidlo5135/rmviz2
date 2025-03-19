#include "presentation/node.hpp"

using namespace net::wavem::viz;

RMViz2::RMViz2()
    : Node(NODE_NAME)
{
    this->node_ = std::shared_ptr<rclcpp::Node>(this, [](rclcpp::Node *){});
}

RMViz2::~RMViz2()
{
}
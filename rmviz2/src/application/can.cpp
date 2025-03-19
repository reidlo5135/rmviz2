#include "application/can.hpp"

using namespace net::wavem::viz;

CanService::CanService(const rclcpp::Node::SharedPtr &node)
    : node_(node)
{

}

CanService::~CanService() = default;
#ifndef PRESENTATION_NODE_HPP
#define PRESENTATION_NODE_HPP

#include <rclcpp/rclcpp.hpp>

#include "domain/robot.hpp"
#include "application/can.hpp"
#include "application/robot.hpp"

#define NODE_NAME "rmviz2"

namespace net::wavem::viz
{
    class Node : public rclcpp::Node
    {
    private:
        rclcpp::Node::SharedPtr node_;
        CanService::SharedPtr can_service_;
        RobotService::SharedPtr robot_service_;

    public:
        explicit Node();
        virtual ~Node();
        [[nodiscard]] Robot::SharedPtr get__robot() const;

    public:
        using SharedPtr = std::shared_ptr<Node>;
    };
}

#endif
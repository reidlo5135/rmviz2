#ifndef PRESENTATION_NODE_HPP
#define PRESENTATION_NODE_HPP

#include <rclcpp/rclcpp.hpp>

#include "application/can.hpp"

#define NODE_NAME "rmviz2"

namespace net::wavem::viz
{
    class RMViz2 : public rclcpp::Node
    {
    private:
        rclcpp::Node::SharedPtr node_;

    public:
        explicit RMViz2();
        virtual ~RMViz2();

    public:
        using SharedPtr = std::shared_ptr<RMViz2>;
    };
}

#endif
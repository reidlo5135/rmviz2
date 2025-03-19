#ifndef APPLICATION_CAN_HPP
#define APPLICATION_CAN_HPP

#include <rclcpp/rclcpp.hpp>

namespace net::wavem::viz
{
    class CanService final
    {
    private:
        rclcpp::Node::SharedPtr node_;


    public:
        explicit CanService(const rclcpp::Node::SharedPtr &node = nullptr);
        virtual ~CanService();

    public:
        using SharedPtr = std::shared_ptr<CanService>;
    };
}

#endif
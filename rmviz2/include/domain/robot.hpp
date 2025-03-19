#ifndef DOMAIN_ROBOT_HPP
#define DOMAIN_ROBOT_HPP

#include <memory>
#include <sensor_msgs/msg/laser_scan.hpp>

namespace net::wavem::viz
{
    class Robot final
    {
    private:
        sensor_msgs::msg::LaserScan::SharedPtr scan_;
    public:
        explicit Robot();
        virtual ~Robot();

        [[nodiscard]] sensor_msgs::msg::LaserScan::SharedPtr get__scan() const;
        void set__scan(const sensor_msgs::msg::LaserScan::SharedPtr &scan);

    public:
        using SharedPtr = std::shared_ptr<Robot>;
    };
}

#endif
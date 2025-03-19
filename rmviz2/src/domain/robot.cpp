#include "domain/robot.hpp"

using namespace net::wavem::viz;

Robot::Robot()
    : scan_(nullptr)
{
}

Robot::~Robot() = default;

sensor_msgs::msg::LaserScan::SharedPtr
Robot::get__scan() const
{
    return this->scan_;
}

void
Robot::set__scan(const sensor_msgs::msg::LaserScan::SharedPtr &scan)
{
    this->scan_ = scan;
}
#ifndef UI_ROBOT_VIEW_HPP
#define UI_ROBOT_VIEW_HPP

#include <any>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <map>

#include <rclcpp/rclcpp.hpp>
#include <Eigen/Dense>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QWidget>
#include <cmath>
#include <QTimer>
#include <QDebug>
#include <QCursor>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>
#include <QObject>
#include <QPainter>
#include <QVector2D>
#include <QVector3D>
#include <QtCore>

#include "domain/robot.hpp"
#include "presentation/node.hpp"

namespace net::wavem::viz
{
    typedef struct
    {
        double x;
        double y;
    } Point;

    class RobotView final : public QGraphicsView
    {
        Q_OBJECT
    private:
        QGraphicsScene *scene_;
        QTimer *robotTimer_;
        Node::SharedPtr node_;
        std::vector<QGraphicsEllipseItem *> scan_points_;
        std::map<int, std::vector<Point>> laser_data_scene_;
        std::map<int, QColor> location_to_color_;
        QRectF bounding_rect_;

        void addGrid();
        void updateScanData(const sensor_msgs::msg::LaserScan::SharedPtr &scan);
        void id2color(int id, int &R, int &G, int &B);
        void drawLaser(QPainter *painter, int id, std::vector<Point>);
        void computeBoundRect(const std::map<int, std::vector<Point>> &laser_scan);
        void SetBoundingRect(QRectF rect) { bounding_rect_ = rect; }
    private slots:
        void robotTimerCallback();

    public:
        explicit RobotView(QWidget *parent = nullptr, const Node::SharedPtr &node = nullptr);
        virtual ~RobotView();
    };
}

#endif
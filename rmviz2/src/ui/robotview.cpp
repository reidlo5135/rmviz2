#include "ui/robotview.hpp"

using namespace net::wavem::viz;

RobotView::RobotView(QWidget *parent, const Node::SharedPtr &node)
    : QGraphicsView(parent)
    , node_(node)
{
    this->scene_ = new QGraphicsScene(this);
    this->setScene(this->scene_);
    this->setRenderHint(QPainter::Antialiasing);
    this->addGrid();

    this->robotTimer_ = new QTimer(this);
    connect(this->robotTimer_, &QTimer::timeout, this, &RobotView::robotTimerCallback);
    this->robotTimer_->start(100);
}

RobotView::~RobotView() = default;

void
RobotView::addGrid()
{
    const int gridSize = 50;
    const int width = 600;
    const int height = 600;

    QPen pen(Qt::gray);
    pen.setStyle(Qt::DashLine);

    for (int x = 0; x < width; x += gridSize)
    {
        this->scene_->addLine(x, 0, x, height, pen);
    }

    for (int y = 0; y < height; y += gridSize)
    {
        this->scene_->addLine(0, y, width, y, pen);
    }
}

void
RobotView::id2color(int id, int &R, int &G, int &B)
{
    #define LocationColorJudge(JudegeId, color) \
    if (id == JudegeId)                         \
    {                                           \
        R = color & 0xFF0000;                   \
        R >>= 16;                               \
        G = color & 0x00FF00;                   \
        G >>= 8;                                \
        B = color & 0x0000FF;                   \
    }
    LocationColorJudge(0, 0xFF6347);
    LocationColorJudge(1, 0xff6600);
    LocationColorJudge(2, 0x228B22);
    LocationColorJudge(3, 0x800000);
    LocationColorJudge(4, 0x8A2BE2);
    LocationColorJudge(5, 0xF4A460);
    LocationColorJudge(6, 0xD2B48C);
    LocationColorJudge(7, 0xADFF2F);
    LocationColorJudge(8, 0xFF00FF);
    LocationColorJudge(9, 0x00FF00);
    LocationColorJudge(-1, 0x40E0D0);
    LocationColorJudge(-2, 0x2F4F4F);
    LocationColorJudge(-3, 0x00BFFF);
    LocationColorJudge(-4, 0x708090);
    LocationColorJudge(-5, 0x00008B);
    LocationColorJudge(-6, 0x006633);
    LocationColorJudge(-7, 0x003300);
    LocationColorJudge(-8, 0xDA70D6);
    LocationColorJudge(-9, 0x9900cc);
    LocationColorJudge(-20, 0x551A8B);
    LocationColorJudge(10, 0x00FF33);
}

void
RobotView::drawLaser(QPainter *painter, int id, std::vector<Point> data)
{
    QColor color;

    if (!location_to_color_.count(id))
    {
        int r, g, b;
        this->id2color(id, r, g, b);
        color = QColor(r, g, b);
    }
    else
    {
        color = location_to_color_[id];
    }

    painter->setPen(QPen(color));

    for (auto one_point : data)
    {
        QPointF point = QPointF(one_point.x, one_point.y);
        std::cout<<"point:"<<point.x() <<" "<<point.y()<<std::endl;
        painter->drawPoint(point);
    }
}

void
RobotView::computeBoundRect(const std::map<int, std::vector<Point>> &laser_scan)
{

    float xmax = -std::numeric_limits<float>::infinity();
    float xmin = std::numeric_limits<float>::infinity();
    float ymax = -std::numeric_limits<float>::infinity();
    float ymin = std::numeric_limits<float>::infinity();

    // 각 레이저 데이터를 기반으로 경계 계산
    for (const auto &[id, points] : laser_scan)
    {
        if (points.empty()) continue;

        for (const auto &point : points)
        {
            xmax = std::max(xmax, static_cast<float>(point.x));
            xmin = std::min(xmin, static_cast<float>(point.x));
            ymax = std::max(ymax, static_cast<float>(point.y));
            ymin = std::min(ymin, static_cast<float>(point.y));
        }
    }

    // 경계 설정
    QRectF bounding_rect(xmin, ymin, xmax - xmin, ymax - ymin);
    SetBoundingRect(bounding_rect);

    // 경계에 맞게 씬의 영역을 설정
    this->scene_->setSceneRect(bounding_rect);

    // float xmax, xmin, ymax, ymin;

    // for (auto [id, points] : laser_scan)
    // {
    //     if (points.empty())
    //     continue;

    //     xmax = xmin = points[0].x;
    //     ymax = ymin = points[0].y;

    //     for (int i = 1; i < points.size(); ++i)
    //     {
    //         Point p = points[i];
    //         xmax = xmax > p.x ? xmax : p.x;
    //         xmin = xmin < p.x ? xmin : p.x;
    //         ymax = ymax > p.y ? ymax : p.y;
    //         ymin = ymin < p.y ? ymin : p.y;
    //     }
    // }
    // SetBoundingRect(QRectF(0, 0, xmax, ymax));
}

void
RobotView::updateScanData(const sensor_msgs::msg::LaserScan::SharedPtr &scan)
{
    QMetaObject::invokeMethod(this, [this, scan]()
    {
        for (auto *point : scan_points_)
        {
            this->scene_->removeItem(point);
            delete point;
        }
        this->scan_points_.clear();

        // 레이저 데이터를 저장할 변수
        std::map<int, std::vector<Point>> laser_scan_data;

        for (size_t i = 0; i < scan->ranges.size(); ++i)
        {
            float angle = scan->angle_min + i * scan->angle_increment;
            float r = scan->ranges[i];
            float x = r * cos(angle);
            float y = r * sin(angle);

            // 레이저 데이터 포인트 추가
            Point p = {x, y};
            laser_scan_data[0].push_back(p); // id는 0으로 고정 (하나의 데이터만 처리하는 경우)

            // 그래픽 아이템으로 추가
            QGraphicsEllipseItem *point = new QGraphicsEllipseItem(x - 2, y - 2, 4, 4);
            point->setBrush(Qt::red);
            this->scan_points_.push_back(point);
            this->scene_->addItem(point);
        }

        // 경계 계산 후 업데이트
        this->computeBoundRect(laser_scan_data);
    }, Qt::QueuedConnection);

    // if (!scan)
    //     return;

    // for (auto child : this->scene_->items())
    // {
    //     delete child;
    // }

    // float angle = scan->angle_min;
    // RCLCPP_INFO(this->node_->get_logger(), "Scan angle : %f", angle);
    // for (size_t i = 0; i < scan->ranges.size(); ++i)
    // {
    //     float range = scan->ranges[i];
    //     if (std::isnan(range) || range <= scan->range_min || range >= scan->range_max)
    //     {
    //         angle += scan->angle_increment;
    //         continue;
    //     }

    //     float x = range * cos(angle);
    //     float y = range * sin(angle);
    //     angle += scan->angle_increment;

    //     QGraphicsEllipseItem *point = new QGraphicsEllipseItem(-0.05, -0.05, 0.1, 0.1);
    //     point->setPos(x, y);
    //     point->setBrush(Qt::red);
    //     this->scene_->addItem(point);
    // }
}

void
RobotView::robotTimerCallback()
{
    if (this->node_->get__robot() != nullptr)
    {
        const auto &scan = this->node_->get__robot()->get__scan();

        if (!scan)
        {
            RCLCPP_ERROR(this->node_->get_logger(), "LaserScan data is nullptr");
            return;
        }

        RCLCPP_INFO(this->node_->get_logger(), "RobotTimerCallback Range Size : %ld", scan->ranges.size());
        this->updateScanData(scan);
    }
    else
    {
        return;
    }
}
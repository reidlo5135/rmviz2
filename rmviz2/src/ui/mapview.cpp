#include "ui/mapview.hpp"

using namespace net::wavem::viz;

MapView::MapView(QWidget *parent, const Node::SharedPtr &node)
    : QGraphicsView(parent)
    , node_(node)
{
    this->scene_ = new QGraphicsScene(this);
    this->setScene(this->scene_);

    QString imagePath = QDir::homePath() + "/RobotData/maps/mgc/test-1_2.bmp";
    QPixmap map(imagePath);

    if (map.isNull())
    {
        fprintf(stderr, "Map is Null\n");
    }
    else
    {
        this->scene_->addPixmap(map);
        this->setFixedSize(map.size());
    }

    QGraphicsPixmapItem *mapItem = new QGraphicsPixmapItem(map);
    this->scene_->addItem(mapItem);
}

MapView::~MapView()
{
    delete this->scene_;
}
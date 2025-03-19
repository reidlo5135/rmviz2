#ifndef UI_MAP_VIEW_HPP
#define UI_MAP_VIEW_HPP

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDir>
#include <QGraphicsPixmapItem>

#include "domain/robot.hpp"
#include "presentation/node.hpp"

namespace net::wavem::viz
{
    class MapView final : public QGraphicsView
    {
        Q_OBJECT
    private:
        QGraphicsScene *scene_;
        Node::SharedPtr node_;

    public:
        explicit MapView(QWidget *parent = nullptr, const Node::SharedPtr &node = nullptr);
        virtual ~MapView();

    };
}

#endif
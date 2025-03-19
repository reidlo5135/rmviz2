#ifndef UI_DASHBOARD_HPP
#define UI_DASHBOARD_HPP

#include <QMainWindow>
#include <QApplication>
#include <QHBoxLayout>
#include <QHeaderView>

#include "ui/mapview.hpp"
#include "ui/robotview.hpp"
#include "presentation/node.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace net::wavem::viz
{
    class DashBoard : public QMainWindow
    {
        Q_OBJECT
    private:
        Ui::MainWindow *ui_;
        net::wavem::viz::Node::SharedPtr node_;
        QTimer *rcl_timer_;

        QWidget *centralWidget_;
        QHBoxLayout *layout_;
        MapView *mapView_;
        RobotView *robotView_;
        void setMainViewLayout();

    public:
        DashBoard(QWidget *parent = nullptr, net::wavem::viz::Node::SharedPtr node = nullptr);
        ~DashBoard();
    };
}

#endif
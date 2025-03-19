#include "ui/dashboard.hpp"
#include "ui/ui_dashboard.h"

using namespace net::wavem::viz;

DashBoard::DashBoard(QWidget *parent, net::wavem::viz::Node::SharedPtr node)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    this->ui_->setupUi(this);

    QHeaderView *headerView = new QHeaderView(Qt::Horizontal);
    headerView->setSectionResizeMode(QHeaderView::ResizeToContents);
    headerView->setSelectionBehavior(QAbstractItemView::SelectRows);
    headerView->setCascadingSectionResizes(false);
    headerView->setMinimumHeight(this->size().height() / 6);
    headerView->setMinimumWidth(this->size().width() / 6);

    this->node_ = node;

    this->setWindowTitle("RMViz2[*]");
    this->setFixedSize(1600, 800);

    this->setMainViewLayout();
}

DashBoard::~DashBoard()
{
    delete this->ui_;
    rclcpp::shutdown();
}

void
DashBoard::setMainViewLayout()
{
    this->centralWidget_ = new QWidget(this);
    this->setCentralWidget(this->centralWidget_);

    this->layout_ = new QHBoxLayout();
    this->layout_->setSpacing(10);
    this->layout_->setContentsMargins(10, 10, 10, 10);

    this->mapView_ = new MapView(this->centralWidget_, this->node_);
    this->robotView_ = new RobotView(this->centralWidget_, this->node_);

    this->layout_->addWidget(this->mapView_, 1);
    this->layout_->addWidget(this->robotView_, 1);
    this->centralWidget_->setLayout(this->layout_);
}
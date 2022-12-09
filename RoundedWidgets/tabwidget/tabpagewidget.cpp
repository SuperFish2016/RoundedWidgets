#include "tabpagewidget.h"
#include <QVBoxLayout>
#include <QGraphicsView>

TabPageWidget::TabPageWidget(QWidget* parent)
    : QWidget(parent)
{
    m_toolBar = new ToolBar(this);
    m_toolBar->setFixedHeight(50);

    m_view = new QGraphicsView;
    m_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_view->setStyleSheet("background-color:gray;");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_toolBar);
    layout->addWidget(m_view);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

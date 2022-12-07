#include "tabpagewidget.h"
#include <QVBoxLayout>
TabPageWidget::TabPageWidget(QWidget* parent)
    : QWidget(parent)
{
    m_toolBar = new ToolBar(this);
    m_toolBar->setFixedHeight(50);

    m_centralWidget = new QWidget;
    m_centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_centralWidget->setStyleSheet("background-color:gray;");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_toolBar);
    layout->addWidget(m_centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

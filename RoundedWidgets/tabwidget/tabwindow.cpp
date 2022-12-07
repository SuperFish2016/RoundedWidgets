#include "tabwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QTabBar>
#include <QSizeGrip>
#include "windowcontrolbuttons.h"
TabWindow::TabWindow(QWidget *parent)
    :QWidget(parent)
{
    m_tabWidget = new TabWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_tabWidget);
    m_sizeGripWidget = new QSizeGrip(this);
    layout->addWidget(m_sizeGripWidget, 0, Qt::AlignBottom | Qt::AlignRight);

    layout->setContentsMargins(5, 5, 5 ,5);
    this->setLayout(layout);

    createWindowControlButtons();

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(1200, 800);
}

void TabWindow::resizeEvent(QResizeEvent *ev)
{
    m_controlButtons->setFixedSize(QSize(90, 30));
    m_controlButtons->move(QPoint(ev->size().width() - 90, 0));
    m_tabWidget->tabBar()->setMaximumWidth(ev->size().width() - 110);
    QWidget::resizeEvent(ev);
}

void TabWindow::createWindowControlButtons()
{
    m_controlButtons = new WindowControlButtons(this);
    connect(m_controlButtons, &WindowControlButtons::minimizedButtonClicked, [=](){
        this->showMinimized();
    });

    connect(m_controlButtons, &WindowControlButtons::maximizedButtonClicked, [=](){
        this->showMaximized();
        m_sizeGripWidget->hide();
    });

    connect(m_controlButtons, &WindowControlButtons::normalButtonClicked, [=](){
        this->showNormal();
        m_sizeGripWidget->show();
    });
}

void TabWindow::mousePressEvent(QMouseEvent *event)
{
    if((Qt::WindowFullScreen & this->windowState()) || (Qt::WindowMaximized & this->windowState()))
        return QWidget::mousePressEvent(event);
    if(m_tabWidget->geometry().contains(event->pos()) && event->pos().y() - m_tabWidget->geometry().y() < 30)
    {
        m_mousePressed = true;
        m_mousePoint = event->pos();
        event->accept();
        return;
    }
    return QWidget::mousePressEvent(event);
}

void TabWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
    return QWidget::mouseReleaseEvent(event);
}

void TabWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(m_tabWidget->geometry().contains(event->pos()) && event->pos().y() - m_tabWidget->geometry().y() < 30)
        m_controlButtons->triggerNormalOrMaxButtonClick();
}

void TabWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePressed)
    {
        QPoint curMousePos = event->globalPos() - m_mousePoint;
        move(curMousePos);
        event->accept();
        return;
    }
    return QWidget::mouseMoveEvent(event);
}


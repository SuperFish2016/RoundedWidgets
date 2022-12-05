#include "tabwidget.h"
#include <QLayout>
#include <QMessageBox>
#include "iconfont/iconfonthelper.hpp"
TabWidget::TabWidget(QWidget *parent)
{
    m_tabBar = new TabBar(this);
    m_tabBar->setIconSize(QSize(25, 20));
    connect(m_tabBar, &TabBar::addButtonClicked, this, [=](){
        int index = this->addNewTab(new QWidget, "New Tab");
        QPushButton* button = new QPushButton;
        IconFontDuotoneHelper::setIcon(button, "images", 10, Qt::black);
        this->setTabButton(index, button);
    });
    setTabBar(m_tabBar);

    // make the tab background-color same with tabbar
    this->setStyleSheet(QString(".TabWidget{background-color:%1;}").arg(TabBarBackgroundColor.name()));
    //this->showMaximized();
    this->setWindowFlag(Qt::FramelessWindowHint);
}

int TabWidget::addNewTab(QWidget *widget, const QString &label, const QIcon &leftIcon)
{
    int index = this->addTab(widget, label);
    this->setCurrentIndex(index);
    QSize iconSize = this->tabBar()->iconSize();

    if(!leftIcon.isNull())
    {
        QPushButton* button = new QPushButton;
        button->setFlat(true);
        button->setIcon(leftIcon);
        button->setFixedSize(iconSize);
        this->tabBar()->setTabButton(index, QTabBar::LeftSide, button);
    }

    QPushButton* button = new QPushButton; // Close Button
    connect(button, &QPushButton::clicked, this, &TabWidget::onCloseButtonClicked);
    button->setFlat(true);
    IconFontLightHelper::setIcon(button, "times", 10);
    button->setFixedSize(iconSize);
    this->tabBar()->setTabButton(index, QTabBar::RightSide, button);
    return index;
}

void TabWidget::setTabLabel(int index, const QString &label)
{
    m_tabBar->setTabText(index, label);
}

void TabWidget::setTabIcon(int index, const QIcon &icon)
{
    QSize iconSize = m_tabBar->iconSize();
    QPushButton* button = new QPushButton;
    button->setFlat(true);
    button->setIcon(icon);
    button->setFixedSize(iconSize);
    m_tabBar->setTabButton(index, QTabBar::LeftSide, button);
}

void TabWidget::setTabButton(int index, QPushButton *button)
{
    QSize iconSize = m_tabBar->iconSize();
    button->setFlat(true);
    button->setFixedSize(iconSize);
    m_tabBar->setTabButton(index, QTabBar::LeftSide, button);
}

void TabWidget::resizeEvent(QResizeEvent *ev)
{
    m_tabBar->setMaximumWidth(ev->size().width() - 80);
    QTabWidget::resizeEvent(ev);
}

void TabWidget::onCloseButtonClicked()
{
    QPushButton *closeButton = qobject_cast<QPushButton*>(sender());
    for (int i = 0 ; i < count(); ++i) {
       QWidget *widget = this->tabBar()->tabButton(i, QTabBar::RightSide);
       QString tabText = this->tabBar()->tabText(i);
       if (widget == closeButton)
       {
           int ret = QMessageBox::question(this, "Close Tab", "would you like to close the tab: " + tabText,
                                           QMessageBox::Yes | QMessageBox::No);
           if(ret == QMessageBox::Yes)
           {
               this->removeTab(i);
               this->setCurrentIndex((this->currentIndex() == i && i >= 1) ? i - 1 : 0);
           }
           break;
       }
    }
}




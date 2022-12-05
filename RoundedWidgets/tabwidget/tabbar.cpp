#include "tabbar.h"
#include <QPainter>
#include <QToolButton>
#include <QStyleOption>
#include <QEvent>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QDebug>
#include "tabbardrawhelper.h"
#include <QToolButton>
#include "style.h"

void TabBarStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption *option,
                                  QPainter *painter, const QWidget *widget) const
{
    // PrimitiveElement是一个普通GUI元素，如checkbox的指示器，
    if (pe == QStyle::PE_IndicatorArrowLeft || pe == QStyle::PE_IndicatorArrowRight )
    {
        const QToolButton *button = static_cast<const QToolButton *>(widget);
        if (!button || (nullptr != button && !button->isVisible()))
            return;
        // draw arrow background-color
        painter->save();
        QPainterPath path;
        // adjust here to remove the border when button is pressed.
        path.addRoundedRect(option->rect.adjusted(-2, -2, 0, 0), 0, 0, Qt::AbsoluteSize);
        painter->setClipPath(path);
        painter->setPen(Qt::NoPen);
        painter->setBrush(TabBarBackgroundColor);
        painter->drawPath(path);
        painter->restore();

        QRect triangelRect = QRect(0, 0, 6, 8);
        if(QStyle::PE_IndicatorArrowLeft == pe)
            DrawHelper::drawArrow(painter,option->rect, triangelRect, DrawHelper::Left, Qt::gray);
        else if(QStyle::PE_IndicatorArrowRight == pe)
            DrawHelper::drawArrow(painter, option->rect, triangelRect, DrawHelper::Right, Qt::gray);
        return;
    }
    QProxyStyle::drawPrimitive(pe, option, painter, widget);
}

int TabBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    if (PM_TabBarScrollButtonWidth == metric) {
        return 30;
    } else {
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}

QRect TabBarStyle::subElementRect(SubElement element,  const QStyleOption *option,  const QWidget *widget) const
{
    if (SE_TabBarTabLeftButton == element) {
        return calcIconRect(true, option);
    } else if (SE_TabBarTabRightButton == element) {
        return calcIconRect(false, option);
    } else {
        return QProxyStyle::subElementRect(element, option, widget);
    }
}

QRect TabBarStyle::calcIconRect(bool left, const QStyleOption *option) const
{
    const QStyleOptionTab *tab_option = qstyleoption_cast<const QStyleOptionTab *>(option);
    QSize icon_size = tab_option->iconSize;
    const QRect tab_rect = tab_option->rect;
    QPoint center_pos;
    QRect button_rect;
    const int icon_padding = 8;
    if (left) {
        center_pos = QPoint(icon_padding+icon_size.width()/2 + tab_rect.x(),
                            tab_rect.y()+(tab_rect.height()-icon_size.height())/2+icon_size.height()/2);
    } else {
        center_pos = QPoint(tab_rect.x()+tab_rect.width()-icon_padding-icon_size.width()/2,
                                tab_rect.y()+(tab_rect.height()-icon_size.height())/2+icon_size.height()/2);
    }
    button_rect = QRect(QPoint(0, 0), icon_size);
    button_rect.moveCenter(center_pos);
    return button_rect;
}

// TabBar implments
TabBar::TabBar(QWidget *parent) : QTabBar(parent)
{
    this->setStyle(new TabBarStyle());
    if (m_addButton.drawPlusButton)
        addTab("WTS");
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

QSize TabBar::tabSizeHint(int index) const
{
    if (index == count()-1 && m_addButton.drawPlusButton)
         return QSize(50, 30);
    return m_tabSize;
}

void TabBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // draw entire tabbar
    drawTabBar(&painter);
    // draw the single tab
    drawTab(&painter);
    // draw plus button
    if (m_addButton.drawPlusButton)
        drawPlusButton(&painter);
}

void TabBar::mousePressEvent(QMouseEvent *event)
{
    int index = tabIndexAtPoint(event->pos());
    if (index == count()-1 && m_addButton.drawPlusButton) {
        emit addButtonClicked();
        return;
    }
    QTabBar::mousePressEvent(event);
}

int TabBar::tabIndexAtPoint(const QPoint &point)
{
    for (int i = 0 ; i < count(); ++i) {
        QRect rect = tabRect(i);
        if (rect.contains(point)) {
            return i;
        }
    }
    return -1;
}

void TabBar::drawTab(QPainter *painter)
{
    int tab_count = m_addButton.drawPlusButton ? count() - 1 : count();
    int curTabIndex = this->currentIndex();
    QStyleOptionTab option;
    for (int index = 0; index < tab_count; index++)
    {
        painter->save();
        QRect rect = tabRect(index);
        initStyleOption(&option, index);
        // draw background
        QRect draw_rect = rect.adjusted(0, 5, 0, 5);
        bool drawSplitLine = true;
        if(index == curTabIndex || index == curTabIndex - 1) drawSplitLine = false;
        painter->setPen(Qt::NoPen);
        if(QStyle::State_Selected & option.state) {
            DrawHelper::drawRoundedTabBar(painter, draw_rect, TabSelectedBackgroundColor);
        }
        else if(!(QStyle::State_Selected & option.state)) {
            DrawHelper::drawRoundedTabBar(painter, draw_rect, TabUnselectedBackgroundColor, drawSplitLine);
        }
        if(!(QStyle::State_Selected & option.state) && QStyle::State_MouseOver & option.state) {
            DrawHelper::drawRoundedTabBar(painter, draw_rect, TabHoverBackgroundColor , false);
        }
        // draw text
        QFont font = painter->font();
        font.setFamily("Arial");
        QRect text_rect = draw_rect.marginsAdded(QMargins{-38, 8, -20, 0});
        if (QStyle::State_Selected & option.state) {
            font.setBold(true);
        }
        painter->setFont(font);
        painter->setPen(TabBarTextColor);
        QString text = fontMetrics().elidedText(option.text, Qt::ElideRight, text_rect.width(), 0);
        painter->drawText(text_rect, Qt::AlignLeft | Qt::AlignVCenter, text);
        painter->restore();
    }
}


void TabBar::drawTabBar(QPainter *painter)
{
    painter->save();
    painter->setBrush(TabBarBackgroundColor);
    painter->drawRect(this->rect().adjusted(-2, -2, 0, 0));
    painter->restore();
}

void TabBar::drawPlusButton(QPainter *painter)
{
    int last_index = count() - 1;
    QRect draw_rect = QRect(QPoint(0, 0), m_addButton.plusButtonSize);
    draw_rect.moveCenter(QPoint(tabRect(last_index).left() + draw_rect.width(), tabRect(last_index).center().y()));
    // adjust postion to keep align with the last tab
    draw_rect = draw_rect.adjusted(0, 5, 0, 0);

    // draw plus button background rect.
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    QStyleOptionTab option;
    initStyleOption(&option, last_index);
    painter->setBrush(QBrush(TabBarBackgroundColor));
    if(option.state & QStyle::State_MouseOver)
    {
        painter->setBrush(QBrush(SelectBackgroundColor));
    }
    painter->drawRoundedRect(draw_rect, 5, 5);
    painter->restore();
    // draw plus
    DrawHelper::drawPlus(painter, draw_rect);
}


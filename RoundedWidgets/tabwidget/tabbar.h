#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>
#include <QProxyStyle>
#include <QStyleOption>
#include <QPushButton>
#include "style.h"

class TabBarStyle : public QProxyStyle
{
public:
    TabBarStyle(QStyle *parent = Q_NULLPTR):QProxyStyle(parent) { }

    void drawPrimitive(PrimitiveElement pe, const QStyleOption *option, QPainter *painter,
                    const QWidget *widget = Q_NULLPTR) const override;

    int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const override;

    virtual QRect subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const override;

private:
    QRect calcIconRect(bool left, const QStyleOption *option) const;
};

class TabBar : public QTabBar
{
    Q_OBJECT
public:
     struct TabBarAddButton {
        bool  drawPlusButton;
        QSize lastTabSize ;
        QSize plusButtonSize;
    };

public:
    explicit TabBar(QWidget *parent = 0);
    QSize tabSize() const { return m_tabSize; }

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual QSize tabSizeHint(int index) const override;

private:
    int tabIndexAtPoint(const QPoint &point);
    void drawTab(QPainter *painter);

    void drawTabButton();
    void drawPlusButton(QPainter *painter);

    void drawTabBar(QPainter *painter);

Q_SIGNALS:
    void addButtonClicked();

private:
    // single tab size, adjust it will infect the tab's icon, text display.
    QSize m_tabSize = QSize(250, 30);

    TabBarAddButton m_addButton{true,  QSize(30, m_tabSize.height()), QSize(25, 25)};
};

#endif // TABBAR_H

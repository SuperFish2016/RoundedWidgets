#ifndef ROUNDEDWIDGET_H
#define ROUNDEDWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include "style.h"

#define OVERRIDE_PAINTEVENT(T) \
protected: \
virtual void paintEvent(QPaintEvent *event) override{ \
    T::paintEvent(event); \
    QPainter painter(this); \
    painter.setRenderHint(QPainter::Antialiasing); \
    painter.setBrush(QBrush(m_brushColor)); \
    painter.setPen(Qt::transparent); \
    QRect rect = this->rect(); \
    rect.setWidth(rect.width() ); \
    rect.setHeight(rect.height()); \
    painter.drawRoundedRect(rect, 8, 8); \
} \
private: \
QBrush m_brushColor;


class RoundedWidget : public QWidget
{
    Q_OBJECT
public:
    RoundedWidget(QWidget* parent = nullptr)
        : QWidget(parent){}

    RoundedWidget(QColor brushColor, QWidget* parent = nullptr)
        : QWidget(parent), m_brushColor(brushColor){}

    OVERRIDE_PAINTEVENT(QWidget)
};

#endif // ROUNDEDWIDGET_H

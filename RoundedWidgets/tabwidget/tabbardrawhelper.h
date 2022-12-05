#ifndef _DRAWHELPER_H
#define _DRAWHELPER_H

#include <QColor>
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QRectF>


class QPainter;

struct DrawHelper {
    enum Orientation
    {
        Left,
        Right,
        Top,
        Bottom
    };

    static void drawX(QPainter* painter, const QRect& target_rect, const QColor& text_color = Qt::black,
                      const QSize& text_size = QSize(8, 8),  const int pen_width = 2)
    {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing, true);
        QRect x_rect = {0, 0, text_size.width(), text_size.height()};
        x_rect.moveCenter(target_rect.center());
        QPen pen;
        pen.setBrush(QBrush(text_color, Qt::SolidPattern));
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(pen_width);
        painter->setPen(pen);
        painter->drawLine(x_rect.topLeft(), x_rect.bottomRight());
        painter->drawLine(x_rect.bottomLeft(), x_rect.topRight());
        painter->restore();
    }

    static void drawPlus(QPainter* painter, const QRect& target_rect, const QColor& text_color = Qt::darkGray,
                         const QSize& text_size = QSize(10, 10), const int pen_width = 2) {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing, true);
        QRect rect = {0, 0, text_size.width(), text_size.height()};
        rect.moveCenter(target_rect.center());
        QPen pen;
        pen.setBrush(QBrush(text_color, Qt::SolidPattern));
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(pen_width);
        painter->setPen(pen);
        painter->drawLine(
                    QPoint(rect.left() + rect.width() / 2, rect.top()),
                    QPoint(rect.left() + rect.width() / 2, rect.top() + rect.height()));
        painter->drawLine(
                    QPoint(rect.left(), rect.top() + rect.height() / 2),
                    QPoint(rect.left() + rect.width(), rect.top() + rect.height() / 2));
        painter->restore();
    }

    static void drawRoundedTabBar(QPainter* painter, const QRect& drawRect = QRect(50, 50, 180, 40),
                                  const QColor& backgroundColor = Qt::white, bool drawSplitLine = false)
    {
        QPainterPath roundRectPath;
        QSizeF topRoundedSize(15, 15);
        QSizeF bottomRoundedSize(10, 10);
        roundRectPath.moveTo(drawRect.x() + drawRect.width() ,
                             drawRect.y() + drawRect.height());
        // top-right
        roundRectPath.arcTo(drawRect.x() + drawRect.width() - topRoundedSize.width(),
                            drawRect.y(),
                            topRoundedSize.width(), topRoundedSize.height(),
                            0.0, 90.0);

        // top-left
        roundRectPath.arcTo(drawRect.x(),
                            drawRect.y(),
                            topRoundedSize.width(), topRoundedSize.height(),
                            90.0, 90.0);

        // left-bottom
        roundRectPath.arcTo(drawRect.x() - bottomRoundedSize.width(),
                            drawRect.y() + drawRect.height() - bottomRoundedSize.height(),
                            bottomRoundedSize.width(), bottomRoundedSize.height(),
                            0.0, -90.0);

        // right-bottom
        roundRectPath.arcTo(drawRect.x() + drawRect.width() ,
                            drawRect.y() + drawRect.height() - bottomRoundedSize.height(),
                            bottomRoundedSize.width(), bottomRoundedSize.height(),
                            270.0, -90.0);
        roundRectPath.closeSubpath();
        painter->save();
        painter->setBrush(backgroundColor);
        painter->setPen(Qt::NoPen);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawPath(roundRectPath);

        // draw split line
        if(drawSplitLine)
        {
            painter->setPen(Qt::lightGray);
            painter->drawLine(QPointF(drawRect.x() + drawRect.width(), drawRect.y() + 10),
                              QPointF(drawRect.x() + drawRect.width(), drawRect.y() + drawRect.height() - 10));
        }
        painter->restore();
    }

    static void drawArrow(QPainter* painter,  const QRectF& outlineRect, const QRectF& triangle, Orientation orientation, const QColor& backgroundColor = Qt::black)
    {
        painter->save();
        QRectF triangleRect = triangle;

        QPointF triangleRectCenter = triangleRect.center();
        triangleRect.moveTo(outlineRect.center());
        triangleRect.translate(-triangleRectCenter);

        static const QPointF rightTrianglePoints[3] = {
            QPointF(triangleRect.x(), triangleRect.y()),
            QPointF(triangleRect.x(), triangleRect.y() + triangleRect.height()),
            QPointF(triangleRect.x() + triangleRect.width(), triangleRect.y() + triangleRect.height() / 2)
        };

        static const QPointF leftTrianglePoints[3] = {
            QPointF(triangleRect.x() + triangleRect.width(), triangleRect.y()),
            QPointF(triangleRect.x() + triangleRect.width(), triangleRect.y() + triangleRect.height()),
            QPointF(triangleRect.x(), triangleRect.y() + triangleRect.height() / 2)
        };

        painter->setBrush(backgroundColor);
        painter->setRenderHint(QPainter::Antialiasing, true);
        switch (orientation) {
        case Right:
            painter->drawPolygon(rightTrianglePoints, 3);
            break;
        case Left:
            painter->drawPolygon(leftTrianglePoints, 3);
            break;
        default:
            break;
        }
        painter->restore();
    }
};

#endif  // _DRAWHELPER_H

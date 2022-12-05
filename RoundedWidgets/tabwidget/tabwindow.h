#ifndef TABWINDOW_H
#define TABWINDOW_H

#include "tabwidget.h"
class QSizeGrip;
class WindowControlButtons;
class TabWindow : public QWidget
{
    Q_OBJECT
public:
    TabWindow(QWidget* parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(TabBarBackgroundColor));
        painter.setPen(Qt::gray);
        QRect rect = this->rect();
        rect.setWidth(rect.width() );
        rect.setHeight(rect.height());
        painter.drawRoundedRect(rect, 7, 7);
    }

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* e) override;
    virtual void resizeEvent(QResizeEvent *ev) override;

private:
    void createWindowControlButtons();

private:
    QSizeGrip* m_sizeGripWidget = nullptr;
    TabWidget* m_tabWidget = nullptr;
    WindowControlButtons* m_controlButtons;


    bool   m_mousePressed = false;
    QPoint m_mousePoint;
};

#endif // TABWINDOW_H

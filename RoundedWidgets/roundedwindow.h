#ifndef ROUNDEDWIDOW_H
#define ROUNDEDWIDOW_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QHoverEvent>
#include <QMouseEvent>
#include <QPainter>
#include "roundedwidget/roundedwidget.h"
#include "style.h"
class QSizeGrip;
class RoundedMenu;

class RoundedWindow : public RoundedWidget
{
    Q_OBJECT

public:
    enum WindowType
    {
        ScalableWindow,
        FixedWindow
    };

    explicit RoundedWindow(WindowType wt = ScalableWindow, QWidget *parent = nullptr);
    ~RoundedWindow();

    void setCentralWidget(QWidget* widget);
    QWidget *centralWidget() const{return m_centralWidget;}

protected:

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void titleWidgetDoubleClicked();

private:
    void createTitleBarWidget();
    void createTitleBarMenu();
private:
    QString m_strAppName;
    QString m_strAppIcon;

    QWidget* m_titlebarWidget;
    QWidget* m_centralWidget;
    QSizeGrip* m_sizeGripWidget = nullptr;

    bool m_mousePressed = false;
    QPoint m_mousePoint;

    RoundedMenu* m_menu;
    WindowType m_windowType;
    QSize      m_windowSize;
};

#endif // ROUNDEDWIDGET_H

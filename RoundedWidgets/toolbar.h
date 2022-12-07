#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    ToolBar(QWidget* parent = nullptr);

private:
    void createAction(QWidget* parent, const QString& text, const QString& iconName, int iconSize, const QColor& iconColor);
    QMenu* createActionMenu(const QString& text, const QString& iconName, int iconSize, const QColor& iconColor);
    void createActions();
};

#endif // TOOLBAR_H

#include "toolbar.h"
#include <QMenu>
#include <QLayout>
#include "iconfont/iconfonthelper.hpp"

typedef  IconFontSolidHelper ICON_TYPE;

ToolBar::ToolBar(QWidget *parent)
    : QToolBar(parent)
{
    createActions();
    this->layout()->setSpacing(20);
    this->setIconSize(QSize(50, 50));
}


void ToolBar::createAction(QWidget* parent, const QString& text, const QString& iconName, int iconSize, const QColor& iconColor)
{
    QAction* action = new QAction(tr(""), this);
    action->setText(text);
    action->setIcon(ICON_TYPE::icon(iconName, iconSize, iconColor));
    action->setToolTip(text);
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    parent->addAction(action);
}

QMenu* ToolBar::createActionMenu(const QString& text, const QString& iconName, int iconSize, const QColor &actionColor)
{
    QAction *menuAction = new QAction();
    menuAction->setIcon(ICON_TYPE::icon(iconName, iconSize, actionColor));
    menuAction->setText(text);

    QMenu *menu = new QMenu("Menu", nullptr);
    menuAction->setMenu(menu);
    this->addAction(menuAction);
    return menu;
}

void ToolBar::createActions()
{
    const QColor actionColor = Qt::darkCyan;
    const int iconSize = 15;

    createAction(this, "Back",    "arrow-circle-left",    iconSize, actionColor);
    createAction(this, "Forward", "arrow-circle-right",   iconSize, actionColor);
    this->addSeparator();

    createAction(this, "Open",    "folder-open",  iconSize, actionColor);
    createAction(this, "Save",    "save",         iconSize, actionColor);
    createAction(this, "Export",  "file-export",  iconSize - 3, actionColor);
    this->addSeparator();

    QMenu* addMenu = createActionMenu("Add", "plus-circle",    iconSize,     actionColor);
    createAction(addMenu, "Circle",    "circle",               iconSize - 6, actionColor);
    createAction(addMenu, "Rectangle", "rectangle-landscape",  iconSize - 6, actionColor);
    createAction(addMenu, "Polygon",   "octagon",   iconSize - 6, actionColor);
    createAction(addMenu, "Triangle",  "triangle",  iconSize - 6, actionColor);

    createAction(this, "Zoom In",    "search-plus",  iconSize, actionColor);
    createAction(this, "Zoom Out",   "search-minus", iconSize, actionColor);

    this->addSeparator();

    QMenu* moreMenu = createActionMenu("More", "ellipsis-h",    iconSize - 3, actionColor);
    createAction(moreMenu, "Circle",    "circle",               iconSize - 4, actionColor);
    createAction(moreMenu, "Rectangle", "rectangle-landscape",  iconSize - 4, actionColor);
}

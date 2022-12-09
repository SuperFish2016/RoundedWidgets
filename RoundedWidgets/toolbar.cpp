#include "toolbar.h"
#include <QMenu>
#include <QDebug>
#include <QLayout>
#include "iconfont/iconfonthelper.hpp"

typedef  IconFontSolidHelper ICON_TYPE;

ToolBar::ToolBar(QWidget *parent)
    : QToolBar(parent)
{
    createToolBarActions();
    this->layout()->setSpacing(20);
    this->setIconSize(QSize(45, 45));
}

void ToolBar::createAction(QWidget *parent, const ActionIcon &actionIcon, int iconSize, const QColor &iconColor)
{
    QAction* action = new QAction(m_actionIcons[actionIcon.id].text, this);
    action->setIcon(ICON_TYPE::icon(m_actionIcons[actionIcon.id].icon, iconSize, iconColor));
    action->setToolTip(m_actionIcons[actionIcon.id].text);
    connect(action, &QAction::triggered, [=](){
        emit actionClicked(m_actionIcons[actionIcon.id].id);
    });
    parent->addAction(action);
}

QMenu* ToolBar::createActionMenu(const ActionIcon& actionIcon, int iconSize, const QColor &actionColor)
{
    QAction *menuAction = new QAction();
    menuAction->setIcon(ICON_TYPE::icon(m_actionIcons[actionIcon.id].icon, iconSize, actionColor));
    menuAction->setText(m_actionIcons[actionIcon.id].text);

    QMenu *menu = new QMenu("Menu", nullptr);
    menu->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setWindowFlag(Qt::NoDropShadowWindowHint);
    menu->setStyleSheet("border:1px solid transparent; border-radius:8px; padding:5 5 0 5;");
    menuAction->setMenu(menu);
    this->addAction(menuAction);
    return menu;
}

void ToolBar::createToolBarActions()
{
    const QColor actionColor = Qt::darkGreen;
    const int iconSize = 15;

    for(int i = 0; i < sizeof(m_actionIcons) / sizeof(m_actionIcons[0]); i++)
    {
        if(m_actionIcons[i].id == Open || m_actionIcons[i].id == Add || m_actionIcons[i].id == More) this->addSeparator();
        if(m_actionIcons[i].id == Add)
        {
            QMenu* addMenu = createActionMenu(m_actionIcons[Add],   iconSize , actionColor);
            createAction(addMenu, m_actionIcons[AddCircle],         iconSize - 5, actionColor);
            createAction(addMenu, m_actionIcons[AddRectangle],      iconSize - 5, actionColor);
            createAction(addMenu, m_actionIcons[AddPolygon],        iconSize - 5, actionColor);
            createAction(addMenu, m_actionIcons[AddTriangle],       iconSize - 5, actionColor);
            i = AddTriangle + 1;
            continue;
        }

        if(m_actionIcons[i].id == More)
        {
            QMenu* moreMenu = createActionMenu(m_actionIcons[More], iconSize -3, actionColor);
            createAction(moreMenu, m_actionIcons[Options], iconSize - 3 , actionColor);
            i = Options + 1;
            continue;
        }
        createAction(this, m_actionIcons[i], iconSize , actionColor);
    }
}

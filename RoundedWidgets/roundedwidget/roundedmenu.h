#ifndef ROUNDEDMENU_H
#define ROUNDEDMENU_H

#include <QMenu>
#include "roundedwidget.h"

class RoundedMenu : public QMenu
{
public:
    RoundedMenu(QWidget *parent = nullptr);
    RoundedMenu(const QString &title, QWidget *parent = nullptr);

    OVERRIDE_PAINTEVENT(QMenu)
};

#endif // ROUNDEDMENU_H

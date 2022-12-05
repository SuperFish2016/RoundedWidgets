#include "roundedmenu.h"
#include "style.h"
#include <QPixmap>
#include <QPainter>
RoundedMenu::RoundedMenu(QWidget *parent)
    : QMenu(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

RoundedMenu::RoundedMenu(const QString &title, QWidget *parent)
    : RoundedMenu(parent)
{
    this->setTitle(title);
}


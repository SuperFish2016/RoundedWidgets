#include "windowcontrolbuttons.h"
#include <QToolButton>
#include "iconfont/iconfonthelper.hpp"
#include <QApplication>
#include <QHBoxLayout>
#include "style.h"
WindowControlButtons::WindowControlButtons(QWidget* parent)
    :QWidget(parent)
{
    const int iconSize = 8;
    const QColor color = Qt::black;
    const QSize buttonSize = QSize(20, 20);

    QToolButton *menuButton, *miniButton, *normalOrMaxButton;
    menuButton = miniButton = normalOrMaxButton = nullptr;

//    menuButton = new QToolButton;
//    IconFontHelper::setIcon(menuButton, "list-ul", iconSize, color);
//    menuButton->setFixedSize(buttonSize);
//    menuButton->setAutoRaise(true);
//    connect(menuButton, &QToolButton::clicked, [=](){
//       // m_menu->exec(this->mapToGlobal(menuButton->pos()) + QPoint(0, menuButton->size().height()));
//    });

    miniButton = new QToolButton;
    IconFontLightHelper::setIcon(miniButton, "minus", iconSize + 3, color);
    miniButton->setFixedSize(buttonSize);
    miniButton->setAutoRaise(true);
    miniButton->setStyleSheet(QString("QToolButton:hover{background-color:%1;}").arg(SelectBackgroundColor.name()));

    connect(miniButton, &QToolButton::clicked, [=](){
        emit minimizedButtonClicked();
    });

    normalOrMaxButton = new QToolButton;
    m_normalOrMaxButton = normalOrMaxButton;
    IconFontLightHelper::setIcon(normalOrMaxButton, "square-full", iconSize, color);
    normalOrMaxButton->setFixedSize(buttonSize);
    normalOrMaxButton->setAutoRaise(true);
    normalOrMaxButton->setStyleSheet(QString("QToolButton:hover{background-color:%1;}").arg(SelectBackgroundColor.name()));

    connect(normalOrMaxButton, &QToolButton::clicked, [=](){
        static bool windowIsMaximized = parent->isMaximized();
        if(windowIsMaximized){
            windowIsMaximized = false;
            emit normalButtonClicked();
            IconFontLightHelper::setIcon(normalOrMaxButton, "square-full", iconSize, color);
        }
        else{
            emit maximizedButtonClicked();
            windowIsMaximized = true;

         //   if(m_sizeGripWidget) m_sizeGripWidget->hide();
            IconFontLightHelper::setIcon(normalOrMaxButton, "clone", iconSize, color);
        }
    });

    QToolButton* closeButton = new QToolButton();
    IconFontLightHelper::setIcon(closeButton, "times", iconSize + 3 , color);
    closeButton->setFixedSize(buttonSize);
    closeButton->setAutoRaise(true);
    closeButton->setStyleSheet("QToolButton:hover{background-color:red;color: white;}");
    connect(closeButton, &QToolButton::clicked, [](){
        qApp->quit();
    });

    QHBoxLayout* layout = new QHBoxLayout;
    if(menuButton) layout->addWidget(menuButton);
    if(miniButton) layout->addWidget(miniButton);
    if(normalOrMaxButton) layout->addWidget(normalOrMaxButton);
    layout->addWidget(closeButton);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setSpacing(6);
    this->setFixedHeight(25);
    this->setLayout(layout);
    this->setStyleSheet("border-radius:4px;");
}

void WindowControlButtons::triggerNormalOrMaxButtonClick()
{
    if(m_normalOrMaxButton)
       m_normalOrMaxButton->click();
}

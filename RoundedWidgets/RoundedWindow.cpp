#include <QSizeGrip>
#include <QMenu>
#include <QBoxLayout>
#include <QApplication>
#include "roundedwindow.h"
#include "iconfont/iconfonthelper.hpp"
#include "style.h"
#include "roundedwidget/roundedmenu.h"
#include "tabwidget/tabwidget.h"

RoundedWindow::RoundedWindow(WindowType wt, QWidget *parent)
    : RoundedWidget(Qt::white), m_windowType(wt)
{
    createTitleBarWidget();
    createTitleBarMenu();
    m_centralWidget = new QWidget;
    m_centralWidget->setStyleSheet(QString(".QWidget{background-color:%1}").arg(TabBarBackgroundColor.name()));

    m_centralWidget->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
    QHBoxLayout* centerWidgetLayout = new QHBoxLayout;
    centerWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_centralWidget->setLayout(centerWidgetLayout);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_titlebarWidget);
    layout->addWidget(m_centralWidget);
    if(m_windowType == ScalableWindow)
    {
        m_sizeGripWidget = new QSizeGrip(m_centralWidget);
        layout->addWidget(m_sizeGripWidget, 0, Qt::AlignBottom | Qt::AlignRight);
    }

    layout->setContentsMargins(1, 0, 1, 6);
    layout->setSpacing(3);
    this->setLayout(layout);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMinimumSize(m_windowType == ScalableWindow ? QSize(600, 480) : QSize(200, 50));
    this->setFont(AppFont);
}

RoundedWindow::~RoundedWindow()
{
}

void RoundedWindow::setCentralWidget(QWidget *widget)
{
    m_centralWidget->layout()->addWidget(widget);
   // this->layout()->removeWidget(centerWidget);
//    this->layout()->addWidget(widget);
//    centerWidget = widget;
}

void RoundedWindow::mousePressEvent(QMouseEvent *event)
{
    if(!(Qt::WindowFullScreen & this->windowState()) && m_titlebarWidget->geometry().contains(event->pos()))
    {
        m_mousePressed = true;
        m_mousePoint = event->pos();
        event->accept();
        return;
    }
    return QWidget::mousePressEvent(event);
}

void RoundedWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
    return QWidget::mouseReleaseEvent(event);
}

void RoundedWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(m_titlebarWidget->geometry().contains(event->pos()))
        emit titleWidgetDoubleClicked();
}

void RoundedWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePressed)
    {
        QPoint curMousePos = event->globalPos() - m_mousePoint;
        move(curMousePos);
        event->accept();
        return;
    }
    return QWidget::mouseMoveEvent(event);
}

void RoundedWindow::createTitleBarWidget()
{
    const int iconSize = 8;
    const QColor color = Qt::black;
    const QSize buttonSize = QSize(20, 20);

    QLabel* appNameLabel = new QLabel;
    QLabel* appIconLabel = new QLabel;
    appNameLabel->setFont(AppFont);
    m_windowSize = QSize(480, 200); // default windows size

    appIconLabel->setPixmap(qApp->windowIcon().pixmap(QSize(20,20)));
    appNameLabel->setText(qApp->applicationName());
    m_windowSize = QSize(640, 480);


    QToolButton *menuButton, *miniButton, *normalOrMaxButton;
    menuButton = miniButton = normalOrMaxButton = nullptr;
    if(m_windowType == ScalableWindow)
    {
        menuButton = new QToolButton;
        IconFontLightHelper::setIcon(menuButton, "list-ul", iconSize, color);
        menuButton->setFixedSize(buttonSize);
        menuButton->setAutoRaise(true);
        connect(menuButton, &QToolButton::clicked, [=](){
            m_menu->exec(this->mapToGlobal(menuButton->pos()) + QPoint(0, menuButton->size().height()));
        });

        miniButton = new QToolButton;
        IconFontLightHelper::setIcon(miniButton, "window-minimize", iconSize, color);
        miniButton->setFixedSize(buttonSize);
        miniButton->setAutoRaise(true);
        connect(miniButton, &QToolButton::clicked, [=](){
            this->showMinimized();
        });

        normalOrMaxButton = new QToolButton;
        IconFontLightHelper::setIcon(normalOrMaxButton, "window-maximize", iconSize, color); // window-restore
        normalOrMaxButton->setFixedSize(buttonSize);
        normalOrMaxButton->setAutoRaise(true);
        connect(this, &RoundedWindow::titleWidgetDoubleClicked, normalOrMaxButton, &QToolButton::click);
        connect(normalOrMaxButton, &QToolButton::clicked, [=](){
            if(this->isMaximized()){
                this->showNormal();
                if(m_sizeGripWidget) m_sizeGripWidget->show();
                IconFontLightHelper::setIcon(normalOrMaxButton, "window-maximize", iconSize, color);
            }
            else{
                this->showMaximized();
                if(m_sizeGripWidget) m_sizeGripWidget->hide();
                IconFontLightHelper::setIcon(normalOrMaxButton, "window-restore", iconSize, color);
            }
        });
    }

    QToolButton* closeButton = new QToolButton();
    IconFontLightHelper::setIcon(closeButton, "times", iconSize, color);
    closeButton->setFixedSize(buttonSize);
    closeButton->setAutoRaise(true);
    closeButton->setStyleSheet("QToolButton:hover{background-color:red;color: white;}");
    connect(closeButton, &QToolButton::clicked, [](){
        qApp->quit();
    });

    m_titlebarWidget = new QWidget;
    m_titlebarWidget->setStyleSheet(QString(".QWidget{background-color:%1}").arg(TitleBarColor.name()));


    QHBoxLayout* titlelayout = new QHBoxLayout;
    titlelayout->addWidget(appIconLabel);
    titlelayout->addWidget(appNameLabel);
    titlelayout->addStretch();
    if(menuButton) titlelayout->addWidget(menuButton);
    if(miniButton) titlelayout->addWidget(miniButton);
    if(normalOrMaxButton) titlelayout->addWidget(normalOrMaxButton);
    titlelayout->addWidget(closeButton);
    titlelayout->setContentsMargins(5, 0, 5, 0);
    titlelayout->setSpacing(6);
    m_titlebarWidget->setFixedHeight(25);
    m_titlebarWidget->setLayout(titlelayout);
    m_titlebarWidget->setStyleSheet("border-radius:4px;");
}

void RoundedWindow::createTitleBarMenu()
{
    m_menu = new RoundedMenu("");
    RoundedMenu* fileSubMenu = new RoundedMenu("File");
    m_menu->addMenu(fileSubMenu);
    fileSubMenu->QMenu::addAction("Open");
    fileSubMenu->QMenu::addAction("Save as");
    m_menu->QMenu::addAction("About");
    m_menu->QMenu::addSeparator();
    m_menu->QMenu::addAction("Exit");
    m_menu->QMenu::setStyleSheet(qMenuQss);
    fileSubMenu->QMenu::setStyleSheet(qMenuQss);
}

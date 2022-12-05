#include <QDebug>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>
#include "roundedmessagebox.h"
#include "style.h"

RoundedMessageBox::RoundedMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QWidget *parent, Qt::WindowFlags flags)
    :RoundedWindow(FixedWindow)
{
    m_msgBox = new QMessageBox(icon, title, text, buttons, this, flags);
    m_msgBox->setWindowFlag(Qt::FramelessWindowHint);
    connect(m_msgBox, &QMessageBox::accepted, [=](){this->close();});
    this->setCentralWidget(m_msgBox);
    this->setStyle();
}

void RoundedMessageBox::setStyle()
{
    for(auto mc : m_msgBox->children())
    {
        if(mc->objectName() == "qt_msgbox_buttonbox")
        {
            QDialogButtonBox* db = qobject_cast<QDialogButtonBox*>(mc);
            for(auto dbc : db->children())
            {
                QPushButton* dbcbt = qobject_cast<QPushButton*>(dbc);
                if(dbcbt)
                    dbcbt->setStyleSheet(qPushButtonQss);
            }
        }
    }
    m_msgBox->setStyleSheet(qMessageBoxQss);
}

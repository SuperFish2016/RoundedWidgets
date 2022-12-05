#ifndef ROUNDEDMESSAGEBOX_H
#define ROUNDEDMESSAGEBOX_H
#include "roundedwindow.h"
#include <QMessageBox>

class QPaintEvent;
class RoundedMessageBox : public RoundedWindow
{
    Q_OBJECT
public:
    RoundedMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                      QMessageBox::StandardButtons buttons = QMessageBox::NoButton, QWidget *parent = nullptr,
                      Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

private:
    void createWindow();
    void setStyle();
private:
    QMessageBox* m_msgBox = nullptr;
};

#endif // ROUNDEDMESSAGEBOX_H

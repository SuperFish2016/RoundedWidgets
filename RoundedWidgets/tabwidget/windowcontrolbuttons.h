#ifndef WINDOWCONTROLBUTTONS_H
#define WINDOWCONTROLBUTTONS_H
#include <QWidget>
class QToolButton;
class WindowControlButtons : public QWidget
{
    Q_OBJECT
public:
    WindowControlButtons(QWidget* parent = nullptr);

    void triggerNormalOrMaxButtonClick();

signals:
    void minimizedButtonClicked();
    void maximizedButtonClicked();
    void normalButtonClicked();
    void closeButtonClicked();

private:
    QToolButton* m_normalOrMaxButton;
};

#endif // WINDOWCONTROLBUTTONS_H

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QPushButton>

#include "roundedwidget/roundedwidget.h"

class TabBar;
class ToolBar;

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = 0);

    int addNewTab(QWidget* widget, const QString& label, const QIcon& icon = QIcon());

    void setTabLabel(int index, const QString& label);

    void setTabIcon(int index, const QIcon& icon);

    void setTabButton(int index, QPushButton* button);

    //OVERRIDE_PAINTEVENT(QTabWidget)

protected:


    virtual void resizeEvent(QResizeEvent *ev) override;

    QSize sizeHint() const override
    {
        return QSize(800, 600);
    }
protected slots:
    void onCloseButtonClicked();

private:
    TabBar*     m_tabBar;
};
#endif // TABWIDGET_H

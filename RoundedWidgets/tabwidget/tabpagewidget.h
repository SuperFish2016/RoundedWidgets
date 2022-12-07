#ifndef TABPAGEWIDGET_H
#define TABPAGEWIDGET_H
#include "toolbar.h"

// A TabPageWidget that will insert into tabWidget as a page
class TabPageWidget : public QWidget
{
public:
    TabPageWidget(QWidget* parent = nullptr);

    void createActions();
private:
    ToolBar* m_toolBar;
    QWidget* m_centralWidget;
};

#endif // TABPAGEWIDGET_H

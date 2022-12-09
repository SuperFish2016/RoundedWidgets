#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    enum ActionId
    {
        Undo = 0,
        Redo,
        Open,
        Save,
        Export,
        Add,
        AddCircle,
        AddRectangle,
        AddPolygon,
        AddTriangle,
        ZoomIn,
        ZoomOut,
        Submit,
        More,
        Options,
        Max
    };

    struct ActionIcon
    {
        ActionId id;
        QString  text;
        QString  icon;
    };

public:
    ToolBar(QWidget* parent = nullptr);
signals:
    void actionClicked(ActionId actionId);
private:   
    void createToolBarActions();

    // create an menu in the toolbar
    QMenu* createActionMenu(const ActionIcon& actionIcon, int iconSize, const QColor& iconColor);

    // create actions for toolbar or menu.
    void createAction(QWidget* parent, const ActionIcon& actionIcon, int iconSize, const QColor& iconColor);

private:
    const ActionIcon m_actionIcons[Max] = {
        {Undo,          "Undo",         "undo"},
        {Redo,          "Redo",         "redo"},
        {Open,          "Open",         "folder-open"},
        {Save,          "Save",         "save"},
        {Export,        "Export",       "file-export"},
        {Add,           "Add",          "plus-circle"},
        {AddCircle,     "Add Circle",   "circle"},
        {AddRectangle,  "Add Rectangle","rectangle-landscape"},
        {AddPolygon,    "Add Polygon",  "octagon"},
        {AddTriangle,   "Add Triangle", "triangle"},
        {ZoomIn,        "ZoomIn",       "search-plus"},
        {ZoomOut,       "ZoomOut",      "search-minus"},
        {Submit,        "Submit",       "check"},
        {More,          "More",         "ellipsis-h"},
        {Options,       "Options",      "wrench"}
    };
};

#endif // TOOLBAR_H

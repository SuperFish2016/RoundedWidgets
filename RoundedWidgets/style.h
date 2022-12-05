#ifndef STYLE_H
#define STYLE_H
#include <QColor>
#include <QFont>

// Generic style
static const QFont  AppFont("Microsoft YaHei", 10, QFont::Bold);
#define BORDER_RADIUS "border-radius:5px;"

const QColor TabBarBackgroundColor(225, 225, 225);
const QColor SelectBackgroundColor(245, 245, 245);
const QColor TabBarTextColor(Qt::black);

const QColor TabHoverBackgroundColor(235, 235, 235);
const QColor TabSelectedBackgroundColor(248, 248, 248);
const QColor TabUnselectedBackgroundColor = Qt::transparent;

//#define ENABLE_DARK_THEME

#ifdef ENABLE_DARK_THEME
static const QColor TitleBarColor(65,65,65);

#define TextFont "font-family: \"Arial\"; font-size: 8pt;"
#define TextColor "color:rgb(239,239,239);"
#define HoverTextColor          "color:white;"
#define TextBackgroundColor     "background-color: rgb(49,49,49);"
#define SelectedBackgroundColor "background-color: rgb(48,154,255);"
#define PressedBackgroundColor  "background-color: rgb(102,179,255);"
#define ButtonBackgroundColor   "background-color: rgb(68,68,68);"
#define BorderColor             "rgb(68,68,68);"
#else

const QColor TitleBarColor(255,255,255);
#define TextFont "font-family: \"Arial\"; font-size: 8pt;"
#define TextColor               "color:black;"
#define HoverTextColor          "color:rgb(244,244,244);"
#define TextBackgroundColor     "background-color: white"
#define SelectedBackgroundColor "background-color: rgb(48,154,255);"
#define PressedBackgroundColor  "background-color: rgb(102,179,255);"
#define ButtonBackgroundColor   "background-color: rgb(249,249,249);"
#define BorderColor             "gray;"

#endif

const QString qLabelQss =
"QLabel{"
    TextColor \
    TextBackgroundColor \
"}";
const QString qMessageBoxQss =
".QMessageBox{" \
    TextColor \
    TextBackgroundColor \
"}" \
"QMessageBox QLabel{"
    TextColor \
"}";

const QString qPushButtonQss =
"QPushButton{" \
    "border: 1px solid " BorderColor \
    "border-radius: 6px;" \
    ButtonBackgroundColor \
    TextFont \
    TextColor \
    "min-width: 80px;" \
    "min-height: 20px;"
"}" \
"QPushButton:hover {" \
    SelectedBackgroundColor \
    HoverTextColor \
"}" \
"QPushButton:pressed {" \
    PressedBackgroundColor \
"}";

const QString qMenuQss =
"QMenu{" \
     "background-color: transparent;" \
     TextBackgroundColor \
     TextColor \
     "border: 1px solid " BorderColor \
     BORDER_RADIUS \
" }" \
" QMenu::item {" \
     "background-color: transparent;" \
     "padding:2px 25px 2px 25px;" \
     "border-bottom:1px " BorderColor \
" }"\
"QMenu::item:selected {" SelectedBackgroundColor "}";


#endif // STYLE_H

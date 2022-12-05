#include "mainwindow.h"
#include "roundedwindow.h"
#include <QApplication>
#include "roundedmessagebox.h"
#include "style.h"
#include "tabwidget/tabwindow.h"
#include <QVBoxLayout>
#include "iconfont/iconfonthelper.hpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("C:\\Icon4.ico"));
    a.setApplicationName("Qt-Creator");
   // RoundedWindow w(RoundedWindow::ScalableWindow);
    TabWindow w;

   //w.setCentralWidget(tabWidget);
   //RoundedMessageBox w(QMessageBox::Question, "Test", "Plesase don't gitve ok.\nThis is a test messgae box, Plesase don't gitve ok.", QMessageBox::Yes | QMessageBox::No);

    w.show();
    return a.exec();
}

#include "mainwindow_yyw.h"
#include "ReadDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /******定义主窗口******/
    MainWindow_yyw w;
    w.setWindowTitle("Shortest Path Analysis");

    /******定义文件选择窗口******/
    ReadDialog dlg;
    dlg.setWindowTitle("Select E00 File");
    dlg.show();

    /******实现主窗口和文件窗口之间的切换和数据传输******/
    QObject::connect(&dlg,SIGNAL(showmainwindow(char*)),&w,SLOT(receiveOpenFile(char*)));
    QObject::connect(&w,SIGNAL(showOpenFile()),&dlg,SLOT(receiveshow()));


    return a.exec();

}

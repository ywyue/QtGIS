#ifndef MAINWINDOW_YYW_H
#define MAINWINDOW_YYW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTableWidget>
#include "CFileManage.h"
#include "CGLFunction.h"
#include "QueryDialog.h"
#include <iostream>

/******主窗口类******/
namespace Ui {
class MainWindow_yyw;
}

class MainWindow_yyw : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_yyw(QWidget *parent = 0);
    CGLFunction* gl;
    CFileManage fm;
    ~MainWindow_yyw();

signals:
    /******显示打开文件对话框信号******/
    void showOpenFile();

private:
    Ui::MainWindow_yyw *ui;
    QueryDialog *qd;

private slots:

    /******通过输入id查询******/
    void seach_by_id();

    /******通过鼠标点击节点查询******/
    void seach_by_click();

    /******关闭当前文件******/
    void closefile();

    /******接受QueryDialog传来的信号******/
    void receiveData(int startID,int endID);

    /******接受ReadDialog传来的信号******/
    void receiveOpenFile(char* file);

    /******打开新的E00文件******/
    void on_SelectButton_triggered();

};

#endif // MAINWINDOW_YYW_H

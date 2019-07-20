#ifndef READDIALOG_H
#define READDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QTableWidget>
#include "CFileManage.h"
#include "CGLFunction.h"
#include "mainwindow_yyw.h"

/******选择文件窗口类******/
namespace Ui {
class ReadDialog;
}

class ReadDialog : public QDialog
{

    Q_OBJECT

public:
    explicit ReadDialog(QWidget *parent = 0);
    ~ReadDialog();
signals:
    /******显示主窗口信号******/
    void showmainwindow(char*);

private:
    Ui::ReadDialog *ui;

private slots:
    /******选择E00文件******/
    void selectfile();

    /******确认******/
    void readfile();

    /******取消******/
    void cancel();

    /******接受MainWindow_yyw传来的打开文件窗口信号******/
    void receiveshow();
};

#endif // READDIALOG_H

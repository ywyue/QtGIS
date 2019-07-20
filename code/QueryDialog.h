#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include <iostream>
using namespace std;

/******查询窗口类******/
namespace Ui {
class QueryDialog;
}

class QueryDialog:public QDialog
{
     Q_OBJECT
public:
    explicit QueryDialog(QWidget *parent = 0);
    ~QueryDialog();

private:
    Ui::QueryDialog *ui;

signals:
    /******传递起始点编号到主窗口******/
    void sendData(int,int);

private slots:
    /******确认******/
    void on_buttonBox_accepted();

    /******取消******/
    void cancel();
};

#endif // QUERYDIALOG_H

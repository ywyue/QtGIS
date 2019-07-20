#include "mainwindow_yyw.h"
#include "ui_mainwindow_yyw.h"
#include <QPushButton>
#include <QAbstractButton>

MainWindow_yyw::MainWindow_yyw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_yyw)
{
    ui->setupUi(this);
    setMouseTracking(true);


    connect(ui->action_By_Click,SIGNAL(triggered(bool)), this, SLOT(seach_by_click()));
    connect(ui->action_By_ID,SIGNAL(triggered(bool)), this, SLOT(seach_by_id()));

    connect(ui->action_Close_E00,SIGNAL(triggered(bool)),this,SLOT(closefile()));
    connect(ui->action_Select_E00,SIGNAL(triggered(bool)),this,SLOT(on_SelectButton_triggered()));
}


void MainWindow_yyw::seach_by_click()
{
    /******通过输入id查询******/
    gl->IsSearchByClick=true;
    gl->IsSearchByID=false;
    gl->ClickedTimes=0;
    gl->update();
}

void MainWindow_yyw::seach_by_id()
{
    /******通过鼠标点击节点查询******/
    qd = new QueryDialog();
    qd->setWindowTitle("Input IDs");
    connect(qd,SIGNAL(sendData(int,int)),this,SLOT(receiveData(int,int)));
    qd->show();
}

void MainWindow_yyw::receiveData(int startID,int endID)
{
    /******接受QueryDialog传来的信号******/
    gl->minDisPoint1.NdID=startID;
    gl->minDisPoint2.NdID=endID;
    gl->IsSearchByID=true;
    gl->IsSearchByClick=false;
    gl->update();
}

void MainWindow_yyw::closefile()
{
    /******关闭当前文件******/
    gl->close();
}

void MainWindow_yyw::receiveOpenFile(char* file)
{
    /******接受ReadDialog传来的信号******/
    fm.ReadFile(file);
    gl = new CGLFunction();
    setCentralWidget(gl);
    gl->update();
    gl->aMap=&fm.aMap;
    this->show();
}

void MainWindow_yyw::on_SelectButton_triggered()
{
    /******打开新的E00文件******/
    this->hide();
    emit showOpenFile();
}

MainWindow_yyw::~MainWindow_yyw()
{
    delete ui;
}

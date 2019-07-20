#include "ReadDialog.h"
#include "ui_readdialog.h"
#include <QPushButton>
ReadDialog::ReadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadDialog)
{
    ui->setupUi(this);
    connect(ui->SelectFileButton,SIGNAL(clicked(bool)), this, SLOT(selectfile()));
    connect(ui->OkButton,SIGNAL(clicked(bool)), this, SLOT(readfile()));
    connect(ui->CancelButton,SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

ReadDialog::~ReadDialog()
{
    delete ui;
}
void ReadDialog::selectfile()
{
    /******选择一个E00文件******/
    QString fileName = QFileDialog :: getOpenFileName(this, NULL, NULL, "*.e00");
    char *name;
    QByteArray ba = fileName.toLatin1();
    name=ba.data();
    ui->CurrentFile->addItem(name);

}
void ReadDialog::readfile()
{
    this->hide();
    /******向主窗口发送文件路径******/
    emit showmainwindow(ui->CurrentFile->currentText().toLatin1().data());
}
void ReadDialog::cancel()
{
    this->close();
}


void ReadDialog::receiveshow()
{
    /******显示打开文件窗口******/
    this->ui->CurrentFile->currentText().clear();
    this->show();
}

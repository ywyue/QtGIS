#include "QueryDialog.h"
#include "ui_querydialog.h"

QueryDialog::QueryDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::QueryDialog)
{
    ui->setupUi(this);
    connect(ui->OkButton,SIGNAL(clicked(bool)), this, SLOT(on_buttonBox_accepted()));
    connect(ui->CancelButton,SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

QueryDialog::~QueryDialog()
{
    delete ui;
}


void QueryDialog::on_buttonBox_accepted()
{
    /******向主窗口发送起始点编号******/
    emit sendData(ui->StartEdit->text().toInt(),ui->EndEdit->text().toInt());
    this->close();
}
void QueryDialog::cancel()
{
    this->close();
}


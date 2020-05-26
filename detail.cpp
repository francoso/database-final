#include "detail.h"
#include "ui_detail.h"
#include "mysql.h"
#include<QString>

detail::detail(QWidget *parent,int Type,int ID) :
    QWidget(parent),
    ui(new Ui::detail)
{
    type=Type;
    id=ID;
    ui->setupUi(this);

    Mysql *data=new Mysql();
    data->db.open();
    QSqlQuery query(data->db);

    //查看客户页面
    if(type==0){
        ui->label->setText("客户ID：");
        ui->label_2->setText("客户名称：");
        ui->label_3->setText("客户公司：");
        ui->label_4->setText("联系方式：");
        ui->label_5->setText("地址：");

        query.prepare("select * from client where client_id="+QString::number(id));
        query.exec();
        query.first();

        ui->lineEdit->setText(query.value(0).toString());
        ui->lineEdit_2->setText(query.value(1).toString());
        ui->lineEdit_3->setText(query.value(2).toString());
        ui->lineEdit_4->setText(query.value(3).toString());
        ui->lineEdit_5->setText(query.value(4).toString());
    }


    //查看货运页面
    if(type==1){
        ui->label->setText("货运公司ID：");
        ui->label_2->setText("货运公司名称：");
        ui->label_3->setText("联系方式：");
        ui->label_4->setText("地址：");
        ui->label_5->hide();

        query.prepare("select * from shipment where shipment_id="+QString::number(id));
        query.exec();
        query.first();

        ui->lineEdit->setText(query.value(0).toString());
        ui->lineEdit_2->setText(query.value(1).toString());
        ui->lineEdit_3->setText(query.value(2).toString());
        ui->lineEdit_4->setText(query.value(3).toString());
        ui->lineEdit_5->hide();
    }
}

detail::~detail()
{
    delete ui;
}

void detail::on_pushButton_clicked()
{
    this->close();
}

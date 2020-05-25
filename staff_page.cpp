#include "staff_page.h"
#include "ui_staff_page.h"
#include "mysql.h"
#include "inside_page.h"
#include "ui_inside_page.h"
#include<QMessageBox>

staff_page::staff_page(QWidget *parent,int Id) :
    QWidget(parent),
    ui(new Ui::staff_page)
{
    ui->setupUi(this);
    id=Id;
    //获取数据库信息
    Mysql *staff=new Mysql();
    staff->db.open();
    QSqlQuery query(staff->db);
    query.exec("select * from staff where Staff_ID="+QString::number(id));
    query.first();
    ui->lineEdit->setText(query.value(0).toString());
    ui->lineEdit_2->setText(query.value(1).toString());
    ui->lineEdit_3->setText(query.value(2).toString());
    ui->lineEdit_4->setText(query.value(3).toString());
    ui->lineEdit_5->setText(query.value(4).toString());
    ui->lineEdit_6->setText(query.value(5).toString());
    ui->lineEdit_7->setText(query.value(6).toString());
    ui->lineEdit_8->setText(query.value(7).toString());
}

staff_page::~staff_page()
{
    delete ui;
}

void staff_page::on_pushButton_clicked()
{
    Mysql *staff=new Mysql();
    staff->db.open();
    QSqlQuery query(staff->db);
    query.prepare("update staff SET Staff_name=?,Staff_contact=?,enter_date=?,password=?,"
               "department=?,staff_address=?"
               "where Staff_ID="+QString::number(id));
    query.addBindValue(ui->lineEdit_2->text());
    query.addBindValue(ui->lineEdit_3->text());
    query.addBindValue(ui->lineEdit_4->text());
    query.addBindValue(ui->lineEdit_5->text());
    query.addBindValue(ui->lineEdit_6->text());
    query.addBindValue(ui->lineEdit_7->text());
    query.exec();
    QMessageBox::information(nullptr,"修改","修改成功");
}



void staff_page::on_pushButton_2_clicked()
{
    inside_page * Inside_Page = new inside_page;
    this->close();
    Inside_Page->show();
}

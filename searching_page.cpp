#include "searching_page.h"
#include "ui_searching_page.h"
#include<QMessageBox>
#include <QDebug>
#include"inside_page.h"
#include"ui_inside_page.h"
#include"detail.h"
#include"ui_detail.h"

searching_page::searching_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searching_page)
{
    ui->setupUi(this);
    //初始化右边页面
    current_order_ID=-1;
    current_client_ID=-1;
    current_shipment_ID=-1;
    is_add=0;
    //初始化列表
    Mysql* list_1=new Mysql();
    list_1->db.open();
    QSqlQuery query(list_1->db);

    query.exec("select order_client_ID,client_name from order_client natural join client ORDER BY order_client_ID;");
    int i=0;
    while(query.next())
    {
        ui->Client_list->insertItem(i,"订单号："+query.value(0).toString()+"\t客户名称："+query.value(1).toString());
        i++;
    }
    //第二页，工厂
    current_order_ID_2=-1;
    current_factory_ID=-1;
    is_add_2=0;

    query.exec("select order_factory_ID,factory_name from order_factory natural join factory ORDER BY order_factory_ID;");
    while(query.next())
    {
        ui->Factory_List->insertItem(i,"订单号："+query.value(0).toString()+"\t工厂名称："+query.value(1).toString());
    }

}

searching_page::~searching_page()
{
    delete ui;
}

void searching_page::on_pushButton_clicked()
{
    ui->Client_list->clear();
    if(ui->comboBox_1->currentIndex()==0)
    {
        qDebug()<<"0";

        Mysql* list_1=new Mysql();
        list_1->db.open();
        QSqlQuery query(list_1->db);

        query.exec("select order_client_ID,client_name from order_client natural join client ORDER BY order_client_ID;");
        int i=0;
        while(query.next())
        {
            ui->Client_list->insertItem(i,"订单号："+query.value(0).toString()+"\t客户名称："+query.value(1).toString());
            i++;
        }
    }
    else if(ui->comboBox_1->currentIndex()==1)
    {
        QString search=ui->search_edit->text();
        qDebug()<<"1";

        qDebug()<<search;
        Mysql* list_1=new Mysql();
        list_1->db.open();
        QSqlQuery query(list_1->db);

        query.prepare("select order_client_ID,client_name from order_client natural join client"
                   " where order_client_ID="+search+" order by order_client_ID");
        if(query.exec())
            qDebug()<<"yes";
        else
            qDebug()<<"no";
        int i=0;
        while(query.next())
        {
            ui->Client_list->insertItem(i,"订单号："+query.value(0).toString()+"\t客户名称："+query.value(1).toString());
            i++;
        }
    }
    else if(ui->comboBox_1->currentIndex()==2)
    {
        qDebug()<<"2";

        Mysql* list_1=new Mysql();
        list_1->db.open();
        QSqlQuery query(list_1->db);

        query.prepare("select order_client_ID,client_name from order_client natural join client where client_name like '"
                      +ui->search_edit->text()+
                      "%' order by order_client_ID");
        int i=0;
        if(query.exec())
            qDebug()<<"yes";
        else
            qDebug()<<"no";
        while(query.next())
        {
            ui->Client_list->insertItem(i,"订单号："+query.value(0).toString()+"\t客户名称："+query.value(1).toString());
            i++;
        }
     }
}

void searching_page::on_Client_list_itemSelectionChanged()
{
    QString search=ui->search_edit->text();
    int index=0;
    //开启数据库
    Mysql* list_1=new Mysql();
    list_1->db.open();
    QSqlQuery query(list_1->db);

    //获取产品编号
    if(ui->comboBox_1->currentIndex()==0)
    {
        query.exec("select order_client_ID,client_name from order_client natural join client ORDER BY order_client_ID;");
        query.first();
        while(index!=ui->Client_list->currentIndex().row())
        {
            query.next();
            index++;
        }
        current_order_ID=query.value(0).toInt();
    }
    else if(ui->comboBox_1->currentIndex()==1)
    {
        query.prepare("select order_client_ID,client_name from order_client natural join client"
                      " where order_client_ID="+search+" order by order_client_ID");
        query.exec();query.first();
        while(index!=ui->Client_list->currentIndex().row())
        {
            query.next();
            index++;
        }
        current_order_ID=query.value(0).toInt();
    }
    else if(ui->comboBox_1->currentIndex()==2)
    {
        query.prepare("select order_client_ID,client_name from order_client natural join client where client_name like '"
                      +ui->search_edit->text()+
                      "%' order by order_client_ID");
        query.exec();query.first();
        while(index!=ui->Client_list->currentIndex().row())
        {
            query.next();
            index++;
        }
        current_order_ID=query.value(0).toInt();
    }
    qDebug()<<"index="<<current_order_ID;

    query.exec("select order_client_id,staff_name,client_name,shipment_name,product_ID,type,"
               "product_number,departure,destination,date,ways,client_ID,shipment_ID "
               "from order_client natural join shipment natural join staff natural join client "
               "where order_client_ID ="+QString::number(current_order_ID));
    query.first();
    ui->order_client_ID_edit->setText(query.value(0).toString());
    ui->staff_name_edit->setText(query.value(1).toString());
    ui->client_name_edit->setText(query.value(2).toString());
    ui->shipment_name_edit->setText(query.value(3).toString());
    ui->product_ID_edit->setText(query.value(4).toString());
    ui->product_type_edit->setText(query.value(5).toString());
    ui->product_number_edit->setText(query.value(6).toString());
    ui->departure_edit->setText(query.value(7).toString());
    ui->destination_edit->setText(query.value(8).toString());
    ui->finish_date_edit->setText(query.value(9).toString());
    ui->way_edit->setText(query.value(10).toString());

    current_client_ID=query.value(11).toInt();
    current_shipment_ID=query.value(12).toInt();
}

//修改更新client
void searching_page::on_pushButton_4_clicked()
{
    Mysql* list_1=new Mysql();
    list_1->db.open();
    QSqlQuery query(list_1->db);

    if(is_add==0){
        query.exec("select order_client_id "
                   "from order_client "
                   "where order_client_ID ="+QString::number(current_order_ID));
        query.first();
        int this_order_client_id = query.value(0).toInt();

        query.prepare("CALL update_order_client(?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(QString::number(this_order_client_id));
        query.addBindValue(ui->client_name_edit->text());
        query.addBindValue(ui->staff_name_edit->text());
        query.addBindValue(ui->shipment_name_edit->text());
        query.addBindValue(ui->product_ID_edit->text());
        query.addBindValue(ui->product_type_edit->text());
        query.addBindValue(ui->product_number_edit->text());
        query.addBindValue(ui->departure_edit->text());
        query.addBindValue(ui->destination_edit->text());
        query.addBindValue(ui->finish_date_edit->text());
        query.addBindValue(ui->way_edit->text());


        if(query.exec()){
            QMessageBox::information(nullptr,"成功","信息已录入");
            query.exec("select client_id from order_client where order_client_ID="+QString::number(current_order_ID));
            query.first();
            current_client_ID=query.value(0).toInt();
            query.exec("select shipment_id from order_client where order_client_ID="+QString::number(current_order_ID));
            query.first();
            current_client_ID=query.value(0).toInt();
        }
        else
            QMessageBox::information(nullptr,"失败","请检查是否有输入错误");
        }
    else
    {

        query.prepare("CALL insert_order_client(?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(QString::number(current_order_ID));
        query.addBindValue(ui->client_name_edit->text());
        query.addBindValue(ui->staff_name_edit->text());
        query.addBindValue(ui->shipment_name_edit->text());
        query.addBindValue(ui->product_ID_edit->text());
        query.addBindValue(ui->product_type_edit->text());
        query.addBindValue(ui->product_number_edit->text());
        query.addBindValue(ui->departure_edit->text());
        query.addBindValue(ui->destination_edit->text());
        query.addBindValue(ui->finish_date_edit->text());
        query.addBindValue(ui->way_edit->text());

        if(query.exec()){
            qDebug()<<"insert yes";
            QMessageBox::information(nullptr,"新增","新增成功");
        }
        else{
            qDebug()<<"insert no";
            QMessageBox::information(nullptr,"失败","请确认是否有输入错误");
        }
    }
}

void searching_page::on_pushButton_5_clicked()
{
    if(is_add==0){
        inside_page * Inside_Page = new inside_page;
        this->close();
        Inside_Page->show();
    }
    else
    {
        searching_page * SP=new searching_page;
        this->close();
        SP->show();
    }
}

void searching_page::on_pushButton_3_clicked()
{
   detail *Detail=new detail(nullptr,0,current_client_ID);
   Detail->show();
}

void searching_page::on_pushButton_2_clicked()
{
   detail *Detail=new detail(nullptr,1,current_shipment_ID);
   Detail->show();
}

//新增，先清除页面
void searching_page::on_new_button_clicked()
{
    is_add=1;
    //开启数据库
    Mysql* list_1=new Mysql();
    list_1->db.open();
    QSqlQuery query(list_1->db);

    //获取下个订单自增id，并清空右边
    query.prepare("SELECT Auto_increment FROM information_schema.`TABLES` WHERE Table_Schema = 'foreign_trade_company' AND table_name = 'order_client' LIMIT 1;");
    if(query.exec())
        qDebug()<<"increment";
    query.first();
    int next_order_id=query.value(0).toInt();
    current_order_ID=next_order_id;
    ui->order_client_ID_edit->setText(QString::number(next_order_id));
    ui->staff_name_edit->clear();
    ui->client_name_edit->clear();
    ui->shipment_name_edit->clear();
    ui->product_ID_edit->clear();
    ui->product_type_edit->clear();
    ui->product_number_edit->clear();
    ui->departure_edit->clear();
    ui->destination_edit->clear();
    ui->finish_date_edit->clear();
    ui->way_edit->clear();

    ui->Client_list->clearSelection();

    ui->pushButton_2->setDisabled(1);
    ui->pushButton_3->setDisabled(1);

    ui->pushButton_4->setText("新增");
    ui->pushButton_5->setText("取消");
}

void searching_page::on_Facotry_enter_btn_clicked()
{
    ui->Factory_List->clear();
    if(ui->comboBox_2->currentIndex()==0)
    {
        qDebug()<<"0";

        Mysql* list_1=new Mysql();
        list_1->db.open();
        QSqlQuery query(list_1->db);

        query.exec("select order_factory_ID,factory_name from order_factory natural join factory ORDER BY order_factory_ID;");
        int i=0;
        while(query.next())
        {
            ui->Factory_List->insertItem(i,"订单号："+query.value(0).toString()+"\t工厂名称："+query.value(1).toString());
            i++;
        }
    }
    else if(ui->comboBox_2->currentIndex()==1)
    {
        QString search=ui->search_edit_2->text();
        qDebug()<<"1";

        qDebug()<<search;
        Mysql* list_1=new Mysql();
        list_1->db.open();
        QSqlQuery query(list_1->db);

        query.prepare("select order_factory_ID,factory_name from order_factory natural join factory"
                   " where order_factory_ID="+search+" order by order_factory_ID");
        if(query.exec())
            qDebug()<<"yes";
        else
            qDebug()<<"no";
        int i=0;
        while(query.next())
        {
            ui->Factory_List->insertItem(i,"订单号："+query.value(0).toString()+"\t工厂名称："+query.value(1).toString());
            i++;
        }
    }
    else if(ui->comboBox_2->currentIndex()==2)
    {
        qDebug()<<"2";

        Mysql* list_1=new Mysql();
        list_1->db.open();
        QSqlQuery query(list_1->db);

        query.prepare("select order_factory_ID,factory_name from order_factory natural join factory where factory_name like '"
                      +ui->search_edit_2->text()+
                      "%' order by order_factory_ID");
        int i=0;
        if(query.exec())
            qDebug()<<"yes";
        else
            qDebug()<<"no";
        while(query.next())
        {
            ui->Factory_List->insertItem(i,"订单号："+query.value(0).toString()+"\t工厂名称："+query.value(1).toString());
            i++;
        }
     }
}

//factory页修改按钮
void searching_page::on_pushButton_8_clicked()
{
    Mysql* list_1=new Mysql();
    list_1->db.open();
    QSqlQuery query(list_1->db);

    if(is_add_2==0){
        query.exec("select order_factory_id "
                   "from order_factory "
                   "where order_factory_ID ="+QString::number(current_order_ID_2));
        query.first();
        int this_order_factory_id = query.value(0).toInt();

        query.prepare("CALL update_order_factory(?,?,?,?,?,?,?)");
        query.addBindValue(QString::number(this_order_factory_id));
        query.addBindValue(ui->factory_name_edit->text());
        query.addBindValue(ui->staff_name_edit_2->text());
        query.addBindValue(ui->product_ID_edit_2->text());
        query.addBindValue(ui->product_type_edit_2->text());
        query.addBindValue(ui->product_number_edit_2->text());
        query.addBindValue(ui->finish_date_edit_2->text());


        if(query.exec()){
            QMessageBox::information(nullptr,"成功","信息已录入");
            query.exec("select factory_id from order_factory where order_factory_ID="+QString::number(current_order_ID_2));
            query.first();
            current_factory_ID=query.value(0).toInt();
        }
        else
            QMessageBox::information(nullptr,"失败","请检查是否有输入错误");
        }
    else
    {

        query.prepare("CALL insert_order_factory(?,?,?,?,?,?,?)");
        query.addBindValue(QString::number(current_factory_ID));
        query.addBindValue(ui->factory_name_edit->text());
        query.addBindValue(ui->staff_name_edit_2->text());
        query.addBindValue(ui->product_ID_edit_2->text());
        query.addBindValue(ui->product_type_edit_2->text());
        query.addBindValue(ui->product_number_edit_2->text());
        query.addBindValue(ui->finish_date_edit_2->text());

        if(query.exec()){
            qDebug()<<"insert yes";
            QMessageBox::information(nullptr,"新增","新增成功");
        }
        else{
            qDebug()<<"insert no";
            QMessageBox::information(nullptr,"失败","请确认是否有输入错误");
        }
    }
}

void searching_page::on_Factory_List_itemSelectionChanged()
{
    QString search=ui->search_edit_2->text();
    int index=0;
    //开启数据库
    Mysql* list_1=new Mysql();
    list_1->db.open();
    QSqlQuery query(list_1->db);

    //获取产品编号
    if(ui->comboBox_2->currentIndex()==0)
    {
        query.exec("select order_factory_ID,factory_name from order_factory natural join factory ORDER BY order_factory_ID;");
        query.first();
        while(index!=ui->Factory_List->currentIndex().row())
        {
            query.next();
            index++;
        }
        current_order_ID_2=query.value(0).toInt();
    }
    else if(ui->comboBox_2->currentIndex()==1)
    {
        query.prepare("select order_factory_ID,factory_name from order_factory natural join factory"
                      " where order_factory_ID="+ui->search_edit_2->text()+" order by order_factory_ID");
        query.exec();query.first();
        while(index!=ui->Factory_List->currentIndex().row())
        {
            query.next();
            index++;
        }
        current_order_ID_2=query.value(0).toInt();
    }
    else if(ui->comboBox_2->currentIndex()==2)
    {
        query.prepare("select order_factory_ID,factory_name from order_factory natural join factory where factory_name like '"
                      +ui->search_edit_2->text()+
                      "%' order by order_factory_ID");
        query.exec();query.first();
        while(index!=ui->Factory_List->currentIndex().row())
        {
            query.next();
            index++;
        }
        current_order_ID_2=query.value(0).toInt();
    }
    qDebug()<<"index="<<current_order_ID_2;

    query.exec("select order_factory_id,staff_name,factory_name,product_ID,type,"
               "number_of_product,finish_date,factory_id "
               "from order_factory natural join staff natural join factory "
               "where order_factory_ID ="+QString::number(current_order_ID_2));
    query.first();
    ui->order_factory_ID_edit->setText(query.value(0).toString());
    ui->staff_name_edit_2->setText(query.value(1).toString());
    ui->factory_name_edit->setText(query.value(2).toString());
    ui->product_ID_edit_2->setText(query.value(3).toString());
    ui->product_type_edit_2->setText(query.value(4).toString());
    ui->product_number_edit_2->setText(query.value(5).toString());
    ui->finish_date_edit_2->setText(query.value(6).toString());

    current_factory_ID=query.value(7).toInt();
}

//查看工厂信息
void searching_page::on_pushButton_9_clicked()
{
    detail *Detail=new detail(nullptr,2,current_factory_ID);
    Detail->show();
}

//factory页返回键
void searching_page::on_pushButton_7_clicked()
{
    if(is_add_2==0){
        inside_page * Inside_Page = new inside_page;
        this->close();
        Inside_Page->show();
    }
    else
    {
        searching_page * SP=new searching_page;
        this->close();
        SP->show();
    }
}

void searching_page::on_new_button_2_clicked()
{
    is_add_2=1;
    //开启数据库
    Mysql* list_1=new Mysql();
    list_1->db.open();
    QSqlQuery query(list_1->db);

    //获取下个订单自增id，并清空右边
    query.prepare("SELECT Auto_increment FROM information_schema.`TABLES` WHERE Table_Schema = 'foreign_trade_company' AND table_name = 'order_factory' LIMIT 1;");
    if(query.exec())
        qDebug()<<"increment";
    query.first();
    int next_order_id=query.value(0).toInt();
    current_order_ID_2=next_order_id;
    ui->order_factory_ID_edit->setText(QString::number(next_order_id));
    ui->staff_name_edit_2->clear();
    ui->factory_name_edit->clear();
    ui->product_ID_edit_2->clear();
    ui->product_type_edit_2->clear();
    ui->product_number_edit_2->clear();
    ui->finish_date_edit_2->clear();

    ui->Factory_List->clearSelection();

    ui->pushButton_9->setDisabled(1);

    ui->pushButton_8->setText("新增");
    ui->pushButton_7->setText("取消");
}

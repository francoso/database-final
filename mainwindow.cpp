#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//当登录按钮被点击
void MainWindow::on_pushButton_clicked()
{
    //获取两个输入框的值
    QString account = ui->lineEdit->text();
    int account_num = account.toInt();
    QString password = ui->lineEdit_2->text();

    //操作数据库
    Mysql *staff=new Mysql();
    if(staff->db.open())
    {
         QSqlQuery query(staff->db);
         query.exec("select staff_id,password from staff");
         while(query.next()){
             if(query.value(0)==account_num&&query.value(1)==password){
                 inside_page * Inside_Page = new inside_page;
                 this->hide();
                 Inside_Page->show();
             }
         }
    }
}

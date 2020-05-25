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
    staff->db.open();
    if(staff->db.open())
    {
         QSqlQuery query(staff->db);
         query.exec("select Staff_ID,password from staff");
         while(query.next()){
             if(query.value(0).toInt()==account_num&&query.value(1).toString()==password){
                 inside_page * Inside_Page = new inside_page(nullptr,account_num);
                 this->close();
                 Inside_Page->show();
                 return;
             }
         }
         QMessageBox::information(nullptr,"登陆错误","请重试");
    }
    return;
}

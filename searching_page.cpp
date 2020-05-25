#include "searching_page.h"
#include "ui_searching_page.h"

searching_page::searching_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searching_page)
{
    ui->setupUi(this);
}

searching_page::~searching_page()
{
    delete ui;
}

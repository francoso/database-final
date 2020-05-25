#include "inside_page.h"
#include "ui_inside_page.h"
#include "searching_page.h"
#include "ui_searching_page.h"
#include "staff_page.h"
#include "ui_staff_page.h"

inside_page::inside_page(QWidget *parent,int ID) :
    QWidget(parent),
    ui(new Ui::inside_page)
{
    ui->setupUi(this);
    id=ID;
}

inside_page::~inside_page()
{
    delete ui;
}

void inside_page::on_search_clicked()
{
    searching_page * Searching_Page = new searching_page;
    this->hide();
    Searching_Page->show();
    return;
}

void inside_page::on_staff_clicked()
{
    staff_page * Staff_Page = new staff_page(nullptr,id);
    this->hide();
    Staff_Page->show();
    return;
}

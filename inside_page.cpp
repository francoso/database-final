#include "inside_page.h"
#include "ui_inside_page.h"

inside_page::inside_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inside_page)
{
    ui->setupUi(this);
}

inside_page::~inside_page()
{
    delete ui;
}

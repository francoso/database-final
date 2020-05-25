#ifndef STAFF_PAGE_H
#define STAFF_PAGE_H

#include <QWidget>

namespace Ui {
class staff_page;
}

class staff_page : public QWidget
{
    Q_OBJECT
    int id;

public:
    explicit staff_page(QWidget *parent = nullptr,int Id=-1);
    ~staff_page();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::staff_page *ui;
};

#endif // STAFF_PAGE_H

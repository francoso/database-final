#ifndef INSIDE_PAGE_H
#define INSIDE_PAGE_H

#include <QWidget>

namespace Ui {
class inside_page;
}

class inside_page : public QWidget
{
    Q_OBJECT
    int id;

public:
    explicit inside_page(QWidget *parent = nullptr,int Id=-1);
    ~inside_page();

private slots:
    void on_search_clicked();

    void on_staff_clicked();

private:
    Ui::inside_page *ui;
};

#endif // INSIDE_PAGE_H

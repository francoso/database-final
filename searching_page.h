#ifndef SEARCHING_PAGE_H
#include "mysql.h"

#define SEARCHING_PAGE_H

#include <QMainWindow>

namespace Ui {
class searching_page;
}

class searching_page : public QMainWindow
{
    int id;
    int current_Client_ID;
    Q_OBJECT

public:
    explicit searching_page(QWidget *parent = nullptr);
    ~searching_page();


private slots:

    void on_pushButton_clicked();

    void on_Client_list_itemSelectionChanged();

    void on_pushButton_4_clicked();

private:
    Ui::searching_page *ui;
};

#endif // SEARCHING_PAGE_H

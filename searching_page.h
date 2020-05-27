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
    int current_order_ID;
    int current_client_ID;
    int current_shipment_ID;
    bool is_add;
    int max_row_client;

    int current_order_ID_2;
    int current_factory_ID;
    bool is_add_2;
    int max_row_factory;

    int current_product_ID;
    QString current_type;
    int current_factory_ID_2;
    bool is_add_3;
    int max_row_product;

    Q_OBJECT

public:
    explicit searching_page(QWidget *parent = nullptr);
    ~searching_page();


private slots:

    void on_pushButton_clicked();

    void on_Client_list_itemSelectionChanged();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_new_button_clicked();

    void on_Facotry_enter_btn_clicked();

    void on_pushButton_8_clicked();

    void on_Factory_List_itemSelectionChanged();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_new_button_2_clicked();

    void on_product_enter_button_clicked();

    void on_Product_List_itemSelectionChanged();

    void on_p3_change_btn_clicked();

    void on_new_button_3_clicked();

    void on_p3_return_btn_clicked();

    void on_p3_check_btn_clicked();

private:
    Ui::searching_page *ui;
};

#endif // SEARCHING_PAGE_H

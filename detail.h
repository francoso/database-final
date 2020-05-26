#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>

namespace Ui {
class detail;
}

class detail : public QWidget
{
    Q_OBJECT
    int type;
    int id;
public:
    explicit detail(QWidget *parent = nullptr,int Type=-1,int ID=-1);
    ~detail();

private slots:
    void on_pushButton_clicked();

private:
    Ui::detail *ui;
};

#endif // DETAIL_H

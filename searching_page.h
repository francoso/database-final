#ifndef SEARCHING_PAGE_H
#define SEARCHING_PAGE_H

#include <QMainWindow>

namespace Ui {
class searching_page;
}

class searching_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit searching_page(QWidget *parent = nullptr);
    ~searching_page();

private:
    Ui::searching_page *ui;
};

#endif // SEARCHING_PAGE_H

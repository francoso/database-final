#ifndef INSIDE_PAGE_H
#define INSIDE_PAGE_H

#include <QWidget>

namespace Ui {
class inside_page;
}

class inside_page : public QWidget
{
    Q_OBJECT

public:
    explicit inside_page(QWidget *parent = nullptr);
    ~inside_page();

private:
    Ui::inside_page *ui;
};

#endif // INSIDE_PAGE_H

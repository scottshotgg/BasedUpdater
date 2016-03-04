#ifndef ABOUTPOPUP_H
#define ABOUTPOPUP_H

#include <QDialog>

namespace Ui {
class aboutpopup;
}

class aboutpopup : public QDialog
{
    Q_OBJECT

public:
    explicit aboutpopup(QWidget *parent = 0);
    ~aboutpopup();

private:
    Ui::aboutpopup *ui;
};

#endif // ABOUTPOPUP_H

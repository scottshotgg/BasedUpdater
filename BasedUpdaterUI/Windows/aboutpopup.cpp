#include "aboutpopup.h"
#include "ui_aboutpopup.h"

aboutpopup::aboutpopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutpopup)
{
    ui->setupUi(this);
}

aboutpopup::~aboutpopup()
{
    delete ui;
}

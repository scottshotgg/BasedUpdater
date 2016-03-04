#include "basedupdater.h"
#include "ui_basedupdater.h"

BasedUpdater::BasedUpdater(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasedUpdater)
{
    ui->setupUi(this);
}

BasedUpdater::~BasedUpdater()
{
    delete ui;
}

#ifndef BASEDUPDATER_H
#define BASEDUPDATER_H

#include <QMainWindow>

namespace Ui {
class BasedUpdater;
}

class BasedUpdater : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasedUpdater(QWidget *parent = 0);
    ~BasedUpdater();

private:
    Ui::BasedUpdater *ui;
};

#endif // BASEDUPDATER_H

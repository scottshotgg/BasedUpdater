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

private slots:
    void on_pushButton_clicked();

    void on_actionAbout_triggered();

    void on_filePath_lineEdit_textEdited(const QString &arg1);

private:
    Ui::BasedUpdater *ui;
};

#endif // BASEDUPDATER_H

#include "basedupdater.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BasedUpdater w;
    w.show();

    return a.exec();
}

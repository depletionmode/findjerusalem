#include <QtGui/QApplication>
#include "findjerusalem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindJerusalem w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}

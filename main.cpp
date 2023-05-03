#include "qhtmlpen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QHTMLPen w;
    w.show();
    return a.exec();
}

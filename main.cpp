#include "quotes.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Quotes w;
    w.show();
    return a.exec();
}

#include <QtGui>
#include <QApplication>
#include <QWidget>
#include "smartdisplay.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SmartDisplay client;
    client.show();

    return a.exec();
}

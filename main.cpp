#include "Printer_Ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Printer_Ui w;
    w.show();

    return a.exec();
}

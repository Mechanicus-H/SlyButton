#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("smile.png"));
    Widget w;
    w.show();

    return a.exec();
}

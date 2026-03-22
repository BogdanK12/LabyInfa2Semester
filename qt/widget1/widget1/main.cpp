#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(400, 500);
    w.setWindowTitle("Just a window.");
    w.show();
    QIcon programIcon("/home/bbquiz/proga/LabyInfa2Semester/qt/widget1/widget1/icons/qt.jpg");
    w.setWindowIcon(programIcon);
    w.setWindowOpacity(0.5);
    return a.exec();
}

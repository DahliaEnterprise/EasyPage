#include "widget.h"
#include "head.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Boot the "head" of the program.
    head * head_of_body = 0;
    head_of_body = new head();


    Widget * w = new Widget();
    w->initalize();
    w->set_head(head_of_body);
    w->show();

    return a.exec();
}

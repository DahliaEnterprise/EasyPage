#include <stdlib.h>
#include <string.h>
#include "main_operation.h"
#include <QApplication>
#include <QDebug>
#include <QDirIterator>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
/* maynot need this
    char * environment_variable_result = 0;
    while(environment_variable_result == 0){environment_variable_result =(char*) malloc(4095*sizeof(char));}
    memset(environment_variable_result, '\0', 4095);
    environment_variable_result = getenv("PWD");
*/

//qDebug() << argv[0];
//qDebug() << argc;

    if(argc > 1)
    {
        //make a seperator line within the terminal.
        qDebug() << "";
        main_operation * mainop = new main_operation();
        unsigned short int error = mainop->initialize(argc, argv);
        if(error == 0)
        {
            mainop->search_loop();
        }else{
            qDebug() << "init error occured";
        }

        delete mainop;
        //make a seperator line within the terminal
        qDebug() << "";
    }
a.exit(0);
    return 0;
}

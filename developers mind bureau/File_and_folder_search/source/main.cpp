#include <stdlib.h>
#include <string.h>
#include "main_operation.h"
#include <QApplication>
#include <QDebug>
#include <QDirIterator>
unsigned short int continue_search_loop;
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
             continue_search_loop = 1;
            while(continue_search_loop == 1)
            {
                mainop->search_loop();
            }

            delete mainop;
        }else if(error == 2)
        {
            qDebug() << "End of instructions";
        }else if(error == 3)
        {
            qDebug() << "not enough inputs.";
        }else if(error == 4)
        {
            qDebug() << "base directory is not a directory";
        }else if(error == 5)
        {
            qDebug() << "base directory is empty";
        }else{
            qDebug() << "base directory is not a directoru.";
        }


        //make a seperator line within the terminal
        qDebug() << "";
    }
a.exit(0);
    return 0;
}

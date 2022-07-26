#include "main_operation.h"

main_operation::main_operation(QObject *parent) : QObject(parent)
{

}

unsigned short int main_operation::initialize(int argc, char *argv[])
{
    unsigned short int error = 0;

    recursive_enabled = 0;

    QString recursive_string("recursive");

    folder_and_file_check = new QFileInfo();

    requested_base_is_directory = 0;

    unsigned short int change_occured = 0;


    //determine run prechecks to prevent catstraphic user envoked damages (what other wise would have been )produced by this apps.
    int index = 1;
    while(index < argc)
    {
        change_occured = 0;
        //qDebug() << argv[index] << index << "\n";
        if(index < (argc-1))
        {
             if(recursive_enabled == 0)
             {//this is a speedup check if statement
                 if(QString(argv[index]).compare(recursive_string, Qt::CaseInsensitive) == 0)
                 {
                   recursive_enabled = 1;
                   change_occured = 1;
                   qDebug() << "recursive enabled";
               }
            }
        }

        if(change_occured == 0)
        {
            if(index == (argc-2))
            {
                //check iffolder and does exist.
                folder_and_file_check->setFile(QString("%1").arg(argv[index]));
                if(folder_and_file_check->isDir() == true)
                {
                    requested_base_is_directory = 1;
                }else{
                    index = argc;
                    error = 1;
                }
            }
        }

        if(change_occured == 0)
        {
            //if last one, then this is the "search query"
            if(index == (argc-1))
            {
                qDebug() << "";
                query = argv[index];
                qDebug() << "found query: " << query;
                qDebug() << "";
            }
        }
        index = index +1;
    }

    return error;
}

void main_operation::search_loop()
{
    direct_trail = new QVector<char *>();

    unsigned short int keep_looping = 1;
    while(keep_looping == 1)
    {
        //if direct trail is empty, then get first ditectory, then go to deepest folder search if recursive is enabled.
        if(direct_trail->count() == 0)
        {
            //just the first folder

        }
    }
}

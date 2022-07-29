#include "main_operation.h"

main_operation::main_operation(QObject *parent) : QObject(parent)
{

}

unsigned short int main_operation::initialize(int argc, char *argv[])
{
    unsigned short int error = 0;

    recursive_enabled = 0;

    QString recursive_string("recursive");


    //determine run prechecks to prevent catstraphic user envoked damages (what other wise would have been )produced by this apps.
    int user_instructions = strncmp(argv[1], "instructions", 12);
    if(user_instructions== 0)
    {
        qDebug() << "";
        qDebug() << "shastafind options \"directory to search\" \"search phrase\"";
        qDebug() << "";
        qDebug() << "recursive search through folders inside of folders.";

        error =2;
    }else{
        //check if at least two arguments we entered.
        if(argc <= 2)
        {
            error = 3;

        }else if(argc >= 3)
        {
           //
           user_requested_base_directory = QString();
           user_requested_base_directory.append(QString("%1").arg(argv[1]));
           QFileInfo * is_dir = new QFileInfo();
           is_dir->setFile(user_requested_base_directory);
           if(is_dir->isDir() == false)
           {
               error = 4;
           }else{
               trail_current_index = new QVector<QFileInfo>();
               QDir filesandfolders;
               filesandfolders.setPath(user_requested_base_directory);
               filesandfolders.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::NoDot);
               QList<QFileInfo> list = filesandfolders.entryInfoList();
               if(list.size() == 0)
               {
                   error = 5;
               }else if(list.size() > 0)
               {
                   trail_current_index->append(list.at(0));

               }
           }
        }
    }

    return error;
}

void main_operation::search_loop()
{
    //
    QFileInfo tail = trail_current_index->at(trail_current_index->size()-1);
    if(tail.isDir() == true)
    {
        qDebug() << tail.absoluteFilePath();

        QDir filesandfolders;
        filesandfolders.setPath(tail.absoluteFilePath());
        filesandfolders.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::NoDot);
        QList<QFileInfo> list = filesandfolders.entryInfoList();
        if(list.size() == 0)
        {
            qDebug() <<  "folder empty";
        }else if(list.size() > 0)
        {
            //
            QFileInfo item = list.at(0);
            trail_current_index->append(item);
            qDebug() << item.absoluteFilePath();
        }
    }
}



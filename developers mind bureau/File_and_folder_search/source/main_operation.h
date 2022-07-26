#ifndef MAIN_OPERATION_H
#define MAIN_OPERATION_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QFileInfo>

class main_operation : public QObject
{
    Q_OBJECT
public:
    explicit main_operation(QObject *parent = nullptr);
    unsigned short int initialize(int argc, char *argv[]);
    void search_loop();

private:
    unsigned short int recursive_enabled;
    unsigned short int folder_location_found;
    char * query;
    QFileInfo * folder_and_file_check;
    unsigned short int requested_base_is_directory;

    QVector<char*> * direct_trail;


signals:

};

#endif // MAIN_OPERATION_H

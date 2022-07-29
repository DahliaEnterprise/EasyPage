#ifndef MAIN_OPERATION_H
#define MAIN_OPERATION_H

#include <stdlib.h>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QFileInfo>
#include <QDirIterator>
#include <QFile>
class main_operation : public QObject
{
    Q_OBJECT
public:

    explicit main_operation(QObject *parent = nullptr);
    unsigned short int initialize(int argc, char *argv[]);
    void search_loop();

private:
    unsigned short int recursive_enabled;
    QString user_requested_base_directory;
    QVector<QFileInfo> * trail_current_index;

signals:

};

#endif // MAIN_OPERATION_H

#ifndef TRAVERSE_FILES_AND_FOLDERS_H
#define TRAVERSE_FILES_AND_FOLDERS_H

#include "searchthread.h"

#include <QObject>
#include <QDebug>
#include <QDirIterator>
#include <QDir>

class traverse_files_and_folders : public QObject
{
    Q_OBJECT
public:
    explicit traverse_files_and_folders();

    void search(QString set_base_root_folder, QString set_search_text);

private:
    SearchThread * search_thread;
    QThread q_thread;

    QDirIterator * directory_iterator;

    QString base_root_folder;
    QString search_text;

signals:
    //private
    void start_search_thread();

    //public
    void sig_result(int);
    void finished_work();

private slots:
    void result(int);

};

#endif // TRAVERSE_FILES_AND_FOLDERS_H

#ifndef TRAVERSE_FILES_AND_FOLDERS_H
#define TRAVERSE_FILES_AND_FOLDERS_H

#include "searchthread.h"

#include <QObject>
#include <QDebug>

class traverse_files_and_folders : public QObject
{
    Q_OBJECT
public:
    explicit traverse_files_and_folders(QObject *parent = nullptr);
    void search(QString base_root_folder, QString search_text);

private:
    SearchThread * search_thread;
    QThread q_thread;

signals:
    //private
    void start_search_thread();

    //public
    void sig_result(int);

private slots:
    void result(int);

};

#endif // TRAVERSE_FILES_AND_FOLDERS_H

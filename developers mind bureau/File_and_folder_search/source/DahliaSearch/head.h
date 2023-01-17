#ifndef HEAD_H
#define HEAD_H

#include "traverse_files_and_folders.h"

#include <QObject>
#include <QDebug>


class head : public QObject
{
    Q_OBJECT
public:
    explicit head(QObject *parent = nullptr);
    void queue_search(QString root_location, QString search_option);

private:
    QString base_root_folder;
    QString search_text;


    traverse_files_and_folders * traverse;

signals:
    void sig_result(int number);
    void sig_finished_work();

private slots:
    void result(int number);
    void finished_work();

};

#endif // HEAD_H

#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QFileInfo>
#include <QMimeDatabase>

class SearchThread : public QObject
{
    Q_OBJECT

public:
    SearchThread();

    void set_search_text_and_file_folder_path(QString, QString);

private:
    QString search_text;
    QString next_file_folder_path;
    QMimeDatabase mime_db;

public slots:
    void do_work();

signals:
    void result(int);

};

#endif // SEARCHTHREAD_H

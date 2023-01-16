#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>

class SearchThread : public QObject
{
    Q_OBJECT

public:
    SearchThread();

public slots:
    void do_work();

signals:
    void result(int);

};

#endif // SEARCHTHREAD_H

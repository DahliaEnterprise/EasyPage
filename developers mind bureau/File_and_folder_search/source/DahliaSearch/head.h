#ifndef HEAD_H
#define HEAD_H

#include <QObject>

class head : public QObject
{
    Q_OBJECT
public:
    explicit head(QObject *parent = nullptr);

signals:

};

#endif // HEAD_H

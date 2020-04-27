#ifndef JSONABLE_H
#define JSONABLE_H

#include"common.h"
class Jsonable : public QObject
{
    Q_OBJECT
public:
    Jsonable(QObject *parent = nullptr);
    virtual void readfromJson(string _path) = 0;
    virtual string writetoJson() = 0;

};

#endif // JSONABLE_H

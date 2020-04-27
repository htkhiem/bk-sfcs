#ifndef JSONABLE_H
#define JSONABLE_H

#include <QObject>
#include"../../backend/common.h"
class Jsonable
{
    Q_OBJECT
public:
    Jsonable();
    virtual void readfromJson(string _path) = 0;
    virtual string writetoJson() = 0;

};

#endif // JSONABLE_H

#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "food.h"

class Stall: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString stallName READ getStallName)
public:
    QString stallName;
    QVector<QFood> menu;
    Stall(QObject *parent = nullptr);
    Stall(const Stall &_stall, QObject *parent = nullptr);
    Stall& operator=(const Stall &);
    string imagePath;
public slots:

    QVector<QFood> getMenu() const;
    bool addFood(QFood item);
    bool removeFood(QFood item);
    string getImagePath();
    void setImagePath();
    QString getStallName();

};

extern QVector<Stall> stallist;
void writeStall(const string filename);
void  loadStall(const string filename);
#endif // MENU_H

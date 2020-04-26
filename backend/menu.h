#ifndef MENU_H
#define MENU_H
#include "food.h"


class Stall: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString stallName READ getStallName)


public:
    QString stallName;
    QVector<QFood> menu;
    Stall();
    Stall(const Stall &_stall);
    Stall& operator=(const Stall &);
    string imagePath;
public slots:

    QVector<QFood> getMenu() const;
    bool addFood(QFood item);
    bool removeFood(QFood item);
    void getImage();
    void setImage();
    QString getStallName();

};

extern QVector<Stall> stallist;
void writeStall(const string filename);
void  loadStall(const string filename);
#endif // MENU_H

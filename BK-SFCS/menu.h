#ifndef MENU_H
#define MENU_H
#include "food.h"

class menu
{
    Q_OBJECT
    Q_PROPERTY(QString stallName READ getStallName)
    Q_PROPERTY(void addFood WRITE addFood)
    Q_PROPERTY(void removeFood WRITE removeFood)
    QString stallName;
    QVector<QFood> foodlist;

public slots:
        menu();
    void getFoodList();
    void addFood();
    void removeFood();
    void loadMenu();
    void writeMenu();
    QString getStallName();

};

#endif // MENU_H

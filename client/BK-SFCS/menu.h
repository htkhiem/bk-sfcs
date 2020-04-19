#ifndef MENU_H
#define MENU_H
#include "food.h"

using namespace rapidjson;
class stall
{
    Q_OBJECT
    Q_PROPERTY(QString stallName READ getStallName)
    Q_PROPERTY(void addFood WRITE addFood)
    Q_PROPERTY(void removeFood WRITE removeFood)
    QString stallName;
public:
    QVector<QFood> menu;

public slots:
       stall();
    void getMenu();
    void addFood(QFood item);
    void removeFood(QFood item);

    QString getStallName();

};
class stalllist{
    QVector<stall> stallList;
    void loadStall(const string filename);
    void writeStall(const string filename);
};

#endif // MENU_H

#ifndef MENU_H
#define MENU_H
#include "food.h"

using namespace rapidjson;
class menu
{
    Q_OBJECT
    Q_PROPERTY(QString stallName READ getStallName)
    Q_PROPERTY(void addFood WRITE addFood)
    Q_PROPERTY(void removeFood WRITE removeFood)
    QString stallName;
public:
    QVector<QFood> foodlist;

public slots:
        menu();
    void getFoodList();
    void addFood();
    void removeFood();

    QString getStallName();

};
class menulist{
    QVector<menu> menulist;
    void loadMenu(const string filename);
    void writeMenu(const string filename);
};

#endif // MENU_H

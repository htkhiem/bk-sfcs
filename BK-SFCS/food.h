#ifndef FOOD_H
#define FOOD_H
#include "common.h"
class QFood {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString type READ getType)

public:
    QFood();
    string name, type,description;
    double price=0;
public slots:
    QString getName();
    QString getType();
    QString getDescription();
    double getPrice();
    bool isSelected();
    void setSelected(bool _sel);
};
#endif // FOOD_H

#ifndef FOOD_H
#define FOOD_H
#include "common.h"
class QFood {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString type READ getType)

public:
    QFood();
    bool select;
    QString name, type,description;
    double price=0;
public slots:
    QString getName();
    void setName(QString name);
    QString getType();
    void setType(QString type);
    QString getDescription();
    void setDescription(QString des);
    double getPrice();
    void setPrice(double price);
    bool isSelected();
    void setSelected(bool _sel);
};
#endif // FOOD_H

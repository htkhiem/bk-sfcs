#ifndef FOOD_H
#define FOOD_H
#include "common.h"
class QFood : public QObject {

    Q_OBJECT
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString type READ getType)
public:

    QFood(QObject *parent = nullptr);
    QFood(const QFood &_food, QObject *parent = nullptr);
    QFood& operator=(const QFood &);
    bool select;
    QString name, type,description;
    double price=0;
public slots:

    QString getName() const;
    void setName(QString name);
    QString getType()const;
    void setType(QString type);
    QString getDescription()const;
    void setDescription(QString des);
    double getPrice()const;
    void setPrice(double price);
    bool isSelected()const;
    void setSelected(bool _sel);
};
#endif // FOOD_H

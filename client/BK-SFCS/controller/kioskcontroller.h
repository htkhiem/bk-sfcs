#ifndef KIOSKCONTROLLER_H
#define KIOSKCONTROLLER_H

#include <QObject>
#include "../../backend/BK-SFCS-Backend/src/abstractcontroller.h"

class KioskController : public AbstractController
{
    Q_OBJECT
public:
    explicit KioskController(QQmlApplicationEngine *eng, QObject *parent = nullptr);

signals:

};

#endif // KIOSKCONTROLLER_H

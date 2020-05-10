#ifndef STALLMGMTCONTROLLER_H
#define STALLMGMTCONTROLLER_H

#include <QObject>
#include "../../../backend/BK-SFCS-Backend/src/abstractcontroller.h"

class StallMgmtController : public AbstractController
{
  Q_OBJECT
public:
      QList<QObject *> logs_db;
      QList<QObject*> waitlist_view_model;
      explicit StallMgmtController(QQmlApplicationEngine* eng, QObject *parent = nullptr);
      bool login(const QString& name, const QString& psw);
      bool logout();
      void updateWaitlistViewModel();
      void populateMgmtGraphs();
      bool loginAsManager(const QString& psw);
      void addFood(QFood * food);
      void editFood(QFood * food);
      bool removeFood(const QString& name);
signals:

};

#endif // STALLMGMTCONTROLLER_H

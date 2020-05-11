#ifndef STALLMGMTCONTROLLER_H
#define STALLMGMTCONTROLLER_H

#include <QObject>
#include "../../../backend/BK-SFCS-Backend/src/abstractcontroller.h"

class StallMgmtController : public AbstractController
{
  Q_OBJECT
  bool is_logged_in;
public:
    QList<QObject *> logs_db;
    QList<QObject*> waitlist_view_model;
    explicit StallMgmtController(QQmlApplicationEngine* eng, QObject *parent = nullptr);
public slots:


      bool login(int idx, const QString& psw);
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

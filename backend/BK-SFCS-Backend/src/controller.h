#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "common.h"
#include "menu.h"

class Controller : public QObject {
  Q_OBJECT
public:
  explicit Controller(QObject *parent = nullptr);
public slots:
  
  /** Main program loop Emits finished() after leaving loop. */
  void run();
signals:
  void finished();
private:

  QList<QObject*> stall_db;

  size_t DisplayStallList();
  void RegisterStall();
  void RemoveStall();

  void Login();
  void Logout();

  size_t current_stall_idx;

  void AddFoodItem();
  void RemoveFoodItem();
  void EditFoodItem();

  void WriteData();
  void ReadData();
};

#endif // CONTROLLER_H

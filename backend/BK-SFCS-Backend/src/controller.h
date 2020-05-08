#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "common.h"
#include "menu.h"

class Controller : public QObject {
  Q_OBJECT
public:
  explicit Controller(QObject *parent = nullptr);
    void WriteData();
    void RegisterStall();
public slots:
  
  /** Main program loop Emits finished() after leaving loop. */
  void run();
signals:
  void finished();
private:
  bool logged_in;
  QList<QObject*> stall_db;
  Stall current_stall;

  size_t DisplayStallList();
  //void RegisterStall();
  bool RemoveStall();

  int Login();
  bool Logout();

  size_t current_stall_idx;

  void AddFoodItem();
  void RemoveFoodItem();
  void EditFoodItem();

  //void WriteData();
  void ReadData();
};

#endif // CONTROLLER_H

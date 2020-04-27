#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "common.h"

class Controller : public QObject {
  Q_OBJECT
public:
  explicit Controller(QObject *parent = nullptr);
public slots:
  
  /** Main program loop Emits finished() after leaving loop. */
  void run() {
    cout << "BK-SFCS ADMINISTRATIVE CONTROL PANEL\n";
    emit finished();
  }
signals:
  void finished();
};

#endif // CONTROLLER_H

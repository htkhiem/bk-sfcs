#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "food.h"
#include "jsonable.h"

class Stall : public Jsonable {
  Q_OBJECT
  Q_PROPERTY(QString stallName READ getStallName)
public:
  /**
   * Basic constructor.
   * @param parent Pointer to parent QObject, if any.
   */
  Stall(QObject *parent = nullptr);
  
  /**
   * Copy constructor.
   * @param _stall Source object.
   * @param parent Pointer to parent QObject, if any.
   */
  Stall(const Stall &_stall, QObject *parent = nullptr);

  /** Basic fields */
  QString stallName;
  QVector<QFood> menu;
  QString imagePath;
  
  /**
   * Explict operator= overload.
   * @param _other Another Stall to compare. 
   * @return True on equal, false otherwise.
   */
  Stall &operator=(const Stall & _other);
  
  /**
   * Read data from a JSON object from disk.
   * @param json JSON object to read from.
   */
  void read(const QJsonObject &json);
  
  /**
   * Write to a JSON object for writing to file on disk.
   * @param json Target JSON object to write to.
   */
  void write(QJsonObject &json) const;
public slots:
  /** Basic getters/setters */
  QVector<QFood> getMenu() const;
  bool addFood(QFood item);
  bool removeFood(QFood item);
  QString getImagePath();
  void setImagePath();
  QString getStallName();
};
#endif // MENU_H

#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "food.h"
#include "jsonable.h"

class Stall : public Jsonable {
  Q_OBJECT
  Q_PROPERTY(QString stallName READ getStallName WRITE setStallName)
  Q_PROPERTY(QUrl imagePath READ getImagePath WRITE setImagePath)
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
  QString image_name;
  QString password;
  QString mgmt_password;
  
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
  const QVector<QFood>* getMenu() const;
  QVector<QFood>* getEditableMenu();
  bool addFood(QFood item);
  bool removeFood(QFood item);
  /** Returns absolute path to copy stored in stall folder */
  QUrl getImagePath() const;
  /** Copies image to stall folder then set name to imagePath field */
  void setImagePath(const QUrl& imgpath);
  QString getStallName() const;
  void setStallName(const QString& name);
  QString getPassword() const;
  void setPassword(QString password);
  QString getMgmtPassword() const;
  void setMgmtPassword(QString mgmt_password);

};
#endif // MENU_H

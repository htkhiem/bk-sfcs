#ifndef JSONABLE_H
#define JSONABLE_H

#include "common.h"
class Jsonable : public QObject {
  Q_OBJECT
public:
  
  /**
   * Constructor for QObject-based Jsonable
   * @param parent Pointer to parent QObject if any.
   */
  Jsonable(QObject *parent = nullptr);

  /**
   * Destructor for QObject-based Jsonable
   */
  ~Jsonable();
  
  /**
   * Pure virtual read function from JSON object from file.
   * @param json Source JSON object.
   */
  virtual void read(const QJsonObject &json) = 0;
  
  /**
   * Pure virtual write function to JSON object for writing to file.
   * @param json Target JSON object to write to.
   */
  virtual void write(QJsonObject &json) const = 0;
};

#endif // JSONABLE_H

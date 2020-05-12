#ifndef FOOD_H
#define FOOD_H
#include "common.h"
#include "jsonable.h"
class QFood : public Jsonable {

  Q_OBJECT
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(QString type READ getType WRITE setType)
  Q_PROPERTY(QString description READ getDescription WRITE setDescription)
  Q_PROPERTY(double price READ getPrice WRITE setPrice)
  Q_PROPERTY(int estimatedTime READ getTime WRITE setTime)
  Q_PROPERTY(bool isOOS READ isOOS WRITE setOOS)
public:
  
  /**
   * Basic constructor, links to QObject through Jsonable.
   * @param parent Pointer to parent QObject (if there is any).
   */
  QFood(QObject *parent = nullptr);
  /**
   * Copy constructor.
   * @param _food Copy source.
   * @param parent Pointer to parent QObject (if any).
   */
  QFood(const QFood &_food, QObject *parent = nullptr);
  
  /**
   * Explicit overload for operator=.
   */
  QFood &operator=(const QFood &);
  
  /** Basic fields  */
  QString name, type, description, image_name;
  double price;
  bool is_OOS;
  int estimated_time;
  
  /**
   * Read from a Food-type JSON object.
   * @param json Object read from file.
   */
  void read(const QJsonObject &json);
  
  /**
   * Write to a JSON object for writing to file on disk.
   * @param json Target object to write into.
   */
  void write(QJsonObject &json) const;
public slots:
  /** Basic getters/setters */
  /** getImagePath and setImagePath needs stall name for absolute path */
  QUrl getImagePath(const QString& stall_name) const;
  void setImagePath(const QString& stall_name, const QUrl& image_path);
  QString getName() const;
  void setName(QString name);
  QString getType() const;
  void setType(QString type);
  QString getDescription() const;
  void setDescription(QString des);
  double getPrice() const;
  void setPrice(double price);
  bool isOOS();
  void setOOS(bool oos);
  void setTime(int _time);
  int getTime();
};
#endif // FOOD_H

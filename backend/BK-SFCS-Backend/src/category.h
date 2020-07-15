#ifndef CATEGORY_H
#define CATEGORY_H

#include "common.h"
#include <QObject>

class Category : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(QString symbol READ getSymbol WRITE setSymbol)
  Q_PROPERTY(QColor colorStart READ getStartColor WRITE setStartColor)
  Q_PROPERTY(QColor colorEnd READ getEndColor WRITE setEndColor)
  Q_PROPERTY(bool visible READ isVisible WRITE toggleVisibility)
  QString name;
  QString symbol; // has to be QString, we don't want to deal with wchar_t for
                // emojis here.
  QColor color_start, color_end;
  bool visible;

public:
  explicit Category(QObject *parent = nullptr);
  Category(const QString &cat_name, QString sym, QColor start, QColor end,
           QObject *parent = nullptr);
public slots:
  // Getters and setters
  QString getName() const;
  void setName(const QString &);
  QString getSymbol() const;
  void setSymbol(QString);
  QColor getStartColor() const;
  void setStartColor(QColor);
  QColor getEndColor() const;
  void setEndColor(QColor);
  bool isVisible() const;
  void toggleVisibility(bool);
signals:
};

#endif // CATEGORY_H

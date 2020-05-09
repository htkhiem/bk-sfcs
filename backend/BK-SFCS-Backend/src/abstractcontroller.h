#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <QObject>
#include "menu.h"
#include "category.h"

class AbstractController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentStallName READ getCurrentStallName)
    Q_PROPERTY(QString currentSTallImagePath READ getCurrentStallImagePath)
    QQmlApplicationEngine* p_engine; // for connecting backend to the thing
    Stall current_stall;

    void loadData();
    void saveData();
    bool categoryIsVisible(const QString& cat_name) const;
public:
    explicit AbstractController(QQmlApplicationEngine *eng, QObject *parent = nullptr);

    QList<QObject *> category_view_model;
    QList<QObject *> menu_view_model;
    QList<QObject *> stall_view_model;

public slots:
    void populateCategoryViewModel();
    void populateMenuViewModel();
    void repopulateStallViewModel();
    QString getCurrentStallName();
    QString getCurrentStallImagePath();
    bool setCurrentStall(const QString& name);
    bool setCurrentStall(Stall* const sptr);
signals:
};

#endif // ABSTRACTCONTROLLER_H

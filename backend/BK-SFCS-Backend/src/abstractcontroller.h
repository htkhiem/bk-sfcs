#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <QObject>
#include "menu.h"

class AbstractController : public QObject
{
    Q_OBJECT
    QQmlApplicationEngine* p_engine; // for connecting backend to the thing
    Stall current_stall;

    void loadData();
    void saveData();
public:
    explicit AbstractController(QQmlApplicationEngine *eng, QObject *parent = nullptr);

    QList<QObject *> category_view_model;
    QList<QObject *> menu_view_model;
    QList<QObject *> stall_view_model;

public slots:
    void populateCategoryViewModel();
    void populateMenuViewModel();
    void populateStallViewModel();
    QString getCurrentStallName();
    QString getCurrentStallImagePath();
    bool setCurrentStall(const QString& name);
signals:
};

#endif // ABSTRACTCONTROLLER_H

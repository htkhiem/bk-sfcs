#include "kioskcontroller.h"

KioskController::KioskController(QQmlApplicationEngine *eng, QObject *parent)
    : AbstractController(eng, parent)
{
    loadData();
}

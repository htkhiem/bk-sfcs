#include "stallmgmtcontroller.h"

StallMgmtController::StallMgmtController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, parent)
{

}

bool StallMgmtController::login(const QString& name, const QString& psw) {

}
bool StallMgmtController::logout() {

}
void StallMgmtController::updateWaitlistViewModel() {

}
void StallMgmtController::populateMgmtGraphs() {

}
bool StallMgmtController::loginAsManager(const QString& psw) {
  if (current_stall.getMgmtPassword() != psw) return false;
  return true;
}
void StallMgmtController::addFood(QFood * food) {
  if (!food) throw invalid_argument("Food item pointer cannot be null.");
  QFood new_food = *food;
  // TODO
}
void StallMgmtController::editFood(QFood * food) {

}
bool StallMgmtController::removeFood(const QString& name) {

}

#include "stallmgmtcontroller.h"

StallMgmtController::StallMgmtController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, parent)
{
  loadData();
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
  if (!food) throw invalid_argument("Null pointer passed to addFood.");
  QFood new_food = *food;
  current_stall.addFood(new_food);
}
void StallMgmtController::editFood(QFood * food) {
  if (!food) throw invalid_argument("Null pointer passed to addFood.");
  QVector<QFood>& current_menu = *current_stall.getEditableMenu();
  for (auto old_food : current_menu) {
      if (old_food.getName() == food->getName()) {
          old_food = *food;
          break;
        }
    }
}
bool StallMgmtController::removeFood(const QString& name) {
  if (name.isEmpty()) throw invalid_argument("Empty food item name passed to removeFood.");
  QVector<QFood>& current_menu = *current_stall.getEditableMenu();
  for (int i = 0; i < current_menu.size(); i++) {
      if (current_menu[i].getName() == name) {
          current_menu.remove(i);
          return true;
        }
    }
  return false;
}

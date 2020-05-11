#include "stallmgmtcontroller.h"

StallMgmtController::StallMgmtController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, parent), is_logged_in(false)
{
  loadData(); // Loads stall data and initialise the stall view model.
}

bool StallMgmtController::login(int idx, const QString& psw) {
    if(is_logged_in || idx < 0 || idx >= stall_view_model.size()) return false;
    if (((Stall*)stall_view_model[idx])->getPassword() != psw) return false;
    // Login successful
    setCurrentStall(idx);
    is_logged_in = true;
    return true;
}
bool StallMgmtController::logout() {
    if (!is_logged_in) return false;
    current_stall = Stall();
    return true;
}
void StallMgmtController::updateWaitlistViewModel() {
  // TODO

}
void StallMgmtController::populateMgmtGraphs() {
  // TODO
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

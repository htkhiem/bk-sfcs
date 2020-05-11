#include "stallmgmtcontroller.h"

StallMgmtController::StallMgmtController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, parent)
{
  loadData(); // Loads stall data and initialise the stall view model.
}

StallMgmtController::~StallMgmtController() {
  saveData(); // Saves stall data
}

bool StallMgmtController::login(int idx, const QString& psw) {
    if(current_stall_idx > -1 || idx < 0 || idx >= stall_view_model.size()) return false;
    if (((Stall*)stall_view_model[idx])->getPassword() != psw) return false;
    // Login successful
    setCurrentStall(idx);
    return true;
}
bool StallMgmtController::logout() {
    if (current_stall_idx == -1) return false;
    current_stall_idx = -1;
    return true;
}
void StallMgmtController::updateWaitlistViewModel() {
  // TODO

}
void StallMgmtController::populateMgmtGraphs() {
  // TODO
}
bool StallMgmtController::loginAsManager(const QString& psw) {
  const QString& mgmtPsw = getCurrentStall()->getMgmtPassword();
  if (mgmtPsw != psw) return false;
  return true;
}
void StallMgmtController::addFood(QFood * food) {
  if (!food) throw invalid_argument("Null pointer passed to addFood.");
  QFood new_food = *food;
  getCurrentStall()->addFood(new_food);
}
void StallMgmtController::editFood(QFood * food) {
  if (!food) throw invalid_argument("Null pointer passed to addFood.");
  QVector<QFood>& current_menu = *getCurrentStall()->getEditableMenu();
  for (auto old_food : current_menu) {
      if (old_food.getName() == food->getName()) {
          old_food = *food;
          break;
        }
    }
}
bool StallMgmtController::removeFood(const QString& name) {
  if (name.isEmpty()) throw invalid_argument("Empty food item name passed to removeFood.");
  QVector<QFood>& current_menu = *getCurrentStall()->getEditableMenu();
  for (int i = 0; i < current_menu.size(); i++) {
      if (current_menu[i].getName() == name) {
          current_menu.remove(i);
          return true;
        }
    }
  return false;
}
bool StallMgmtController::setStallName(const QString& name) {
  if (name.isEmpty()) return false;
  getCurrentStall()->setStallName(name);
  return true;
}
bool StallMgmtController::setStallPassword(const QString& password) {
  getCurrentStall()->setPassword(password);
  return true;
}
bool StallMgmtController::setStallMgmtPassword(const QString& mgmtpsw) {
  getCurrentStall()->setMgmtPassword(mgmtpsw);
  return true;
}
bool StallMgmtController::setStallImagePath(const QString& imgpath) {
  getCurrentStall()->setImagePath(imgpath);
  return true;
}

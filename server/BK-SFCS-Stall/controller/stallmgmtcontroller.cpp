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
  if(idx < 0 || idx >= stall_view_model.size())
    throw range_error("Stall index out of range in login function.");
  if (current_stall_idx != -1 || ((Stall*)stall_view_model[idx])->getPassword() != psw)
    return false;
  // Login successful
  setCurrentStall(idx);
  populateMenuViewModel();
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
void StallMgmtController::proposeAddFood(QFood * food) {
  if (!food) throw invalid_argument("Null pointer passed to proposeAddFood.");
  QFood* new_food = food;
  menu_view_model.append(new_food);
  p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
}
bool StallMgmtController::proposeEditFood(QFood * food) {
  if (!food) throw invalid_argument("Null pointer passed to proposeEditFood.");
  QVector<QFood>& current_menu = *getCurrentStall()->getEditableMenu();
  for (auto old_food : current_menu) {
      if (old_food.getName() == food->getName()) {
          old_food = *food;
          return true;
        }
    }
  return false;
}
bool StallMgmtController::proposeRemoveFood(const QString& name) {
  if (name.isEmpty()) throw invalid_argument("Empty food item name passed to proposeRemoveFood.");
  QVector<QFood>& current_menu = *getCurrentStall()->getEditableMenu();
  for (int i = 0; i < current_menu.size(); i++) {
      if (current_menu[i].getName() == name) {
          current_menu.remove(i);
          p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
          return true;
        }
    }
  return false;
}
void StallMgmtController::applyProposal() {
  QVector<QFood>* current_menu = getCurrentStall()->getEditableMenu();
  current_menu->clear();
  for (auto ptr : menu_view_model) current_menu->append(*(QFood *) ptr);
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
bool StallMgmtController::setStallImage(const QUrl& imgpath) {
  getCurrentStall()->setImagePath(imgpath);
  return true;
}

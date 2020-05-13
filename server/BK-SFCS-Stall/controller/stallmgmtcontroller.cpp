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
void StallMgmtController::proposeAddFood() {
  QFood* new_food = new QFood();
  menu_view_model.append(new_food);
  p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
}

bool StallMgmtController::proposeRemoveFood(int idx) {
  try {
    delete (QFood *) menu_view_model[idx];
    menu_view_model.removeAt(idx);
    p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
    return true;
  }  catch (...) {
    return false;
  }
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

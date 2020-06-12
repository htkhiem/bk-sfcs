#include "stallmgmtcontroller.h"

StallMgmtController::StallMgmtController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, "BK-SFCS Stall Manager", parent), management_mode(false)
{
}

StallMgmtController::~StallMgmtController()
{
}

void StallMgmtController::login(int idx, const QString& psw) {
  if(idx < 0 || idx >= stall_view_model.size())
    throw range_error("Stall index out of range in login function.");
  web_socket.sendTextMessage("LG " + QString::number(idx) + " " + psw);
}
bool StallMgmtController::logout() { // currently useless in networked version
  if (current_stall_idx == -1) return false;
  current_stall_idx = -1;
  return true;
}

int StallMgmtController::getCurrentStallIdx()
{
  return current_stall_idx;
}

bool StallMgmtController::isManagementModeEnabled()
{
  return management_mode;
}
void StallMgmtController::updateWaitlistViewModel() {
  // TODO

}
void StallMgmtController::populateMgmtGraphs() {
  // TODO
}
void StallMgmtController::loginAsManager(const QString& psw) {
  web_socket.sendTextMessage("LM " + psw);
}
void StallMgmtController::proposeAddFood() {
  QFood* new_food = new QFood();
  new_food->setValid(false);
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

void StallMgmtController::updateStallData() {
  QJsonObject stall_json;
  getCurrentStall()->write(stall_json);
  // Serialise current stall data into JSON and send it
  QString request = "SS " + QString::number(getClientIdx()) + " " + QJsonDocument(stall_json).toJson();
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

void StallMgmtController::parseRepliesToStall(const QString &message)
{
  // Stall-specific replies never come with file data so we can safely tokenise them.
  QStringList response_tokens = message.split(' ', QString::SkipEmptyParts);
  if (response_tokens[1] == "LG") {
      qDebug() << "Login reply received";
      if (response_tokens[0] == "OK") {
          current_stall_idx = response_tokens[2].toInt();
          qDebug() << "Logged into stall at index " << current_stall_idx;
        }
      else {
          qDebug() << "Failed to log in.";
          current_stall_idx = -2; // use -2 for wrong password
        }
      emit currentStallIndexChanged();
    }
  else if (response_tokens[1] == "LM") {
      qDebug() << "Management login reply received";
      if (response_tokens[0] == "OK") {
          management_mode = true;
        }
      else {
          management_mode = false;
        }
      emit managementModeChanged();
    }
}

void StallMgmtController::parseRepliesToKiosk(const QString &message) {
  qDebug() << "[WARNING] Server sent kiosk-specific replies to this stall!";
}

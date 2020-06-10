#include "stallmgmtcontroller.h"

StallMgmtController::StallMgmtController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, parent)
{
  loadData(); // Loads stall data and initialise the stall view model.
  current_stall_idx = -1;
}

StallMgmtController::~StallMgmtController() {
  saveData(); // Saves stall data
}

bool StallMgmtController::login(int idx, const QString& psw) {
  if(idx < 0 || idx >= stall_view_model.size())
    throw range_error("Stall index out of range in login function.");
  QString correct_psw = ((Stall*)stall_view_model[idx])->getPassword();
  if (current_stall_idx != -1 || correct_psw != psw)
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


void StallMgmtController::loadOrder() {
  QDir data_cursor = QDir::home();
  if (!data_cursor.cd("sfcs_data")) {
      throw runtime_error("Data folder not found. A blank folder will be created after this run.");
    }

  // Load stall menu and data
  data_cursor.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  QStringList stall_dirs = data_cursor.entryList();
  for (auto qstr : stall_dirs) {
      data_cursor.cd(qstr);
      //move into order folder
      data_cursor.cd("orders");
      QStringList stall_orders = data_cursor.entryList(QStringList() << "*.json",QDir::Files);
      for(auto qorder : stall_orders ){
          QFile stall_order_file(qorder);
          if (!stall_order_file.open(QIODevice::ReadOnly)) {
              throw runtime_error("Cannot read data file: " + qstr.toStdString());
            }
          QJsonDocument stall_order_json_doc(QJsonDocument::fromJson(stall_order_file.readAll()));
          OrderInfo* order = new OrderInfo();
          order->read(stall_order_json_doc.object());
          //Set add load cuz yea
          order->setOrderID(stall_order_file.fileName());

          waitlist_view_model.append(order);
          stall_order_file.close();
          //stall_order_file.remove();
      }
      data_cursor.cdUp();
      data_cursor.cdUp();
    }
  data_cursor.cdUp();

  p_engine->rootContext()->setContextProperty("stallWaitlistModel", QVariant::fromValue(stall_view_model));
}

void StallMgmtController::setReply(const QString _orderID){
    QDir data_cursor = QDir::home();
    //Access order folder from specific stall
    data_cursor.cd("sfcs_data/" + getCurrentStallName() + "/orders");
    QStringList stall_orders = data_cursor.entryList(QStringList() << "*.json",QDir::Files);

        QFile stall_order_file(_orderID);
            //Find the orderInfo within the waitlist
            for(auto ptr : waitlist_view_model){
                OrderInfo& order = *((OrderInfo* )ptr);
                //If waitlist item matches the updated order name
                if(order.getOrderID() == _orderID){
                    QJsonObject order_data_json_obj;
                    //Write that specific waitlist item into the exact name file
                    order.write(order_data_json_obj);
                    QJsonDocument order_data_json_doc(order_data_json_obj);
                    stall_order_file.write(order_data_json_doc.toJson());
                    stall_order_file.close();
                    break;
                }
            }

        data_cursor.cdUp();
        data_cursor.cdUp();

    data_cursor.cdUp();
}



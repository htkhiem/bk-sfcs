#include "kioskcontroller.h"

KioskController::KioskController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, parent)
{
  loadData();
}
int KioskController::getCurrentStallIdx() {
  return current_stall_idx;
}
void KioskController::setCurrentStallIdx(int idx) {
  if (idx < stall_view_model.size() && idx >= 0)
    current_stall_idx = idx;
  else throw range_error("Current stall index out of range.");
}
void KioskController::searchFilter(const QString& _input){

  for (auto ptr : menu_view_model) delete ptr;
  menu_view_model.clear();
  QVector<QFood>& temp = *(getCurrentStall()->getEditableMenu());
  for (QFood& qfood : temp) {
      if (categoryIsVisible(qfood.getType()) && qfood.getName().contains(_input)) {
          QObject * qfoodptr = new QFood(qfood);
          menu_view_model.append(qfoodptr);
        }
    }

  p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
}
void KioskController::setOrderFoodItem(int idx) {
  if (idx < menu_view_model.size() && idx >= 0)
    current_order.setFoodItem(getCurrentStall()->getMenu()->at(idx));
  else throw range_error("Selected food item index out of range.");
}
void KioskController::setOrderQuantity(int qty) {
  if (qty > 0) current_order.setQuantity(qty);
  else throw range_error("Ordering quantity less than one.");
}
void KioskController::setOrderMethod(int method) {
  // TODO
}
QString KioskController::sendOrder() {
  current_order.setStatus(waiting);
  QDir stall_dir = QDir::home();
  stall_dir.cd("sfcs_data");
  stall_dir.cd(getCurrentStallName());
  stall_dir.mkdir("waitlist");
  stall_dir.cd("waitlist");
  QString filename = QDateTime::currentDateTime().toString();
  QFile order_file(stall_dir.filePath(filename + QString(".json")));
  if (!order_file.open(QIODevice::WriteOnly)) {
      throw runtime_error("Cannot write current order!");
    }
  QJsonObject order_json_obj;
  current_order.write(order_json_obj);
  QJsonDocument order_json_doc(order_json_obj);
  order_file.write(order_json_doc.toJson());
  order_file.close();
  return filename;
}

bool KioskController::waitForResults(const QString& order_name) {
  QDir stall_dir = QDir::home();
  stall_dir.cd("sfcs_data");
  stall_dir.cd(getCurrentStallName());
  stall_dir.cd("waitlist");
  int elapsed_seconds = 0;
  while (true) {
      QFile order_file(stall_dir.filePath(order_name + QString(".json")));
      if (!order_file.open(QIODevice::ReadOnly)) {
          throw runtime_error("Cannot check on current order!");
        }
      QJsonDocument order_json_doc(QJsonDocument::fromJson(order_file.readAll()));
      current_order.read(order_json_doc.object());
      order_file.close();
      if (current_order.getStatus() == OrderStatus::rejected) {
          order_file.remove();
          return false;
        }
      else if (current_order.getStatus() == OrderStatus::processing) {
          order_file.remove();
          return true;
        }
      else { // wait for 1 second, then check again
          std::this_thread::sleep_for(std::chrono::seconds(1));
          // Keep OS from labeling program as not responding
          // but don't let user click away from it
          QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
          ++elapsed_seconds;
          if (elapsed_seconds == 15) {
              order_file.remove();
              return false; // timeout
            }
        }
    }
}

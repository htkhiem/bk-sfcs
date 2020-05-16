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
void KioskController::sendOrder() {
  current_order.setStatus(waiting);
  QDir stall_dir = QDir::home();
  stall_dir.cd("sfcs_data");
  stall_dir.cd(getCurrentStallName());
  stall_dir.mkdir("waitlist");
  stall_dir.cd("waitlist");

  QFile order_file(stall_dir.filePath(QDateTime::currentDateTime().toString() + QString(".json")));
  if (!order_file.open(QIODevice::WriteOnly)) {
      throw runtime_error("Cannot write current order!");
    }
  QJsonObject order_json_obj;
  current_order.write(order_json_obj);
  QJsonDocument order_json_doc(order_json_obj);
  order_file.write(order_json_doc.toJson());
  order_file.close();
}

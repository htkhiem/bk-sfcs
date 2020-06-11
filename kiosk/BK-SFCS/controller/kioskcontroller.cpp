#include "kioskcontroller.h"

KioskController::KioskController(QQmlApplicationEngine *eng, QObject *parent)
  : AbstractController(eng, "BK-SFCS Kiosk", parent)
{
}
int KioskController::getCurrentStallIdx() {
  return current_stall_idx;
}
void KioskController::setCurrentStallIdx(int idx) {
  if (idx < stall_view_model.size() && idx >= 0)
    current_stall_idx = idx;
  else throw range_error("Current stall index out of range.");
}
void KioskController::searchFilter(const QString& _input) {
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
void KioskController::sendOrder() {
  current_order.setStatus(waiting);
  QJsonObject order_object;
  current_order.write(order_object);
  web_socket.sendTextMessage("OD " +
                             QString::number(getClientIdx()) +
                             " " + QString::number(getCurrentStallIdx()) +
                             " " + QJsonDocument(order_object).toJson());
}

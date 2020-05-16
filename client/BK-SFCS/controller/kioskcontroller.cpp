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
    current_order.setFoodItem(*((QFood *) menu_view_model[idx]));
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

}

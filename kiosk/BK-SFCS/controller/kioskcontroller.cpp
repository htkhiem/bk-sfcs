#include "kioskcontroller.h"

KioskController::KioskController(QQmlApplicationEngine *eng, QObject *parent)
    : AbstractController(eng, "BK-SFCS Kiosk", parent)
{
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
    if (idx < menu_view_model.size() && idx >= 0) {
        current_order.setFoodItem(*((QFood *) menu_view_model[idx]));
        current_order.setFoodIdx(idx);
    }
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

int KioskController::getCurrentOrderStatus() {
    switch (current_order.getStatus()) {
    case processing: return 1;
    case rejected: return 2;
    default: return 0;
    }
}

void KioskController::parseRepliesToKiosk(const QString& message) { // Only runs for case "OD"
    QStringList response_tokens = message.split(' ', QString::SkipEmptyParts);
    if (response_tokens[0] == "OK") {
        int slip = response_tokens[2].toInt();
        current_order.setAnswered();
        emit currentOrderStatusChanged(slip);
    }
    else {
        current_order.setAnswered(true);
        emit currentOrderStatusChanged(); // defaults to -1, which means rejected
    }

}

void KioskController::parseRepliesToStall(const QString &message) {
    qDebug() << "[WARNING] Server sent stall-specific replies to this kiosk!";
}

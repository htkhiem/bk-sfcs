#include "stallmgmtcontroller.h"
#include <QImage>

StallMgmtController::StallMgmtController(QQmlApplicationEngine *eng, QObject *parent)
    : AbstractController(eng, "BK-SFCS Stall Manager", parent), management_mode(false)
{
    // Also get all other data of this stall for easier syncing
}

StallMgmtController::~StallMgmtController()
{
}

void StallMgmtController::flushWaitList()
{
  while (!waitlist_view_model.empty()) {
      reject(waitlist_view_model.size() - 1); // remove from end to begin is faster
    }
}

void StallMgmtController::manualCopy(const QUrl &from)
{
    QFile source(from.toLocalFile());
    if (!source.open(QIODevice::ReadOnly)) {
        throw invalid_argument("Could not access new stall image file.");
    }
    QDir cursor = getAppFolder();
    cursor.cd(getCurrentStallName());
    QFile dest(cursor.filePath(from.fileName()));
    if (!dest.open(QIODevice::WriteOnly)) {
        throw invalid_argument("Could not copy new stall image to stall folder.");
    }
    QByteArray buffer = source.readAll();
    dest.write(buffer);
    source.close();
    dest.close();
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
bool StallMgmtController::isManagementModeEnabled()
{
    return management_mode;
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
void StallMgmtController::applyProposal(bool also_update_images) {
    QVector<QFood>* current_menu = getCurrentStall()->getEditableMenu();
    current_menu->clear();
    for (auto ptr : menu_view_model) current_menu->append(*(QFood *) ptr);
    updateStallData(also_update_images);
}

void StallMgmtController::updateStallData(bool also_update_images) {
    QJsonObject stall_json;
    getCurrentStall()->write(stall_json);
    // Serialise current stall data into JSON and send it
    QString request = "SS " + QString::number(getClientIdx()) + " " + QJsonDocument(stall_json).toJson();
    web_socket.sendTextMessage(request);
    
    if (also_update_images) {
        QString filename = getCurrentStall()->getImageName();
        // Send stall image
        QByteArray message;
        QDir cursor(getCurrentStallPath());
        QFile stall_image(getCurrentStallImagePath().toLocalFile());
        if (!stall_image.open(QIODevice::ReadOnly))
            throw runtime_error("Could not load stall image from disk.");
        message += QString("%1").arg(1, 2, 10, QChar('0')).toUtf8();
        message += QString("%1").arg(getCurrentStallIdx(), 2, 10, QChar('0')).toUtf8();
        message += QString("%1").arg(filename.toUtf8().size(), 4, 10, QChar('0')).toUtf8();
        message += filename.toUtf8();
        message += stall_image.readAll();
        web_socket.sendBinaryMessage(message);
        stall_image.close();
        
        // Send menu item images
        for (int i = 0; i < getCurrentStall()->getMenu()->size(); ++i) {
            message.clear();
            QFile item_image(cursor.filePath(getCurrentStall()->getMenu()->at(i).getImageName()));
            filename = item_image.fileName();
            if (!item_image.open(QIODevice::ReadOnly))
                qDebug() << "Skipped updating a menu item's image (full-res version not present - we did not update it)";
            filename = item_image.fileName();
            message += QString("%1").arg(2, 2, 10, QChar('0')).toUtf8();
            message += QString("%1").arg(getCurrentStallIdx(), 2, 10, QChar('0')).toUtf8();
            message += QString("%1").arg(i, 2, 10, QChar('0')).toUtf8();
            message += QString("%1").arg(filename.toUtf8().size(), 4, 10, QChar('0')).toUtf8();
            message += filename.toUtf8();
            message += item_image.readAll();
            web_socket.sendBinaryMessage(message);
            item_image.close();
        }
    }
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
    QImage original(imgpath.toLocalFile());
    QImage resized;
    if (original.width() > original.height()) {
        resized = original.copy((original.width() - original.height())/2, 0, original.height(), original.height());
      }
    else if (original.width() < original.height()) {
        resized = original.copy(0, (original.height() - original.width())/2, original.width(), original.width());
      }
    else resized = original;

    // Resize down to 190x190 (the size it would appear in the kiosks).
    resized = resized.scaled(190, 190, Qt::KeepAspectRatio);

    QDir cursor = getAppFolder();
    cursor.cd(getCurrentStallName());
    resized.save(cursor.filePath(imgpath.fileName()));

    // Set name to in-memory stall data for now
    getCurrentStall()->setImageName(imgpath.fileName());
    return true;
}

bool StallMgmtController::setItemImage(const QUrl &filepath, const int idx)
{
    // Copy the file to the stall folder
    manualCopy(filepath);
    // Set item image name in JSON
    ((QFood *) menu_view_model[idx])->setImageName(filepath.fileName());
    return true;
}

void StallMgmtController::hold(int idx)
{
    OrderInfo *processing_order = ((OrderInfo *) waitlist_view_model[idx]);
    web_socket.sendTextMessage("OK OD " + QString::number(processing_order->getKiosk())
                               + " " + QString::number(getCurrentStallIdx()));
    // TODO: update waitlist
    // Don't forget to set status.
    processing_order->setAnswered(false);
}

void StallMgmtController::complete(int idx)
{
    //  OrderInfo *completed_order = ((OrderInfo *) waitlist_view_model[idx]);
    //  web_socket.sendTextMessage("OK OD " + QString::number(completed_order->getKiosk())
    //                             + " " + QString::number(getCurrentStallIdx()));
    //  // TODO: log then deallocate this OrderInfo and update waitlist
    //  // Don't forget to set status before logging.
    // This will have to wait until we have a pager display emulator.

    OrderInfo& target_order = *(OrderInfo *) waitlist_view_model[idx];
    target_order.setFinished();
    QDir cursor = getAppFolder();
    cursor.cd(getCurrentStallName());
    cursor.mkdir("logs");
    cursor.cd("logs");
    QString filename = QString::number(target_order.getFinished().toMSecsSinceEpoch());
    QFile old_order_file(cursor.filePath(filename + "json"));
    if (!old_order_file.open(QIODevice::WriteOnly)) throw("Cannot log order!");
    QJsonObject target_order_json;
    target_order.write(target_order_json);
    old_order_file.write(QJsonDocument(target_order_json).toJson());
    old_order_file.close();

    waitlist_view_model.removeAt(idx);
    p_engine->rootContext()->setContextProperty("waitlistViewModel", QVariant::fromValue(waitlist_view_model));
}

void StallMgmtController::reject(int idx)
{
    OrderInfo *rejected_order = ((OrderInfo *) waitlist_view_model[idx]);
    web_socket.sendTextMessage("NO OD " + QString::number(rejected_order->getKiosk())
                               + " " + QString::number(getCurrentStallIdx()));
    // TODO: log then deallocate this OrderInfo and update waitlist
    // Don't forget to set status before logging.
    rejected_order->setAnswered(true);
    waitlist_view_model.removeAt(idx);
    p_engine->rootContext()->setContextProperty("waitlistViewModel", QVariant::fromValue(waitlist_view_model));
}

void StallMgmtController::parseRepliesToStall(const QString &message)
{
    QStringList response_tokens = message.left(16).split(' ', QString::SkipEmptyParts);
    if (response_tokens[0] == "OD") {
        int json_start_pos = message.indexOf("{");
        QStringRef data(&message, json_start_pos, message.length() - json_start_pos - 1);
        OrderInfo *new_order = new OrderInfo();
        new_order->read(QJsonDocument::fromJson(data.toUtf8()).object());
        waitlist_view_model.append(new_order);
        p_engine->rootContext()->setContextProperty("waitlistViewModel", QVariant::fromValue(waitlist_view_model));
    }
    else {
        if (response_tokens[1] == "LG") {
            qDebug() << "Login reply received";
            if (response_tokens[0] == "OK") {
                current_stall_idx = response_tokens[2].toInt();
                web_socket.sendTextMessage("GS " + QString::number(getCurrentStallIdx()));
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
        else if (message.midRef(3, 2) == "GS") {
            if (response_tokens[0] == "OK") {
                int json_start_pos = message.indexOf("{");
                QStringRef data(&message, json_start_pos, message.length() - json_start_pos - 1);
                getCurrentStall()->read(QJsonDocument(QJsonDocument::fromJson(data.toUtf8())).object());
                qDebug() << "Full stall data received. Initializing waitlist...";
                p_engine->rootContext()->setContextProperty("waitlistViewModel", QVariant::fromValue(waitlist_view_model));
            }
            else {
                throw runtime_error("Failed to receive stall data.");
            }
        }
        else if (message.midRef(3, 2) == "SS") {
            emit stallDataUpdateFinished();
          }
    }
}

void StallMgmtController::parseRepliesToKiosk(const QString &message) {
    qDebug() << "[WARNING] Server sent kiosk-specific replies to this stall!";
}

#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "category.h"
#include "menu.h"
#include "common.h"
#include "orderinfo.h"

/** Abstract class for per-app controllers. Contains features used by all apps.
 */
class AbstractController : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString currentStallName READ getCurrentStallName NOTIFY currentStallNameChanged)
  Q_PROPERTY(QUrl currentStallImagePath READ getCurrentStallImagePath NOTIFY currentStallImagePathChanged)

  /**
   * @brief WebSocket for communicating with server
   * Outgoing Protocol:
   * KX = Get index of self within list of server clients
   * GL = get list of stalls
   * GS <idx> = get all info of stall at given index
   * IS <idx> = get image of stall at given index
   * LG <idx> <psw> = log into stall at given index with this password
   * LM <psw> = log into current stall with administrative password.
   *  Stall must already have been logged in with basic rights.
   * GM <idx> = get menu for stall at given index.
   * IM <stall idx> <menu idx> = get image of menu item at given index of stall at given index.
   * IP <stall idx> <menu idx> = get full-resolution image of menu item at given idex of stall at given index (for popup).
   * SS <idx> <serialised stall JSON object> = set stall data (for stall app)
   *  Stall must already have been logged in with administrative rights.
   * OD <idx1> <idx2> <serialised OrderInfo object> = send order from kiosk idx1 to stall idx2
   *
   * Binary Outgoing Protocol:
   * 1 <idx> <sz> <name> <data>: Send new stall image with filename "name" (of length sz) for stall at index.
   * 2 <idx1> <idx2> <sz> <name> <name> <data>: Send new image with filename "name" (of length sz) for menu item idx2 of stall idx1.
   *
   * Incoming Protocol:
   * OK <out> <data>: Context-dependent action successful (replies to "out"
   *  with data, for example replying to GL with a JSON list of stalls.
   * NO <out>: Context-dependent failure (order rejected, login failure,...)
   * Special case: OK OD <slip>: Replies that the current order is accepted and returns the slip.
   *               NO OD: Replies that the current order is rejected.
   *
   * Binary Incoming Protocol:
   * 1 <sz1> <sz2> <out><text><bin>: Context-dependent action successful (replies to <out> with UTF-8 text and binary data).
   *  sz1 is length of <out>, sz2 is length of <text>, all in UTF-8. Text and binary part not mandatory.
   * 0 <sz1> <out>: Context-dependent failure (replies to "out").
   *  sz1 is length of <out> in UTF-8.
   *
   * Note for binary protocols: all numeric parameters are sent as TWO ASCII digits, padded with zeroes if necessary.
   */

  QUrl server_url;
  QString app_name;
  int client_idx;
protected:
  QWebSocket web_socket;
  QQmlApplicationEngine *p_engine; // for connecting backend to the thing
  int current_stall_idx;

  /**
   * Checks if the category with the given name is visible. Usually called by QFood.
   * @param cat_name Category name as stored in QFood.
   * @return True if found and visible, false otherwise.
   */
  bool categoryIsVisible(const QString& cat_name) const;
  /**
   * @brief Gets the absolute path to the data folder of the current app.
   * @return a QDir containing the absolute path.
   */
  QDir getAppFolder();
  /**
   * @brief Asks for stall list from server.
   */
  void getStallList();
  /**
   * @brief Asks for stall image from server.
   * @param idx Index of target stall.
   */
  void getStallImage(int idx);
  /**
   * @brief Saves downloaded stall image into the respective stall folder for later loading.
   * @param stall_idx Index of target stall (for locating folder and setting name).
   * @param filename Name of saved file.
   * @param image Binary data of the file.
   */
  void saveStallImage(int stall_idx, const QString& filename, const QByteArray& image);
  /**
   * @brief Ask for item image from server.
   * @param stall_idx Index of target stall.
   * @param item_idx Index of target item within that stall.
   */
  void getMenuItemImage(int stall_idx, int item_idx);
  /**
   * @brief Saves downloaded item image into the respective stall folder for later loading.
   * @param stall_idx Index of target stall (for locating folder).
   * @param item_idx Index of target item within that stall (for setting name).
   * @param filename Name of saved file.
   * @param image Binary data of the file.
   */
  void saveMenuItemImage(int stall_idx, int item_idx, const QString& filename, const QByteArray& image);
  /**
   * @brief (For kiosk app) Parses order reply and sets currentOrderStatus accordingly.
   * It is delcared as a virtual function here to allow processTextMessage to call it.
   * @param message QString containing the full text message (for future extensibility).
   */
  virtual void parseRepliesToKiosk(const QString& message) = 0;
  /**(
   * @brief Parses stall app-specific replies. To be implemented by stall app.
   * @param message QString containing the full text message.
   */
  virtual void parseRepliesToStall(const QString& message) = 0;
public:
  /**
   * Main constructor.
   * @param eng Pointer to the QML application engine. Used for setting contexts
   * and exposing view models to QML.
   * @param parent Pointer to parent QObject if any. For now, leave it blank.
   */
  explicit AbstractController(QQmlApplicationEngine *eng, const QString& name,
                              QObject *parent = nullptr);

  /** View models for exposing to QML Quick Views. Note that category_view_model
   * and stall_view_model are immutable for GUI apps, due to them also serving
   * as in-memory database. On the other hand, in case of the stall management
   * app, the menu view model can be edited volatile-esque and will not affect
   * the true menu data stored in Stalls until the manager clicks the Confirm
   * button. */
  QList<QObject *> category_view_model;
  QList<QObject *> menu_view_model;
  QList<QObject *> stall_view_model;

  int getClientIdx() const;
  void setClientIdx(int value);

public slots:
  // Populators
  /** Fills category info with hardcoded categories. (Low priority) TODO:
   * implement loadable category lists. */
  void populateCategoryViewModel();
  /**
   * Send a request to get the menu of the stall at the given index.
   * It is declared as a public slot so that QML GUI can directly call it.
   * @param idx Index of target stall.
   */
  void getStallMenu(int idx);
  /**
   * @brief Fills menu view model with data downloaded from server.
   * @param list_obj a JSON list of item data downloaded from server.
   */
  void populateMenuViewModel(const QJsonObject& list_obj);
  /**
   * @brief Fills stall view model with data downloaded from server.
   * @param list_obj a compact JSON list (that does not contain menus) of stalls downloaded from server.
   */
  void populateStallViewModel(const QJsonObject& list_obj);

  // Universal data operations on local cache
  /**
   * @brief Returns absolute image path of stall at given index (for QML stall list view).
   * @param idx Index of stall.
   * @return Absolute local QUrl path to image.
   */
  QUrl getStallImagePath(int idx);
  /**
   * @brief Returns absolute image path of item of CURRENT stall (for QML menu list view).
   * If you need item images of another stall, set that stall to being the current stall first.
   * @param stall_idx Index of stall.
   * @param item_idx Index of item within that stall.
   * @return Absolute local QUrl path to image.
   */
  QUrl getItemImagePath(int item_idx);

  // Syntactic sugar for data operations on current stall
  /**
   * Set current stall to the one at the given index within stall_view_model.
   * @param idx Index of target stall.
   * @return False if out-of-range, true otherwise.
   */
  bool setCurrentStallIdx(int idx);
  /**
   * Returns a pointer to the current stall. Used internally but I'll leave it in public
   * slots for now.
   * @return Pointer to current stall.
   */
  Stall *getCurrentStall();
  /**
   * @brief getCurrentStallIdx Returns the index of the current stall.
   * @return Index of the current stall.
   */
  int getCurrentStallIdx();
  /**
   * QML-facing slot for exposing current stall name. Included in AbstractController
   * since both kiosk and stall app needs it.
   * @return Stall name as QString.
   */
  QString getCurrentStallName();
  /**
   * Same as above, for image path. Note that it returns the absolute path to the copy
   * in the stall folder.
   * @return Stall image path as QUrl (file://...).
   */
  QUrl getCurrentStallImagePath();
  /**
   * @brief Syntactic sugar for getting absolute path to current stall.
   * @return Absolute path as a QString that can be used to initialise a QDir.
   */
  QString getCurrentStallPath();


  void onConnected();
  void onTextMessageReceived(const QString& message);
  void onBinaryMessageReceived(const QByteArray &message);
signals:
  void closed();
  void currentStallNameChanged();
  void currentStallImagePathChanged();
  void stallImageChanged(int idx);
  void itemImageChanged(int sidx, int midx);
};

#endif // ABSTRACTCONTROLLER_H

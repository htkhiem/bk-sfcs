#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "category.h"
#include "menu.h"
#include "common.h"

/** Abstract class for per-app controllers. Contains features used by all apps.
 */
class AbstractController : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString currentStallName READ getCurrentStallName NOTIFY currentStallNameChanged)
  Q_PROPERTY(QUrl currentStallImagePath READ getCurrentStallImagePath NOTIFY currentStallImagePathChanged)

  /**
   * @brief WebSocket for communicating with server
   * Outgoing Protocol:
   * GL = get list of stalls
   * GS <idx> = get all info of stall at given index
   * IS <idx> = get image of stall at given index
   * LG <idx> <psw> = log into stall at given index with this password
   * GM <idx> = get menu for stall at given index
   * IM <stall idx> <menu idx> = get image of menu item at given index of stall at given index.
   * SS <serialised stall JSON object> = set stall data (for stall app)
   * OD <serialised OrderInfo object> = send order info
   *
   * Incoming Protocol:
   * OK <out> <data>: Context-dependent action successful (replies to "out"
   *  with data, for example replying to GL with a JSON list of stalls.
   * NO <out>: Context-dependent failure (order rejected, login failure,...)
   *
   * Binary Incoming Protocol:
   * <sz1> OK <sz2> <out> <data>: Context-dependent action successful (replies to "out" with "data").
   *  sz1 is length of "OK" in UTF-8. sz2 is length of "out", also in UTF-8.
   * <sz1> NO <sz2> <out>: Context-dependent failure (replies to "out").
   *  sz1 is length of "OK" in UTF-8. sz2 is length of "out", also in UTF-8.
   */
  QWebSocket web_socket;
  QUrl server_url;
  QString app_name;

protected:
  QQmlApplicationEngine *p_engine; // for connecting backend to the thing
  int current_stall_idx;

  /** Loads stall data (and their menus) from ~/sfcs_data. Also populates the
   * stall view model. */
  void loadData();

  /** Saves stall data to disk after running. This includes their menus. */
  void saveData();

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

  void getStallList();
  void getStallImage(int idx);

  void getStallMenu(int idx);
  void getMenuItemImage(int stall_idx, int item_idx);
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
public slots:

  /** Fills category info with hardcoded categories. (Low priority) TODO:
   * implement loadable category lists. */
  void populateCategoryViewModel();

  /** Fills menu view model with menu of current stall. It keeps its own data
   * so that the stall-side app can have safely modify the menu.
      In case of stall app, the logged in stall is the current stall. The menu
     view is mutable (for MenuEditor) but only written back to the actual menu
     data on tapping the Confirm button. In case of kiosk app, the selected
     stall is the current stall. The menu is not editable.
 */
  void populateMenuViewModel();
  
  /** Populate stall list with name and image. */
  void populateStallViewModel(const QJsonObject& list_obj);
  void saveStallImage(const QString& stall_name, const QByteArray& image);
  
  /**
   * Set current stall to the one at the given index within stall_view_model.
   * @param idx Index of target stall.
   * @return False if out-of-range, true otherwise.
   */
  bool setCurrentStall(int idx);

  /**
   * Returns a pointer to the current stall. Used internally but I'll leave it in public
   * slots for now.
   * @return Pointer to current stall.
   */
  Stall *getCurrentStall();
  
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

  void onConnected();
  void onTextMessageReceived(const QString& message);
  void onBinaryMessageReceived(const QByteArray &message);

  void onStallImageReceived(int idx, const QByteArray& image);
  void onStallDataReceived(const QString& serialised_json);
  void onMenuReceived(const QString& serialised_json);
  void onMenuItemImageReceived(int idx, const QByteArray& image);
signals:
  void closed();
  void currentStallNameChanged();
  void currentStallImagePathChanged();
};

#endif // ABSTRACTCONTROLLER_H

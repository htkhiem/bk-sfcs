#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "category.h"
#include "menu.h"
#include <QObject>

/** Abstract class for per-app controllers. Contains features used by all apps.
 */
class AbstractController : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString currentStallName READ getCurrentStallName)
  Q_PROPERTY(QString currentSTallImagePath READ getCurrentStallImagePath)
  QQmlApplicationEngine *p_engine; // for connecting backend to the thing
protected:
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

public:
  /**
   * Main constructor.
   * @param eng Pointer to the QML application engine. Used for setting contexts
   * and exposing view models to QML.
   * @param parent Pointer to parent QObject if any. For now, leave it blank.
   */
  explicit AbstractController(QQmlApplicationEngine *eng,
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

  /** Fills menu view model with menu of current stall.
      In case of stall app, the logged in stall is the current stall. The menu
     view is mutable (for MenuEditor) but only written back to the actual menu
     data on tapping the Confirm button. In case of kiosk app, the selected
     stall is the current stall. The menu is not editable.
 */
  void populateMenuViewModel();
  
  /** Reloads stall data. Not usually used except for debugging purposes, since stall data is only loaded once on startup and already handled by loadData(). */
  void repopulateStallViewModel();
  
  /**
   * Set current stall to the one at the given index within stall_view_model.
   * @param idx Index of target stall.
   * @return False if out-of-range, true otherwise. 
   */
  bool setCurrentStall(int idx);
  
  /**
   * Returns a pointer to the current stall. Used internally but I'll leave it in public slots for now.
   * @return Pointer to current stall.
   */
  Stall *getCurrentStall();
  
  /**
   * QML-facing slot for exposing current stall name. Included in AbstractController since both kiosk and stall app needs it.
   * @return Stall name as QString.
   */
  QString getCurrentStallName();
  
  /**
   * Same as above, for image path.
   * @return Stall image path as string (converted to QUrl in QML).
   */
  QString getCurrentStallImagePath();
signals:
};

#endif // ABSTRACTCONTROLLER_H

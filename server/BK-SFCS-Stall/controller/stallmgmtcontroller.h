#ifndef STALLMGMTCONTROLLER_H
#define STALLMGMTCONTROLLER_H

#include "../../../backend/BK-SFCS-Backend/src/abstractcontroller.h"
#include <QObject>

class StallMgmtController : public AbstractController {
  Q_OBJECT
public:
  /** TODO */
  QList<QObject *> logs_db;

  /** Model for waitlist ListView in QML. Contains OrderInfo objects. */
  QList<QObject *> waitlist_view_model;

  /**
   * Constructor. Relies on AbstractController's constructor for its  work.
   * See AbstractController's constructor in backend/abstractcontroller.h for
   * more details.
   */
  explicit StallMgmtController(QQmlApplicationEngine *eng,
                               QObject *parent = nullptr);

  /** Destructor. Calls saveData() to save stall data to JSON.
   * AbstractController doesn't do that since KioskController cannot save data.
   */
  ~StallMgmtController();
public slots:

  /**
   * Attempts to log into a stall's account. If login succceeds, it sets
   * current_stall_idx to the given index and populates the menu view model.
   * Any index not -1 is seen as logged in.
   * @param idx Index of stall in stall_view_model.
   * @param psw Given password.
   * @return True if login succeeds (correct password), false otherwise.
   * @throw range_error if given index is out-of-range.
   */
  bool login(int idx, const QString &psw);

  /**
   * Logs out of current stall. It also sets current_stall_idx to -1, which is
   * understood as not logged in.
   * @return False if no stall is currently logged in, true otherwise.
   */
  bool logout();

  /** Reloads waitlist. This is called periodically to receive new orders. */
  void updateWaitlistViewModel();

  /** TODO */
  void populateMgmtGraphs();

  /**
   * Attempts to authorise data editing for current stall, such as menu prices
   * and stall name.
   * @param psw Given password.
   * @return True if authorisation succeeds, false otherwise.
   */
  bool loginAsManager(const QString &psw);

  /**
   * QML-facing slot for proposing to a food item to the current stall.
   * @param food Packaged food item object from QML.
   */
  void proposeAddFood(QFood *food);

  /**
   * QML-facing slot for proposing to replace an existing food item in the current stall.
   * @param food Packaged food item object from QML.
   * @param idx Index of food item to be edited.
   * @return True if target item is within range and updated, false otherwise.
   */
  bool proposeEditFood(QFood *food, int idx);

  /**
   * QML-facing slot for proposing to remove a food item from the current stall.
   * @param idx Index of food item to remove.
   * @return True if food item is within range and removed, false otherwise.
   */
  bool proposeRemoveFood(int idx);
  /** Apply all editing proposals to current_stall's menu. */
  void applyProposal();
  /** QML-facing slots for GUI to edit stall data, exclusive to stall app. */
  bool setStallName(const QString &name);
  bool setStallPassword(const QString &password);
  bool setStallMgmtPassword(const QString &mgmtpsw);
  /** QML-facing slot for setting image. It copies the given image to the stall folder and
   * links from there.
   */
  bool setStallImage(const QUrl& imgpath);
signals:
};

#endif // STALLMGMTCONTROLLER_H

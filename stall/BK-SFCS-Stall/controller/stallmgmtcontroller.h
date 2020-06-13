#ifndef STALLMGMTCONTROLLER_H
#define STALLMGMTCONTROLLER_H

#include "../../../backend/BK-SFCS-Backend/src/abstractcontroller.h"
#include <QObject>

class StallMgmtController : public AbstractController {
  Q_OBJECT
  Q_PROPERTY(int currentStallIdx READ getCurrentStallIdx NOTIFY currentStallIndexChanged)
  Q_PROPERTY(bool managementMode READ isManagementModeEnabled NOTIFY managementModeChanged)

  bool management_mode;

  void parseRepliesToStall(const QString& message) override;
  void parseRepliesToKiosk(const QString& message) override;
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
   * Attempts to log into a stall's account by sending a login request to the server.
   * @param idx Index of stall in stall_view_model.
   * @param psw Given password.
   * @throw range_error if given index is out-of-range.
   */
  void login(int idx, const QString &psw);

  /**
   * Logs out of current stall. It also sets current_stall_idx to -1, which is
   * understood as not logged in.
   * @return False if no stall is currently logged in, true otherwise.
   */
  bool logout();

  /**
   * @brief Gets current stall index for QML.
   * @return Current stall index as int.
   */
  int getCurrentStallIdx();

  /**
   * @brief Checks whether management mode is enabled or not for QML.
   * @return True if management mode is enabled, false otherwise.
   */
  bool isManagementModeEnabled();

  /** Reloads waitlist. This is called periodically to receive new orders. */
  void updateWaitlistViewModel();

  /** TODO */
  void populateMgmtGraphs();

  /**
   * Attempts to authorise data editing for current stall, such as menu prices
   * and stall name by sending a request to the server.
   * @param psw Given password.
   */
  void loginAsManager(const QString &psw);

  /**
   * QML-facing slot for proposing to a food item to the current stall.
   */
  void proposeAddFood();

  /**
   * QML-facing slot for proposing to remove a food item from the current stall.
   * @param idx Index of food item to remove.
   * @return True if food item is within range and removed, false otherwise.
   */
  bool proposeRemoveFood(int idx);
  /** Apply all editing proposals to current_stall's menu. */
  void applyProposal(bool also_update_images = false);
  void updateStallData(bool also_update_images = false);
  /** QML-facing slots for GUI to edit stall data, exclusive to stall app. */
  bool setStallName(const QString &name);
  bool setStallPassword(const QString &password);
  bool setStallMgmtPassword(const QString &mgmtpsw);
  /** QML-facing slot for setting image. It copies the given image to the stall folder and
   * links from there.
   */
  bool setStallImage(const QUrl& imgpath);


signals:
  void currentStallIndexChanged();
  void managementModeChanged();
};

#endif // STALLMGMTCONTROLLER_H

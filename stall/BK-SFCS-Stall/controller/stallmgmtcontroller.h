#ifndef STALLMGMTCONTROLLER_H
#define STALLMGMTCONTROLLER_H

#include "../../../backend/BK-SFCS-Backend/src/abstractcontroller.h"
#include "./sales.h"

class StallMgmtController : public AbstractController {
  Q_OBJECT
  Q_PROPERTY(int currentStallIdx READ getCurrentStallIdx NOTIFY currentStallIndexChanged)
  Q_PROPERTY(bool managementMode READ isManagementModeEnabled NOTIFY managementModeChanged)

  bool management_mode;

  Sales *sales;

  void parseRepliesToStall(const QString& message) override;
  void parseRepliesToKiosk(const QString& message) override;
  void manualCopy(const QUrl& from);
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
  StallMgmtController(QQmlApplicationEngine *eng, Sales* sales_backend,
                               QObject *parent = nullptr);

  /** Destructor. Calls saveData() to save stall data to JSON.
   * AbstractController doesn't do that since KioskController cannot save data.
   */
  ~StallMgmtController();

  void flushWaitList();
public slots:
  /**
   * Attempts to log into a stall's account by sending a login request to the server.
   * @param idx Index of stall in stall_view_model.
   * @param psw Given password.
   * @throw range_error if given index is out-of-range.
   */
  void login(int idx, const QString &psw);
  /**
   * Attempts to authorise data editing for current stall, such as menu prices
   * and stall name by sending a request to the server.
   * @param psw Given password.
   */
  void loginAsManager(const QString &psw);
  /**
   * Logs out of current stall. It also sets current_stall_idx to -1, which is
   * understood as not logged in.
   * @return False if no stall is currently logged in, true otherwise.
   */
  bool logout();
  /**
   * @brief Checks whether management mode is enabled or not for QML.
   * @return True if management mode is enabled, false otherwise.
   */
  bool isManagementModeEnabled();

  /** TODO */
  void populateMgmtGraphs();

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
  /** QML-facing slot for setting image for item at index idx. It copies the given image to the stall folder and
   * links from there.
   */
  bool setItemImage(const QUrl& filepath, const int idx);
  /** Apply all editing proposals to current_stall's menu. */
  void applyProposal(bool also_update_images = false);

  /** QML-facing slots for GUI to edit stall data, exclusive to stall app. */
  bool setStallName(const QString &name);
  bool setStallPassword(const QString &password);
  bool setStallMgmtPassword(const QString &mgmtpsw);
  /** QML-facing slot for setting stall image. It copies the given image to the stall folder and
   * links from there.
   */
  bool setStallImage(const QUrl& filepath);

  /** Sync stall data with server */
  void updateStallData(bool also_update_images = false);

  // ORDERING FUNCTIONS
  void hold(int idx);
  void complete(int idx);
  void reject(int idx);

signals:
  void currentStallIndexChanged();
  void managementModeChanged();
  void stallDataUpdateFinished();
  void connectionLost();
};

#endif // STALLMGMTCONTROLLER_H

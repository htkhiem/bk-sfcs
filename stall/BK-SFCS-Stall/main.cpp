#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controller/stallmgmtcontroller.h"
#include "controller/sales.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // QApplication instead of QGuiApplication due to Qt Graphics View Framework dependency
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    StallMgmtController backend(&engine);
    Sales management;
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("sales", &management);

    const QUrl url(QStringLiteral("qrc:/Login.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &backend, &StallMgmtController::flushWaitList);
    engine.load(url);

    return app.exec();
}

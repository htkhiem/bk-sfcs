#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controller/stallmgmtcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // QApplication instead of QGuiApplication due to Qt Graphics View Framework dependency
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    StallMgmtController backend(&engine);
    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url(QStringLiteral("qrc:/Login.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

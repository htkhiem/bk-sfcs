#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controller/kioskcontroller.h"
#include <QFontDatabase>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    KioskController backend(&engine);
    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url(QStringLiteral("qrc:/Window.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

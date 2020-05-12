#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controller/stallmgmtcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    StallMgmtController backend(&engine);
    engine.rootContext()->setContextProperty("backend", &backend);

    qmlRegisterType<QFood>("backend.qfood", 1, 0, "QFood");

    const QUrl url(QStringLiteral("qrc:/Login.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

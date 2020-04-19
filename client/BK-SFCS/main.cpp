#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "menu.h"

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

//    return app.exec();




for(int i=0;i<10;i++){
    Stall stall;
    stall.stallName = i;
    for(int i = 0;i<5;i++){
    QFood food;
    food.name = "fried chicken";
    food.price = 7.8;
    food.type = "main";
    food.description = "Crispy spicy deep-fried chicken";

    stall.menu.push_back(food);
    }
    stallist.push_back(stall);
}
    writeStall("stall.json");

}

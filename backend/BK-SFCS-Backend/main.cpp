#include <QCoreApplication>
#include "./src/common.h"
#include "./src/controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Controller *controller = new Controller(&a);
    QObject::connect(controller, SIGNAL(finished()), &a, SLOT(quit()));
    controller->run();
    return a.exec();
}

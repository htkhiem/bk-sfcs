#include <QCoreApplication>
#include "./src/common.h"
#include "./src/controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Controller *controller = new Controller(&a);
    QObject::connect(controller, SIGNAL(finished()), &a, SLOT(quit()));
Controller control;
control.RegisterStall();
control.RegisterStall();
control.RegisterStall();
control.RegisterStall();
control.RegisterStall();
control.WriteData();
    return a.exec();
}

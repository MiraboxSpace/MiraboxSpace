#include <QCoreApplication>
#include <CustomMain.h>
#include "ExamplePlugin.h"

int main(int argc, const char **argv)
{
    QCoreApplication a(argc, (char **)argv);

    ExamplePlugin *myPlugin = new ExamplePlugin();
    QObject::connect(&a, &QCoreApplication::destroyed, [myPlugin](){
        delete myPlugin;
    });
    if (CustomMain(argc, argv, myPlugin)) {
        return 1;
    }

    return a.exec();
}

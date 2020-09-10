#include "mainwindow.h"

#include <QApplication>

#include "touchtranslator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    static TouchTranslator translator;

    a.installEventFilter(&translator);
    w.installEventFilter(&translator);
    const QList<QObject *> objects = w.findChildren<QObject *>();
    for (QObject *object : objects) {
        object->installEventFilter(&translator);
    }

    return a.exec();
}

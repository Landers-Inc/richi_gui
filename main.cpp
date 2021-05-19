#include <QApplication>
#include <QQmlApplicationEngine>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qputenv("QT_VIRTUALKEYBOARD_STYLE", "richikb");
    qputenv("QT_QPA_EGLFS_HIDECURSOR", "1");

    QApplication a(argc, argv);

    QQmlApplicationEngine engine;

    engine.addImportPath(":/resources");

    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<std::vector<double>>("std::vector<double>");

    MainWindow w;
    w.show();
    w.setupGUI();
    return a.exec();
}

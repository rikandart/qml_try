#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>


#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<BackEnd>("com.dieseleeasy.backend", 1, 0, "BackEnd");

    /*const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject* window = (QObject*)engine.rootObjects().first();

    // кнопки с индикацией включен/выключен бит для ручной установки индикации
    for(int i = 0; i < 8; i++)
        BackEnd::itemVec.push_back(window->findChild<QObject*>(QString("butBackRec%1").arg(i)));

    return app.exec();
}

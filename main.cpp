#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "colormaker.h"
#include "stdio.h"
#include <stdlib.h>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        if (strstr(msg.toLatin1().data(), "Qt: Untested Windows version 10.0 detected!") == 0) {
            // Print warning if it is not "Qt: Untested Windows..."
            fprintf(stderr, "Warning: %s\n", msg);
        }
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);
    //qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");//[1]导入类
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("colorMaker",new ColorMaker);//[2]类对象作为上下文
    engine.load(QUrl(QStringLiteral("qrc:/animation.qml")));

    return app.exec();
}


/*
 * Qt集成了QML引擎和Qt元对象系统，使得QML很容易从C++中得到扩展，在一定的条件下，QML就可以访问QObject派生类的成员，例如信号、槽函数、枚举类型、属性、成员函数等。

QML访问C++有两个方法：一是在Qt元对象系统中注册C++类，在QML中实例化、访问。二是在C++中实例化并设置为QML上下文属性，在QML中直接使用。与后者相比，前者可以使C++类在QML中作为一个数据类型，例如函数参数类型或属性类型，也可以使用其枚举类型、单例等，功能更强大。


1、QML与C++为什么要混合编程

QML与C++为什么要混合编程，简单来说，就是使用QML高效便捷地构建UI，而C++则用来实现业务逻辑和复杂算法，下面介绍了两者间交互的方法与技巧。

2、QML访问C++概述

Qt集成了QML引擎和Qt元对象系统，使得QML很容易从C++中得到扩展，在一定的条件下，QML就可以访问QObject派生类的成员，例如信号、槽函数、枚举类型、属性、成员函数等。

QML访问C++有两个方法：一是在Qt元对象系统中注册C++类，在QML中实例化、访问。二是在C++中实例化并设置为QML上下文属性，在QML中直接使用。与后者相比，前者可以使C++类在QML中作为一个数据类型，例如函数参数类型或属性类型，也可以使用其枚举类型、单例等，功能更强大。

3、如何实现可以被QML访问的C++类

C++类要想被QML访问，首先必须满足两个条件：
一是派生自QObject类或QObject类的子类，
二是使用Q_OBJECT宏。QObject类是所有Qt对象的基类，作为Qt对象模型的核心，提供了信号与槽机制等很多重要特性。
Q_OBJECT宏必须在private区（C++默认为private）声明，用来声明信号与槽，使用Qt元对象系统提供的内容，位置一般在语句块首行。

Q_ENUMs
Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)
Q_INVOKABLE

下面例子在QtCreator3.4.1中创建，Projects选择QtQuickApplication，工程名为qml，Component选择QtQuick2.2，然后在自动生成的文件中添砖加瓦。

*/

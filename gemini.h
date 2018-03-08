#ifndef GEMINI_H
#define GEMINI_H
// Gemini.h
#include <qobject>
#include <qdebug>
class Gemini : public QObject
{
    Q_OBJECT
signals:
    void begin();
public slots:
    void doSomething() {
        qDebug() << "Gemini::doSomething() called";
    }
};
#endif // GEMINI_H</qdebug></qobject>

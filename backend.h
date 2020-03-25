#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtQuick/QQuickItem>
#include <QFile>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString hexNumber READ getNumber WRITE setHexNumber NOTIFY numberChanged)
public:
    static QVector<QObject*> itemVec;
    explicit BackEnd(QObject *parent = nullptr);
    QString getNumber();
    void setNumber(const QString&);
    void setHexNumber(const QString&);
    void processLine(const QString&);

    Q_INVOKABLE void invertBits();
    Q_INVOKABLE void toggleBit(const quint8&);
    Q_INVOKABLE void openFile(const QString&);

private:
    bool isOK; // для преобразования строки в число
    bool verified; // признак подтвержденного числа
    short radix; // система исчисления
    quint8 m_number; // само число
    quint8 verifyNumber(const QString &, const short);
    void setButtColor(const int);
    void setIndicator(const QString&, const int);

signals:
    void numberChanged();


};

#endif // BACKEND_H

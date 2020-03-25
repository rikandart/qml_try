#include "backend.h"
#include <QDebug>

BackEnd::BackEnd(QObject *parent) : QObject(parent){}

QVector<QObject*> BackEnd::itemVec = QVector<QObject*>();

void BackEnd::setNumber(const QString &number){
    QString tmp_num = number;
    if(number == "")
        tmp_num = "0";
    else
        tmp_num = number;
    m_number = verifyNumber(tmp_num, 10);
    emit numberChanged();
    setButtColor(-1);
}

void BackEnd::setHexNumber(const QString &number){
    QString tmp_num = number;
    if(number == "")
        tmp_num = "0";
    else
        tmp_num = number;
    m_number = verifyNumber(tmp_num, 16);
    emit numberChanged();
    setButtColor(-1);
}

QString BackEnd::getNumber(){
    if(verified && isOK)
        return QString::number(m_number, 16).toUpper();
    else
        if(radix == 10)
            return QString("Insert any decimal number in range 0 to 255!");
        else if(radix == 16)
            return QString("Insert any hex number in range 0 to FF!");
}


// проверка на число
quint8 BackEnd::verifyNumber(const QString &number, const short radix){
    //qDebug() << number;
    quint8 iNumber = 0;
    // quint8 сам отбрасывает старшие биты
    // а метод toUint возвращает isOK == false, если число отрицательное или введены случайные буквы
    iNumber = number.toUInt(&isOK, radix);

    this->radix = radix; // запоминаем систему исчисления

    if(!isOK){
        verified = false;
        return 0;
    } else

    verified = true;
    return iNumber;
}

// инвертирование битов
void BackEnd::invertBits(){
    m_number = ~m_number;
    emit numberChanged();
    setButtColor(-1);
}

void BackEnd::toggleBit(const quint8& bit_pos){
    if (bit_pos > 7)
        return;

    QString number = QString::number(m_number, 2);
    int len;
    // дополнение нулями
    if((len = number.length()) < 8)
        for(int i = 0; i < 8 - len; i++)
            number.insert(i, QChar('0'));
    if(number[bit_pos] == QChar('1'))
        number[bit_pos] = QChar('0');
    else if (number[bit_pos] == QChar('0'))
        number[bit_pos] = QChar('1');
    m_number = number.toInt(&isOK, 2);
    emit numberChanged();
    setButtColor(bit_pos);
}

void BackEnd::setButtColor(const int buttonNumber){
    QString number = QString::number(m_number, 2);

    int len;
    // дополнение нулями
    if((len = number.length()) < 8)
        for(int i = 0; i < 8 - len; i++)
            number.insert(i, QChar('0'));


    if(buttonNumber == -1){
        for (int i = 0; i < number.length(); i++){
            setIndicator(number, i);
        }
    } else {
        setIndicator(number, buttonNumber);
    }
}

void BackEnd::setIndicator(const QString& number, const int i){
    if(number[i] == QChar('0')) // если на этой позиции 0, соответственно, бит выключен
        itemVec[i]->setProperty("color", "#70798c");
    else // если 1, то включен
        itemVec[i]->setProperty("color", "#04934e");
}

void BackEnd::openFile(const QString &filename){
    //qDebug() << filename;
    //"file:///home/pizhun/Documents/file.txt"
    QString fn = filename.mid(7, filename.length());
    QFile file(fn);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
        processLine(line);
        line = in.readLine();
    }
    setButtColor(-1);
    emit numberChanged();
}

void BackEnd::processLine(const QString &line){
    QStringList strList = line.split(' ');
    for(int i = 0; i < strList.length(); i++){
        unsigned int tmp = strList[i].toUInt(&isOK, 10);
        // quint8 сам отбрасывает старшие биты
        if(isOK && tmp <= 100)
            m_number += tmp;
    }
}

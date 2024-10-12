#include "serialportreader.h"

SerialPortReader::SerialPortReader(QSerialPort *sp, QObject *parent) :
    QThread(parent),
    receivedResponce(false),
    m_serial(sp)
{
    // если в порт записывает дата, то она считывается и отправляет "ответ"
    connect(m_serial, &QSerialPort::readyRead, this, &SerialPortReader::readData);
}

SerialPortReader::~SerialPortReader() {}


void SerialPortReader::writeData(const QByteArray &data)
{
    m_serial->write(data);
    qDebug() << "Writed to " << m_serial->portName() << "data: " << data;
}

void SerialPortReader::readData()
{
    const QByteArray data = m_serial->readAll();
    qDebug() << "Data received: " << data;

    // запускаем таймер на 15 сек и отправляем ответ "123"
    QTimer::singleShot(15000, this, &SerialPortReader::sendData);
}

void SerialPortReader::sendData()
{
    const QByteArray data = "123";
    writeData(data);
}

void SerialPortReader::run()
{
    exec();
}


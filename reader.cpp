#include "reader.h"

Reader::Reader(QSerialPort *sp, QObject *parent) :
    QThread(parent),
    m_serial(sp)
{
    connect(m_serial, &QSerialPort::readyRead, this, &Reader::readData);
}
Reader::~Reader(){}


void Reader::run()
{
    while(!isInterruptionRequested())
    {
        if(m_serial->waitForReadyRead(100)){
            const QByteArray data = m_serial->readAll();
            emit dataReady(data);
        }
    }
}


void Reader::readData()
{
    const QByteArray data = m_serial->readAll();
    emit dataReady(data);
}


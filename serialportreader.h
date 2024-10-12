#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include "QDebug"
#include "QThread"
#include "QTimer"
#include "QSerialPort"
#include "QSerialPortInfo"
#include "QByteArray"


class SerialPortReader : public QThread
{
    Q_OBJECT
public:
    SerialPortReader(QSerialPort *sp, QObject *parent = nullptr);
    ~SerialPortReader();


    void writeData(const QByteArray &data);

public slots:
    void readData();
    void sendData();

signals:
    void dataReady(const QByteArray &data);
    void responceReceived(bool ok);

protected:
    void run() override;

private:
    bool receivedResponce = false;
    QSerialPort *m_serial;
};

#endif // SERIALPORTREADER_H

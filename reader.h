#ifndef READER_H
#define READER_H

#include <QThread>
#include <QSerialPort>
#include <QByteArray>

class Reader : public QThread
{
    Q_OBJECT
public:
    explicit Reader(QSerialPort *sp, QObject *parent = nullptr);
    ~Reader();

protected:
    void run() override;

signals:
    void dataReady(const QByteArray &data);

private:
    QSerialPort *m_serial;
};

#endif // READER_H

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
    /*
     * намек на многопоточность я оставил, но qtшные функции асинхронны,
     * так что (потоки) здесь особо и не нужны.
     */
    void run() override;

signals:
    void dataReady(const QByteArray &data);

private:
    /*
     * функция чтения данных из порта
     */
    void readData();
private:
    QSerialPort *m_serial;
};

#endif // READER_H

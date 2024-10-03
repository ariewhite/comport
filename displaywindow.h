#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QDebug>
#include <QThread>

#include "reader.h"
#include "console.h"


namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWindow(QSerialPort *sp, QWidget *parent = nullptr);
    ~DisplayWindow();

public:
    void readSP();

private slots:
    void on_pushButton_clicked();
    void handleReadyData(const QByteArray &data);

private:
    QSerialPort *m_serial;
    Console *console;
    Ui::DisplayWindow *ui;
    Reader *m_read;

signals:
    void dataRead(const QByteArray &data);
};




#endif // DISPLAYWINDOW_H

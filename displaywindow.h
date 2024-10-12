#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QDebug>
#include <QThread>
#include <QMessageBox>

#include "serialportreader.h"
#include "console.h"
#include "settingsdialog.h"

/**
 * Класс отвечает за "второе окно", для просмотра данных из порта
 */
namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = nullptr);
    ~DisplayWindow();

private slots:
    // *** печатает данные в консоль ***
    void handleReadyData(const QByteArray &data);
    // *** обработчик нажатия настроек ***
    void on_settingsBtn_clicked();
    // *** обработчик нажатия конекта ***
    void on_connectBtn_clicked();
    // *** обработчик нажатия дисконекта ***
    void on_disconnectBtn_clicked();
    // *** обработчик нажатия кнопки отправки данных ***
    void on_sendBtn_clicked();

private:
    QSerialPort *m_serial;
    Console *m_console;
    Ui::DisplayWindow *ui;
    SerialPortReader *m_read;
    SettingsDialog *m_settings;

signals:
    void dataRead(const QByteArray &data);
};




#endif // DISPLAYWINDOW_H

#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QWidget(parent),
    m_serial(new QSerialPort),
    m_console(new Console(this)),
    ui(new Ui::DisplayWindow),
    m_read(new SerialPortReader(m_serial, this)),
    m_settings(new SettingsDialog(this))
{
    // отображаем консоль, кнопки
    ui->setupUi(this);
    ui->vertLay->addWidget(m_console);
    ui->sendBtn->setDisabled(true);
    ui->disconnectBtn->setDisabled(true);
    m_console->setEnabled(false);
    m_console->show();
    ui->connectBtn->setEnabled(false);
    m_console->setLocalEchoEnabled(true);

    // связываем получения данных из класса и печать их на консоль
    connect(m_read, &SerialPortReader::dataReady, this, &DisplayWindow::handleReadyData);
}


DisplayWindow::~DisplayWindow()
{
    delete ui;
    //закрываем связь с портом
    if(m_serial->isOpen()){
        m_serial->close();
    }

    delete m_settings;
    delete m_read;
    delete m_console;
}


void DisplayWindow::handleReadyData(const QByteArray &data)
{
    m_console->putData(data);
}


void DisplayWindow::on_settingsBtn_clicked()
{
    m_settings->show();
    ui->connectBtn->setEnabled(true);
}


void DisplayWindow::on_connectBtn_clicked()
{
    // вытаскиваем данные из настроек
    const SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);

    // пробуем подключиться
    if (m_serial->open(QIODevice::ReadWrite)) {
        m_console->setEnabled(true);

        // запускаем поток "железа"
        m_read->start();
        qDebug() << "Сonnected to " << m_serial->portName();
        ui->disconnectBtn->setEnabled(true);
        ui->connectBtn->setDisabled(true);
        ui->sendBtn->setEnabled(true);
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
    }
}


void DisplayWindow::on_disconnectBtn_clicked()
{
    if(m_serial->isOpen()){
        qDebug() << "Disconnect " << m_serial->portName();
        m_serial->close();
    }
    ui->disconnectBtn->setDisabled(true);
    ui->connectBtn->setEnabled(true);
    ui->sendBtn->setDisabled(true);
}


void DisplayWindow::on_sendBtn_clicked()
{
    // консоль из себя представляет qplaintextedit
    QString data = m_console->toPlainText();
    // <qstring> -> <qbytearray>
    QByteArray bytes = data.toUtf8();
    m_read->writeData(bytes);
}


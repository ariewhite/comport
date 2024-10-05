#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QSerialPort *sp, QWidget *parent) :
    QWidget(parent),
    m_serial(new QSerialPort),
    m_console(new Console(this)),
    m_read(new Reader(m_serial, this)),
    m_settings(new SettingsDialog(this)),
    ui(new Ui::DisplayWindow)
{
    // отображаем консоль
    ui->setupUi(this);
    ui->vertLay->addWidget(m_console);
    m_console->setEnabled(false);
    m_console->show();
    ui->connectBtn->setEnabled(false);

    // связываем получения данных из класса и печать их на консоль
    connect(m_read, &Reader::dataReady, this, &DisplayWindow::handleReadyData);
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
    if (m_serial->open(QIODevice::ReadOnly)) {
        m_console->setEnabled(false);
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
    }

    qDebug() << "Сonnected to " << m_serial->portName();
}


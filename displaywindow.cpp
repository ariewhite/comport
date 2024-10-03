#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QSerialPort *sp, QWidget *parent) :
    QWidget(parent),
    m_serial(sp),
    console(new Console(this)),
    m_read(new Reader(m_serial, this)),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
    ui->vertLay->addWidget(console);
    console->setEnabled(false);
    console->show();

    m_read->start();

    connect(m_read, &Reader::dataReady, this, &DisplayWindow::handleReadyData);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
    m_read->requestInterruption();
    m_read->wait();
}

void DisplayWindow::readSP()
{
    const QByteArray data = m_serial->readAll();
    //qDebug() << data;
    console->putData(data);
}

void DisplayWindow::on_pushButton_clicked()
{

    //QByteArray data = readSP();
    //ui->textEdit->insertPlainText(QString(data));
}

void DisplayWindow::handleReadyData(const QByteArray &data)
{
    console->putData(data);
}


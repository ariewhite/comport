#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>

#include "settingsdialog.h"

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWindow(QWidget *parent = nullptr);
    ~ConnectWindow();

private:
    Ui::ConnectWindow *ui;
    SettingsDialog *st = nullptr;
};

#endif // CONNECTWINDOW_H

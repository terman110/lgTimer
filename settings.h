#ifndef SETTINGS_H
#define SETTINGS_H

#include "ui_settings.h"
#include <QDebug>

struct SettingsParameter
{
    qlonglong seconds;
    double opacity;
    bool showSec;
    bool showDialog;
    SettingsParameter() : seconds(3600), opacity(0.8), showSec(false), showDialog(false) {}
};

class Settings :
        public QDialog,
        private Ui::Settings
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0, SettingsParameter param = SettingsParameter());

    SettingsParameter getSettings();
};

#endif // SETTINGS_H

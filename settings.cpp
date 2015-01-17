#include "settings.h"

Settings::Settings(QWidget *parent, SettingsParameter param) :
    QDialog(parent)
{
    setupUi(this);

    qlonglong sec = param.seconds;
    qlonglong hrs = sec / 3600;
    sec -= hrs * 3600;
    qlonglong min = sec / 60;
    min -= min * 60;
    hrsSpin->setValue((int)hrs);
    minSpin->setValue((int)min);
    secSpin->setValue((int)sec);

    opacitySpin->setValue( param.opacity);
    showDialogBox->setChecked( param.showDialog);
    showSecBox->setChecked( param.showSec);
}

SettingsParameter Settings::getSettings() {
    SettingsParameter param;

    param.seconds = (qlonglong)hrsSpin->value()*3600 + (qlonglong)minSpin->value()*60 + (qlonglong)secSpin->value();

    param.opacity = opacitySpin->value( );
    param.showDialog = showDialogBox->checkState() == Qt::Checked ? true : false;
    param.showSec = showSecBox->checkState() == Qt::Checked ? true : false;

    return param;
}

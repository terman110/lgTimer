#include "settings.h"

Settings::Settings(QWidget *parent, SettingsParameter param) :
    QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint|windowFlags());

    update();

    QRect w_pos = geometry();
    QRect scrn = QApplication::desktop()->availableGeometry(this);

    int s_height = scrn.height();
    int s_width = scrn.width();
    int s_x = scrn.x();
    int s_y = scrn.y();

    int x = w_pos.x();
    if( x < s_x)
        x = s_x;
    if( x + w_pos.width() > s_width)
        x = s_width - w_pos.width();

    int y = w_pos.y();
    if( y < s_y)
        y = s_y;
    if( y + w_pos.height() > s_height)
        y = s_height - w_pos.height();

    move( QPoint( x, y));

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

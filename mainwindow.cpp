#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _moving(false), _running(false), _finished(true)
{
    param.opacity = QSettings().value( "opacity", param.opacity).toDouble();
    param.seconds = QSettings().value( "seconds", param.seconds).toULongLong();
    param.showSec = QSettings().value( "showSec", param.showSec).toBool();
    param.showDialog = QSettings().value( "showDialog", param.showDialog).toBool();

    setupUi(this);
    setWindowTitle("lgTimer");
    setWindowOpacity( param.opacity);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    setTimeLabel( param.seconds);
    _running = true;
    pausePressed();
    _running = false;

    connect( playBtn,       SIGNAL(clicked()),this, SLOT(playPressed()));
    connect( pauseBtn,      SIGNAL(clicked()),this, SLOT(pausePressed()));
    connect( repeatBtn,     SIGNAL(clicked()),this, SLOT(repeatPressed()));
    connect( settingsBtn,   SIGNAL(clicked()),this, SLOT(settingsPressed()));

    restoreGeometry( QSettings().value("geometry").toByteArray());

    connect(&timer, SIGNAL(timeout()), this, SLOT(loop()));
    timer.setSingleShot(false);
    timer.start(1000);
}

void MainWindow::setBackground( unsigned char r, unsigned char g, unsigned char b) {
    setStyleSheet(QString("QMainWindow{\n	background: rgb(") + QString::number((int)r) + "," + QString::number((int)g) + "," + QString::number((int)b) + ");\n}");
    style()->unpolish(this);
    style()->polish(this);
    update();
}

QString MainWindow::numToStr( qlonglong num) {
    return QString("%1").arg( num, 2, 10, QChar('0'));
}

void MainWindow::setTimeLabel( qlonglong sec) {
    _lastwritten = sec;
    double secf = ((double)sec / (double)param.seconds);
    if( secf < 0)
        secf = 0.;
    unsigned char r = 255. - (255. * secf);
    unsigned char g = 255. * secf;
    unsigned char b = 0;

    qlonglong hrs = sec/3600;
    sec -= hrs * 3600;
    qlonglong min = sec/60;
    sec -= min * 60;
    QString str;
    if( sec < 0 || min < 0 || hrs < 0){
        sec *= -1;
        min *= -1;
        hrs *=-1;
        str += "-";
    }
    str += QString() + numToStr(hrs) + ":" + numToStr(min);
    if( param.showSec)
        str += QString(":") + numToStr(sec);
    timeLabel->setText( str);

    setBackground( r, g, b);
}

void MainWindow::loop() {
    if( !_running)
        return;
    _remaining -= timer.interval() / 1000;
    if( param.showSec || _remaining - _lastwritten >= 60)
        setTimeLabel( _remaining);
    if( _remaining <= 0 && !_finished) {
        _finished = true;
        QSound::play(":sound/bell");
        QApplication::beep();
        if( param.showDialog)
            QMessageBox::warning( this, "Time's up", "Time's up!");
    }
}

void MainWindow::playPressed() {
    if( _running)
        return;
    _remaining = param.seconds;
    _running = true;
    _finished = false;
    setTimeLabel( param.seconds);
    _lastwritten = 0;
    playBtn->setDisabled(true);
    pauseBtn->setDisabled(false);
    repeatBtn->setDisabled(false);
    timeLabel->setDisabled(false);
}

void MainWindow::pausePressed() {
    if( !_running)
        return;
    _running = false;
    _finished = false;
    playBtn->setDisabled(false);
    pauseBtn->setDisabled(true);
    repeatBtn->setDisabled(false);
    timeLabel->setDisabled(true);
    setBackground( 128, 128, 128);
}

void MainWindow::repeatPressed() {
    _running = false;
    playPressed();
}

void MainWindow::settingsPressed() {
    pausePressed();
    Settings dlg(this, param);
    if( dlg.exec() >= 1) {
        param = dlg.getSettings();
        QSettings().setValue( "opacity", param.opacity);
        QSettings().setValue( "seconds", param.seconds);
        QSettings().setValue( "showSec", param.showSec);
        QSettings().setValue( "showDialog", param.showDialog);
        setWindowOpacity( param.opacity);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if( event->button() == Qt::LeftButton) {
        _moving = true;
        _mpos = event->pos();
    }
    else if( event->button() == Qt::RightButton) {
        settingsPressed();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if( (event->buttons() & Qt::LeftButton) && _moving) {
        QRect w_pos = geometry();
        QPoint m_pos = event->pos();
        QRect scrn = QApplication::desktop()->availableGeometry(this);

        int s_height = scrn.height();
        int s_width = scrn.width();
        int s_x = scrn.x();
        int s_y = scrn.y();

        int x = w_pos.x() + ( m_pos.x() - _mpos.x());
        if( x < s_x)
            x = s_x;
        if( x + w_pos.width() > s_width)
            x = s_width - w_pos.width();

        int y = w_pos.y() + (m_pos.y() - _mpos.y());
        if( y < s_y)
            y = s_y;
        if( y + w_pos.height() > s_height)
            y = s_height - w_pos.height();

        move( QPoint( x, y));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if( event->button() == Qt::LeftButton && _moving) {
        _moving = false;
        QSettings().setValue("geometry", saveGeometry());
    }
}

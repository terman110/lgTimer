#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "settings.h"

#include <QSettings>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include <QSound>
#include <QDesktopWidget>

class MainWindow :
        public QMainWindow,
        private Ui::MainWindow
{
    Q_OBJECT

protected:
    SettingsParameter param;

    bool _moving;
    QPoint _mpos;
    qlonglong _remaining;
    qlonglong _lastwritten;
    bool _running;
    bool _finished;

    QTimer timer;

    void setBackground( unsigned char r, unsigned char g, unsigned char b);

    QString numToStr( qlonglong num);
    void setTimeLabel( qlonglong sec);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void playPressed();
    void pausePressed();
    void repeatPressed();
    void settingsPressed();
    void loop();

public:
    explicit MainWindow(QWidget *parent = 0);
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include "udphost.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //Constructor
    explicit MainWindow(QWidget *parent = 0);

    //Destructor
    ~MainWindow();

public slots:

    //reads pending datagram sent by another Program at
    // a particular port
    void readPendingDatagrams();

private slots:

    //Slot Called when Start Laser Button is Clicked
    void on_startLaserButton_clicked();

    //Slot Called when Stop Laser Button is Clicked
    void on_stopLaserButton_clicked();

    //Slot Called when Full Scan Mode is selected
    void on_fullScanModeButton_clicked();

    //Slot Called when Bounded Elevation Scan Mode is selected
    void on_boundedElevationModeButton_clicked();

    //Slot Called when Region Scan Mode is selected
    void on_regionScanModeButton_clicked();

    //Slot Called when Open option is selected by the user for
    //loading a different model for sensing
    void on_openAction_clicked();


    void on_actionSave_triggered();

private:

    //Pointer to the designer form
    Ui::MainWindow *ui;

    //Socket for receiving sensed data from server
    QUdpSocket *socket;

    UdpHost *_udp;
};

#endif // MAINWINDOW_H

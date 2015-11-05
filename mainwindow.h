#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include "udphost.h"
#include "udpreceiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum LASER_STATUS{
        ON,
        OFF
    };

    enum SCAN_MODE{
        FULL_FIELD_SCAN,
        BOUNDED_ELEVATION_SCAN,
        REGION_SCAN
    };

    //Constructor
    explicit MainWindow(QWidget *parent = 0);

    //Destructor
    ~MainWindow();

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


    //Acknowledgement for Start Laser
    void ackRunLaser();

    //Acknowledgement for Stop Laser
    void ackStopLaser();

    //Acknowledgement for Full Scan Mode
    void ackFullScanMode();

    //Acknowledgement for Bounded Elevation Scan Mode
    void ackBoundedElevation();

    //Acknowledgement for Region Scan Mode
    void ackRegionScan();

    //Acknowledgement for Laser Sensor Position
    void ackLaserSensorPosition();


    void on_LaserPositionButton_clicked();

private:

    //Pointer to the designer form
    Ui::MainWindow *ui;

    UdpHost *_udpSender;

    UdpReceiver *_udpReceiver;

    int _samplingFrequency;
    int _tempSamplingFrequency;

    int _totalPoints;
    int _tempTotalPoints;

    float _maximumRange;
    float _tempMaximumRange;

    int _azimuthalFrequency;
    int _tempAzimuthalFrequency;

    int _numberScanline;
    int _tempNumberScanline;

    LASER_STATUS _sensorStatus;
    LASER_STATUS _tempSensorStatus;

    SCAN_MODE _sensorScanMode;
    SCAN_MODE _tempSensorScanMode;

    float _upperBound;
    float _tempUpperBound;

    float _lowerBound;
    float _tempLowerBound;

    float _lAngular;
    float _tempLAngular;

    float _rAngular;
    float _tempRAngular;

    float _laserSensorPosition[3]; // X, Y, Z
    float _tempLaserSensorPosition[3];

    float _laserSensorOrientation[3]; //Roll, Pitch, Yaw
    float _tempLaserSensorOrientation[3];
};

#endif // MAINWINDOW_H

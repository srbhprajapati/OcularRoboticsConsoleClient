#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <cmath>

#include <QtNetwork/QUdpSocket>

#define RECEIVING_PORT 1235

class UdpReceiver : public QObject
{
    Q_OBJECT
    public:

        // Constructor
        UdpReceiver();

        // Destructor
        ~UdpReceiver();


    public slots:

        //reads pending datagram sent by another Program at
        // a particular port
        void readPendingDatagrams();

    signals:

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

    private:

        void parseDatagram(QByteArray datagram);

        //Socket for receiving sensed data from server
        QUdpSocket *socket;

};

#endif // UDPRECEIVER_H

#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

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


    private:

        void parseDatagram(QByteArray datagram);

        //Socket for receiving sensed data from server
        QUdpSocket *socket;

};

#endif // UDPRECEIVER_H

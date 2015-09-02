#include "udpreceiver.h"

#define RECEIVING_PORT 1235
#define RECEIVING_IP	QHostAddress::LocalHost
#define PIBY2 1.57142857143

UdpReceiver::UdpReceiver()
{

    socket = new QUdpSocket(this);

    //Bind Socket to an Address
    if(!socket->bind(QHostAddress::Any, RECEIVING_PORT))
    {
        qDebug()<<"Unable to connect to Server";
    }

    QObject::connect(socket, SIGNAL(readyRead()),
                     this, SLOT(readPendingDatagrams()));

}

UdpReceiver::~UdpReceiver()
{
    socket->~QUdpSocket();
}


void UdpReceiver::readPendingDatagrams()
{
    //while data is available
    while (socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender = RECEIVING_IP;
        quint16 senderPort = RECEIVING_PORT;

        socket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);


        //Read Packet Header
        std::string packetHeader(datagram.constData(), 6);
        if(packetHeader.compare("EARNLS")==0)
        {
            emit ackRunLaser();
        }
        else if(packetHeader.compare("EASTLS")==0)
        {
            emit ackStopLaser();
        }
        else if(packetHeader.compare("EASFFS")==0)
        {
            emit ackFullScanMode();
        }
        else if(packetHeader.compare("EASBES")==0)
        {
            emit ackBoundedElevation();
        }
        else if(packetHeader.compare("EASRES")==0)
        {
            emit ackRegionScan();
        }
        else
        {
            parseDatagram(datagram);
        }
    }

}


void UdpReceiver::parseDatagram(QByteArray datagram)
{
    unsigned char* dataPointer = reinterpret_cast<unsigned char*>(datagram.data());

    for(int i=0; i<100; i++)
    {
        unsigned short azimuthalAngle = dataPointer[8*i + 1]<<8 |  dataPointer[8*i];
        short elevationAngle = dataPointer[8*i + 3]<<8 |  dataPointer[8*i + 2];
        unsigned short range = dataPointer[8*i + 5]<<8 |  dataPointer[8*i + 4];

        if(elevationAngle>3501 || elevationAngle <-3500)
        {
            qDebug()<<"Elevation Angle out of Range";
        }

        float elevationAngleConverted = ((float)elevationAngle)/100.0;
        float azimuthalAngleConverted = ((float)azimuthalAngle)/100.0;
        float rangeConverted = ((float)range)/1000.0;


        float x = rangeConverted*sin(PIBY2 - elevationAngleConverted*0.0174532925)*cos(azimuthalAngleConverted*0.0174532925);
        float z = - rangeConverted*sin(PIBY2 - elevationAngleConverted*0.0174532925)*sin(azimuthalAngleConverted*0.0174532925);
        float y = rangeConverted*cos(PIBY2 - elevationAngleConverted*0.0174532925);



        if(i==37)
        {
            qDebug()<<"Point : "<<x<<" "<<y<<" "<<z;
        }
    }
}

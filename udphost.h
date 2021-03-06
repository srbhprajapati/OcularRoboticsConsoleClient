#ifndef UDPHOST_H
#define UDPHOST_H

#include <QtNetwork/QUdpSocket>

class UdpHost : public QObject
{
    public:

        //Constructor
        UdpHost();

        //Destructor
        ~UdpHost();

        //Sends datagram for Full Field Scan mode
        bool setFullFieldScan(int Azimuthal_value, int Scanline_value);

        //Sends datagram for Bounded Elevation Scan mode
        bool setBoundedElevationScan(int Azimuthal_value, int Scanline_value, float upper_bound, float lower_bound);

        //Sends datagram for Region Scan mode
        bool setRegionScan(int Azimuthal_value, int Scanline_value, float upper_bound, float lower_bound, float lAngular, float rAngular);

        //Sends datagram for starting the laser sensor simulator
        bool runLaserSensor(int Azimuthal_value, int Scanline_value);

        //Sends the new position of the Sensor
        bool setLaserSensorPosition(float x, float y, float z, float roll, float pitch, float yaw);

        //Sends datagram for stopping the sensor
        bool stopLaserSensor();

        //Opens a new Model as simulation Model
        bool openModel(QString filename);


        //Saves the Point Cloud
        bool saveModel(QString filename);


    private:

        //Socket for sending data
        QUdpSocket *socket;

        //Convert Integer to char array
        void _intToChar(unsigned int &num, unsigned char* array);

        //Convert Short to char Array
        void _shortToChar(short &num, unsigned char* array);
};

#endif // UDPHOST_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(on_openAction_clicked()));


    _udpSender = new UdpHost();

    _udpReceiver = new UdpReceiver();

    QObject::connect(_udpReceiver, SIGNAL(ackRunLaser()), this, SLOT(ackRunLaser()));
    QObject::connect(_udpReceiver, SIGNAL(ackStopLaser()), this, SLOT(ackStopLaser()));
    QObject::connect(_udpReceiver, SIGNAL(ackFullScanMode()), this, SLOT(ackFullScanMode()));
    QObject::connect(_udpReceiver, SIGNAL(ackBoundedElevation()), this, SLOT(ackBoundedElevation()));
    QObject::connect(_udpReceiver, SIGNAL(ackRegionScan()), this, SLOT(ackRegionScan()));
    QObject::connect(_udpReceiver, SIGNAL(ackLaserSensorPosition()), this, SLOT(ackLaserSensorPosition()));

}

MainWindow::~MainWindow()
{
    delete ui;

    _udpSender->~UdpHost();

    _udpReceiver->~UdpReceiver();
}


void MainWindow::on_startLaserButton_clicked()
{
    //Read Azimuthal and Elevation Value
    int Azimuthal_value = ui->AzimuthalspinBox->value();
    int Scanline_value = ui->scanLineSpinBox->value();

    //Set Azimuthal and Elevation Value to display tag
    ui->AzimuthalFullScanLabel->setText(QString::number(Azimuthal_value));
    ui->ScanLineFullScanLabel->setText(QString::number(Scanline_value));

    //For starting the rendering in ClientGLWidget
    //ui->widget->start_laser(Azimuthal_value, Scanline_value);
    _udpSender->runLaserSensor(Azimuthal_value, Scanline_value);

    _tempAzimuthalFrequency = Azimuthal_value;
    _tempNumberScanline = Scanline_value;


}

void MainWindow::on_stopLaserButton_clicked()
{
    //For stopping the rendering in ClientGLWidget
    //ui->widget->stopLaserSensor();
    _udpSender->stopLaserSensor();

}


void MainWindow::on_fullScanModeButton_clicked()
{
    //Read Azimuthal and Elevation Value
    int Azimuthal_value = ui->AzimuthalspinBox->value();
    int Scanline_value = ui->scanLineSpinBox->value();

    //Set Azimuthal and Elevation Value to display tag
    ui->AzimuthalFullScanLabel->setText(QString::number(Azimuthal_value));
    ui->ScanLineFullScanLabel->setText(QString::number(Scanline_value));

    //call Full Field Scan method in ClientGLWidget
    //ui->widget->setFullFieldScan(Azimuthal_value, Scanline_value);
    _udpSender->setFullFieldScan(Azimuthal_value, Scanline_value);

    _tempAzimuthalFrequency = Azimuthal_value;
    _tempNumberScanline = Scanline_value;


}


void MainWindow::on_boundedElevationModeButton_clicked()
{

    //Read Azimuthal and Elevation Value
    int Azimuthal_value = ui->AzimuthalspinBox->value();
    int Scanline_value = ui->scanLineSpinBox->value();

    //Read Upper and Lower Bound Values
    float upper_bound = ui->UpperBoundSpinBox->value();
    float lower_bound = ui->LowerBoundSpinBox->value();

    //call Bounded Elevation Scan method in ClientGLWidget
    //ui->widget->setBoundedElevationScan(Azimuthal_value, Scanline_value, upper_bound, lower_bound);
    _udpSender->setBoundedElevationScan(Azimuthal_value, Scanline_value, upper_bound, lower_bound);


    _tempAzimuthalFrequency = Azimuthal_value;
    _tempNumberScanline = Scanline_value;
    _tempUpperBound = upper_bound;
    _tempLowerBound = lower_bound;


}

void MainWindow::on_regionScanModeButton_clicked()
{
    //Read Azimuthal and Elevation Value
    int Azimuthal_value = ui->AzimuthalspinBox->value();
    int Scanline_value = ui->scanLineSpinBox->value();

    //Read Upper Bound, LowerBound, Left Bound, and Right Bound from the UI
    float upper_bound = ui->UpperBoundRegionSpinBox->value();
    float lower_bound = ui->LowerBoundRegionSpinBox->value();
    float lAngular = ui->AngularLeftSpinBox->value();
    float rAngular = ui->AngularRightSpinBox->value();

    //call Bounded Elevation Scan method in ClientGLWidget
    //ui->widget->setRegionScan(Azimuthal_value, Scanline_value, upper_bound, lower_bound, lAngular, rAngular);
    _udpSender->setRegionScan(Azimuthal_value, Scanline_value, upper_bound, lower_bound, lAngular, rAngular);


    _tempAzimuthalFrequency = Azimuthal_value;
    _tempNumberScanline = Scanline_value;
    _tempUpperBound = upper_bound;
    _tempLowerBound = lower_bound;
    _tempLAngular = lAngular;
    _tempRAngular = rAngular;


}


void MainWindow::on_openAction_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/", tr("Data Files( *.obj *.ply)"));
    if(!filename.isEmpty())
    {
        _udpSender->openModel(filename);
    }

}


void MainWindow::on_actionSave_triggered()
{

    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "C:/", tr("Data Files(*.pcd)"));

    if(!filename.isEmpty())
    {
        _udpSender->saveModel(filename);
    }

}


void MainWindow::ackRunLaser()
{

    _azimuthalFrequency = _tempAzimuthalFrequency;
    _numberScanline = _tempNumberScanline;

    //Azimuthal Frequency
    ui->AzimuthalFullScanLabel->setText(QString::number(_tempAzimuthalFrequency));
    ui->AzimuthalFreqLabel->setText(QString::number(_tempAzimuthalFrequency));

    //Number of Scanlines
    ui->ScanLineFullScanLabel->setText(QString::number(_tempNumberScanline));
    ui->scanLinesValueLabel->setText(QString::number(_tempNumberScanline));

    //Sampling Frequency
    ui->samplingFreqValueLabel->setText(QString::number(5000));
    _samplingFrequency = 5000;

    //Total Number of Points
    ui->TotalPointsValueLabel->setText(QString::number(100000));
    _totalPoints = 100000;

    //Sensor Position
    ui->LaserXValueLabel->setText(QString::number(ui->LaserXSpinBox->value()));
    ui->LaserYValueLabel->setText(QString::number(ui->LaserYSpinBox->value()));
    ui->LaserZValueLabel->setText(QString::number(ui->LaserZSpinBox->value()));
    _laserSensorPosition[0] = ui->LaserXSpinBox->value();
    _laserSensorPosition[1] = ui->LaserYSpinBox->value();
    _laserSensorPosition[2] = ui->LaserZSpinBox->value();


    //Maximum Range of the Sensor
    ui->maxRangeValueLabel->setText(QString::number(10.0));
    _maximumRange = 10.0;

    //Scan Mode for the Sensor
    ui->scanModeValueLabel->setText(QString("FS"));
    _sensorScanMode = FULL_FIELD_SCAN;

    //Laser Sensor Status
    ui->LaserStatusLabel->setText(QString("ON"));
    _sensorStatus = ON;

}

void MainWindow::ackStopLaser()
{
    //Set Value to Other Text Labels
    ui->LaserStatusLabel->setText(QString("OFF"));
    _sensorStatus = OFF;
}

void MainWindow::ackFullScanMode()
{

    _azimuthalFrequency = _tempAzimuthalFrequency;
    _numberScanline = _tempNumberScanline;

    //Set Value to Other Text Labels
    ui->scanModeValueLabel->setText(QString("FS"));
    _sensorScanMode = FULL_FIELD_SCAN;

    ui->AzimuthalFullScanLabel->setText(QString::number(_tempAzimuthalFrequency));
    ui->AzimuthalFreqLabel->setText(QString::number(_tempAzimuthalFrequency));

    ui->ScanLineFullScanLabel->setText(QString::number(_tempNumberScanline));
    ui->scanLinesValueLabel->setText(QString::number(_tempNumberScanline));
}

void MainWindow::ackBoundedElevation()
{

    _azimuthalFrequency = _tempAzimuthalFrequency;
    _numberScanline = _tempNumberScanline;
    _upperBound = _tempUpperBound;
    _lowerBound = _tempLowerBound;

    //Set Value to Other Text Labels
    ui->scanModeValueLabel->setText(QString("BES"));
    _sensorScanMode = BOUNDED_ELEVATION_SCAN;

}

void MainWindow::ackRegionScan()
{

    _azimuthalFrequency = _tempAzimuthalFrequency;
    _numberScanline = _tempNumberScanline;
    _upperBound = _tempUpperBound;
    _lowerBound = _tempLowerBound;
    _lAngular = _tempLAngular;
    _rAngular = _tempRAngular;

    //Set Value to Other Text Labels
    ui->scanModeValueLabel->setText(QString("RS"));
    _sensorScanMode = REGION_SCAN;
}

void MainWindow::ackLaserSensorPosition()
{
    _laserSensorPosition[0] = _tempLaserSensorPosition[0];
    _laserSensorPosition[1] = _tempLaserSensorPosition[1];
    _laserSensorPosition[2] = _tempLaserSensorPosition[2];

    _laserSensorOrientation[0] = _tempLaserSensorOrientation[0];
    _laserSensorOrientation[1] = _tempLaserSensorOrientation[1];
    _laserSensorOrientation[2] = _tempLaserSensorOrientation[2];
}

void MainWindow::on_LaserPositionButton_clicked()
{
    _tempLaserSensorPosition[0] = ui->LaserXSpinBox->value();
    _tempLaserSensorPosition[1] = ui->LaserYSpinBox->value();
    _tempLaserSensorPosition[2] = ui->LaserZSpinBox->value();

    _tempLaserSensorOrientation[0] = ui->RollSpinBox->value();
    _tempLaserSensorOrientation[1] = ui->PitchSpinBox->value();
    _tempLaserSensorOrientation[2] = ui->YawSpinBox->value();

    _udpSender->setLaserSensorPosition(_tempLaserSensorPosition[0],
                                       _tempLaserSensorPosition[1],
                                       _tempLaserSensorPosition[2],
                                       _tempLaserSensorOrientation[0],
                                       _tempLaserSensorOrientation[1],
                                       _tempLaserSensorOrientation[2]);

}


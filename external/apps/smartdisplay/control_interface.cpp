#include "control_interface.h"
#include <iostream>

Control_Interface::Control_Interface(QMqttClient *client)
{
    _controlGroupBox = new QGroupBox;
    _controlLayout = new QHBoxLayout;
    _client = client;

    _statusWidget = new QLabel;
    _statusWidget->setText("Status: ");
    _statusWidget->setStyleSheet("QLabel{font-family: Cornerstone; font: bold; font-size: 10px;}");
    connect(_client, &QMqttClient::stateChanged, this, &Control_Interface::updateLogStateChange);
    _controlLayout->addWidget(_statusWidget,0,Qt::AlignLeft);

    _hostStatus = new QLabel;
    _hostStatus->setText("Host: " + _client->hostname());
    _hostStatus->setStyleSheet("QLabel{font-family: Cornerstone; font: bold; font-size: 10px;}");
    connect(_client, &QMqttClient::hostnameChanged, this, &Control_Interface::updateHostName);
    _controlLayout->addWidget(_hostStatus,0,Qt::AlignLeft);

    _connectButton = new QPushButton;
    _connectButton->setStyleSheet("QPushButton{background: #41d0f4; font-family: Cornerstone; font: bold; font-size: 20px; padding: 5px; border-style: outset; border-width: 2px; border-radius: 10px; border-color: #41d0f4; outline: none;}");
    _connectButton->setText("Connect");
    QObject::connect(_connectButton, SIGNAL (clicked()), this, SLOT(connectHandle()));
    _controlLayout->addWidget(_connectButton,0,Qt::AlignRight);

    _controlButton = new QPushButton;
    _controlButton->setIcon(QPixmap(":/Images/configure_button.png"));
    _controlButton->setIconSize(QSize(40,40));
    _controlButton->setStyleSheet("QPushButton{background: #dbf5fc; padding: 5px; border: none; outline: none;}");
    QObject::connect(_controlButton, SIGNAL (clicked()), this, SLOT(configHandle()));
    _controlLayout->addWidget(_controlButton,0,Qt::AlignRight);

    updateLogStateChange(_client->state());
    _controlGroupBox->setLayout(_controlLayout);
    _controlGroupBox->setStyleSheet("QGroupBox{background: #dbf5fc;}");
    _controlGroupBox->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
}

Control_Interface::~Control_Interface(){
    delete _controlGroupBox;
    delete _controlLayout;
    delete _statusWidget;
    delete _hostStatus;
    delete _controlButton;
    delete _connectButton;

}

// Slots Handles:
void Control_Interface::updateLogStateChange(QMqttClient::ClientState state){
    QString text;
    switch(state){
        case 0:
            text = "Disconnected";
            _connectButton->setText("Connect");
        break;
        case 1:
            text = "Connecting";
        break;
        case 2:
            text = "Connected";
            _connectButton->setText("Disconnect");
            _client->subscribe(QString("home/#"),2);
        break;
        default:
        break;
    }
    _statusWidget->setText("Status: " + text);
}
void Control_Interface::updateHostName(){
    _hostStatus->setText("Host: " + _client->hostname());
}

void Control_Interface::configHandle(){

}

void Control_Interface::connectHandle(){
    switch(_client->state()){
        case 0:
            _connectButton->setText("Disconnect");
            _client->connectToHost();
        break;
        case 2:
            _connectButton->setText("Connect");
            _client->disconnectFromHost();
        break;
        default:
        break;
    }

}

#include <QtMqtt/QMqttClient>
#include "smartdisplay.h"
#include <QWidget>

#define PROJECT_VERSION "SmartDisplay v1.0"

SmartDisplay::SmartDisplay()
{
    _client = new QMqttClient();
    _client->setHostname("192.168.2.1");
    _client->setPort(1883);

    _window = new QWidget;
    _window->setFixedSize(1024, 600);
    _window->setWindowTitle("     ");
    _window->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    _window->setStyleSheet("QWidget{background: #dbf5fc;}");
    _window->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    setCentralWidget(_window);

    _windowLayout = new QVBoxLayout();

    _controlInterface = new Control_Interface(_client);
    _windowLayout->addWidget(_controlInterface->getControlBox());
    _windowLayout->setAlignment(Qt::AlignTop);

    _topicInterface = new Topics_Interface(_client);
    _windowLayout->addWidget(_topicInterface->getTopicBox());
    _windowLayout->setAlignment(Qt::AlignTop);

    _window->setLayout(_windowLayout);
}

SmartDisplay::~SmartDisplay(){
    delete _client;
    delete _windowLayout;
    delete _controlInterface;
    delete _topicInterface;
}


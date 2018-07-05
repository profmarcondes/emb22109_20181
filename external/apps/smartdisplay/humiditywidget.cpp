#include "humiditywidget.h"

HumidityWidget::HumidityWidget(QString topic,QString msg)
{
    _card = new QGroupBox;
    _cardLayout = new QVBoxLayout;

    _topic = new QLabel(topic);
    _topic->setStyleSheet("QLabel{background-color: #41d0f4;font-family: Cornerstone; font: bold; font-size: 10px; font-color: #ffffff}");
    _topic->setFixedSize(100,30);
    _cardLayout->addWidget(_topic);

    _humIcon = new QPushButton;
    _humIcon->setIcon(QPixmap(":/Images/hum_icon.png"));
    _humIcon->setIconSize(QSize(100,50));
    _humIcon->setStyleSheet("QPushButton{background: #41d0f4; border: none; outline: none;}");
    _cardLayout->addWidget(_humIcon);

    _humValue = new QLabel(msg);
    _humValue->setStyleSheet("QLabel{background-color: #ffffff; font-family: Cornerstone; font: bold; font-size: 25px; text-align: center; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #727272;}");
    _humValue->setAlignment(Qt::AlignCenter);
    _humValue->setFixedSize(100,80);
    _humValue->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    _cardLayout->addWidget(_humValue);

    _card->setLayout(_cardLayout);
    _card->setStyleSheet("QGroupBox{background-color: #41d0f4; padding: 0px; border-color: #000000; outline: none; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #000000;}");
    _card->setFixedSize(120,200);
}

HumidityWidget::~HumidityWidget(){
    delete _topic;
    delete _humValue;
    delete _humIcon;
    delete _cardLayout;
    delete _card;
}

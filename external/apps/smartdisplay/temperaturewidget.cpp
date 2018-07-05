#include "temperaturewidget.h"
#include <QLayout>

TemperatureWidget::TemperatureWidget(QString topic,QString msg)
{
    _card = new QGroupBox;
    _cardLayout = new QVBoxLayout;

    _topic = new QLabel(topic);
    _topic->setStyleSheet("QLabel{background-color: #41d0f4;font-family: Cornerstone; font: bold; font-size: 10px; font-color: #ffffff}");
    _topic->setFixedSize(100,30);
    _cardLayout->addWidget(_topic);

    _tempIcon = new QPushButton;
    _tempIcon->setIcon(QPixmap(":/Images/temp_icon.png"));
    _tempIcon->setIconSize(QSize(100,50));
    _tempIcon->setStyleSheet("QPushButton{background: #41d0f4; border: none; outline: none;}");
    _cardLayout->addWidget(_tempIcon);

    _tempValue = new QLabel(msg);
    _tempValue->setStyleSheet("QLabel{background-color: #ffffff; font-family: Cornerstone; font: bold; font-size: 25px; text-align: center; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #727272;}");
    _tempValue->setAlignment(Qt::AlignCenter);
    _tempValue->setFixedSize(100,80);
    _tempValue->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    _cardLayout->addWidget(_tempValue);

    _card->setLayout(_cardLayout);
    _card->setStyleSheet("QGroupBox{background-color: #41d0f4; padding: 0px; border-color: #000000; outline: none; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #000000;}");
    _card->setFixedSize(120,200);
}

TemperatureWidget::~TemperatureWidget(){
    delete _topic;
    delete _tempValue;
    delete _tempIcon;
    delete _cardLayout;
    delete _card;
}

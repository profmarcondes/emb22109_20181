#include "lumenwidget.h"

LumenWidget::LumenWidget(QString topic,QString msg)
{
    _card = new QGroupBox;
    _cardLayout = new QVBoxLayout;

    _topic = new QLabel(topic);
    _topic->setStyleSheet("QLabel{background-color: #41d0f4;font-family: Cornerstone; font: bold; font-size: 10px; font-color: #ffffff}");
    _topic->setFixedSize(100,30);
    _cardLayout->addWidget(_topic);

    _LumenIcon = new QPushButton;
    _LumenIcon->setIcon(QPixmap(":/Images/lumen_icon.png"));
    _LumenIcon->setIconSize(QSize(100,50));
    _LumenIcon->setStyleSheet("QPushButton{background: #41d0f4; border: none; outline: none;}");
    _cardLayout->addWidget(_LumenIcon);

    _LumenValue = new QLabel(msg);
    _LumenValue->setStyleSheet("QLabel{background-color: #ffffff; font-family: Cornerstone; font: bold; font-size: 25px; text-align: center; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #727272;}");
    _LumenValue->setAlignment(Qt::AlignCenter);
    _LumenValue->setFixedSize(100,80);
    _LumenValue->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    _cardLayout->addWidget(_LumenValue);

    _card->setLayout(_cardLayout);
    _card->setStyleSheet("QGroupBox{background-color: #41d0f4; padding: 0px; border-color: #000000; outline: none; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #000000;}");
    _card->setFixedSize(120,200);
}

LumenWidget::~LumenWidget(){
    delete _topic;
    delete _LumenValue;
    delete _LumenIcon;
    delete _cardLayout;
    delete _card;
}

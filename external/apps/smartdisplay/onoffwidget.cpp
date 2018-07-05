#include "onoffwidget.h"
#include <string.h>

OnOffWidget::OnOffWidget(QString topic,QMqttClient *client,QString msg)
{
    _card = new QGroupBox;
    _cardLayout = new QVBoxLayout;

    _client = client;

    _topic = new QLabel(topic);
    _topic->setStyleSheet("QLabel{background-color: #41d0f4;font-family: Cornerstone; font: bold; font-size: 10px; font-color: #ffffff}");
    _topic->setFixedSize(100,30);
    _cardLayout->addWidget(_topic);

    _onoffIcon = new QPushButton;
    if(msg.toInt() == 1)
    {
        _status = 1;
        _onoffIcon->setIcon(QPixmap(":/Images/on_icon.png"));
    }
    else
    {
        _onoffIcon->setIcon(QPixmap(":/Images/off_icon.png"));
        _status = 0;
    }
    _onoffIcon->setIconSize(QSize(100,50));
    _onoffIcon->setStyleSheet("QPushButton{background: #41d0f4; border: none; outline: none;}");
    QObject::connect(_onoffIcon, SIGNAL (clicked()), this, SLOT(onoffHandle()));
    _cardLayout->addWidget(_onoffIcon);

    _onoffValue = new QLabel;
    if(_status == 1)
        _onoffValue->setText("ON");
    else
        _onoffValue->setText("OFF");
    _onoffValue->setStyleSheet("QLabel{background-color: #ffffff; font-family: Cornerstone; font: bold; font-size: 25px; text-align: center; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #727272;}");
    _onoffValue->setAlignment(Qt::AlignCenter);
    _onoffValue->setFixedSize(100,80);
    _onoffValue->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    _cardLayout->addWidget(_onoffValue);

    _card->setLayout(_cardLayout);
    _card->setStyleSheet("QGroupBox{background-color: #41d0f4; padding: 0px; border-color: #000000; outline: none; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #000000;}");
    _card->setFixedSize(120,200);
}

void OnOffWidget::onoffHandle(){
    if(_status == 1){
        _status = 0;
        _onoffIcon->setIcon(QPixmap(":/Images/off_icon.png"));
        _client->publish(QMqttTopicName(_topic->text()),"0",2,false);
        _onoffValue->setText("OFF");
    }
    else{
        _status = 1;
        _onoffIcon->setIcon(QPixmap(":/Images/on_icon.png"));
        _client->publish(QMqttTopicName(_topic->text()),"1",2,false);
        _onoffValue->setText("ON");
    }
}

void OnOffWidget::setOnOff(QString value){
    if(QString(value).toInt() == 1){
        _status = 1;
        _onoffIcon->setIcon(QPixmap(":/Images/on_icon.png"));
        _onoffValue->setText("ON");
    }
    else if(QString(value).toInt() == 0){
        _status = 0;
        _onoffIcon->setIcon(QPixmap(":/Images/off_icon.png"));
        _onoffValue->setText("OFF");
    }
}

OnOffWidget::~OnOffWidget(){
    delete _topic;
    delete _onoffValue;
    delete _onoffIcon;
    delete _cardLayout;
    delete _card;
}

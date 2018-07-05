#include "dimerwidget.h"

DimerWidget::DimerWidget(QString topic,QMqttClient *client,QString msg)
{
    _client = client;

    _card = new QGroupBox;
    _cardLayout = new QVBoxLayout;

    _topic = new QLabel(topic);
    _topic->setStyleSheet("QLabel{background-color: #41d0f4;font-family: Cornerstone; font: bold; font-size: 10px; font-color: #ffffff}");
    _topic->setFixedSize(100,30);
    _cardLayout->addWidget(_topic);

    _dimerIcon = new QPushButton;
    _dimerIcon->setIcon(QPixmap(":/Images/dimer_icon.png"));
    _dimerIcon->setIconSize(QSize(100,30));
    _dimerIcon->setStyleSheet("QPushButton{background: #41d0f4; border: none; outline: none;}");
    _cardLayout->addWidget(_dimerIcon);

    _dimerSlider = new QSlider(Qt::Horizontal,NULL);
    _dimerSlider->setRange(0,100);
    _dimerSlider->setValue(msg.toInt());
    _dimerSlider->setBaseSize(100,20);
    _dimerSlider->setStyleSheet("QSlider {background-color: #41d0f4}");
    QObject::connect(_dimerSlider, SIGNAL (valueChanged(int)), this, SLOT(dimerHandle(int)));
    _cardLayout->addWidget(_dimerSlider);

    _dimerValue = new QLabel(msg);
    _dimerValue->setStyleSheet("QLabel{background-color: #ffffff; font-family: Cornerstone; font: bold; font-size: 25px; text-align: center; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #727272;}");
    _dimerValue->setAlignment(Qt::AlignCenter);
    _dimerValue->setFixedSize(100,80);
    _dimerValue->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    _cardLayout->addWidget(_dimerValue);

    _card->setLayout(_cardLayout);
    _card->setStyleSheet("QGroupBox{background-color: #41d0f4; padding: 0px; border-color: #000000; outline: none; border-style: solid; border-width: 2px; border-radius: 10px; border-color: #000000;}");
    _card->setFixedSize(120,200);
}

DimerWidget::~DimerWidget(){
    delete _topic;
    delete _dimerValue;
    delete _dimerIcon;
    delete _dimerSlider;
    delete _cardLayout;
    delete _card;
}

void DimerWidget::dimerHandle(int value){
    _dimerValue->setText(QString::number(value));
    _client->publish(QMqttTopicName(_topic->text()),QByteArray(_dimerValue->text().toLocal8Bit(),3),2,false);
}

void DimerWidget::setDimer(QString value){
    if(QString(value).toInt() >= 0 && QString(value).toInt() <= 0){
        _dimerValue->setText(value);
        _dimerSlider->setValue(QString(value).toInt());
    }
}

#ifndef HUMIDITYWIDGET_H
#define HUMIDITYWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>
#include <QtMqtt/QMqttClient>

class HumidityWidget : public QWidget
{
    Q_OBJECT
public:
    HumidityWidget(QString topic,QString msg);
    ~HumidityWidget();

    QGroupBox* getHumBox() {return _card;}
    void setHumidity(QString value) {_humValue->setText(value);}
private:
    QMqttClient *_client;

    QLabel *_topic;
    QLabel *_humValue;
    QPushButton *_humIcon;

    QGroupBox *_card;
    QLayout *_cardLayout;
};

#endif // HUMIDITYWIDGET_H

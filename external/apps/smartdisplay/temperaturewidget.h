#ifndef TEMPERATUREWIDGET_H
#define TEMPERATUREWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>
#include <QtMqtt/QMqttClient>

class TemperatureWidget : public QWidget
{
    Q_OBJECT
public:
    TemperatureWidget(QString topic,QString msg);
    ~TemperatureWidget();

    QGroupBox* getTempBox() {return _card;}
    void setTemp(QString value) {_tempValue->setText(value);}
private:
    QMqttClient *_client;

    QLabel *_topic;
    QLabel *_tempValue;
    QPushButton *_tempIcon;

    QGroupBox *_card;
    QLayout *_cardLayout;
};

#endif // TEMPERATUREWIDGET_H

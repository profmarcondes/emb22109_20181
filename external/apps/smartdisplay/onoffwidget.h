#ifndef ONOFFWIDGET_H
#define ONOFFWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>
#include <QtMqtt/QMqttClient>

class OnOffWidget : public QWidget
{
    Q_OBJECT
public:
    OnOffWidget(QString topic,QMqttClient *client,QString msg);
    ~OnOffWidget();
    QGroupBox* getOnOffBox() {return _card;}

    void setOnOff(QString value);
private:
    QMqttClient *_client;

    QLabel *_topic;
    QLabel *_onoffValue;
    QPushButton *_onoffIcon;

    QGroupBox *_card;
    QLayout *_cardLayout;

    qint8   _status;
private slots:
    void onoffHandle();
};

#endif // ONOFFWIDGET_H

#ifndef LUMENWIDGET_H
#define LUMENWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>
#include <QtMqtt/QMqttClient>

class LumenWidget : public QWidget
{
    Q_OBJECT
public:
    LumenWidget(QString topic,QString msg);
    ~LumenWidget();
    QGroupBox* getLumenBox() {return _card;}
    void setLumen(QString value) {_LumenValue->setText(value);}
private:
    QMqttClient *_client;

    QLabel *_topic;
    QLabel *_LumenValue;
    QPushButton *_LumenIcon;

    QGroupBox *_card;
    QLayout *_cardLayout;
};

#endif // LUMENWIDGET_H

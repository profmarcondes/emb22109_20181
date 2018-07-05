#ifndef TOPICS_INTERFACE_H
#define TOPICS_INTERFACE_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QtMqtt/QMqttClient>
#include "temperaturewidget.h"
#include "humiditywidget.h"
#include "lumenwidget.h"
#include "onoffwidget.h"
#include "dimerwidget.h"

class Topics_Interface : public QWidget
{
    Q_OBJECT
public:
    Topics_Interface(QMqttClient* client);
    ~Topics_Interface();

    QGroupBox* getTopicBox(){return _topicBox;}

private:
    QMqttClient *_client;
    std::map<QString, void*> _widgetsTable;
    QGroupBox *_topicBox;
    QGridLayout *_topicLayout;
private slots:
    void messageHandle(const QByteArray &message, const QMqttTopicName &topic);
};

#endif // TOPICS_INTERFACE_H

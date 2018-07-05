#include <QtMqtt/QMqttClient>
#include <QMainWindow>

#ifndef SMARTDISPLAY_H
#define SMARTDISPLAY_H

#include "control_interface.h"
#include "topics_interface.h"

class SmartDisplay : public QMainWindow
{
    Q_OBJECT
    QWidget *_window;
public:
    SmartDisplay();
    ~SmartDisplay();
private:
    QMqttClient *_client;
    QLayout *_windowLayout;
    Control_Interface *_controlInterface;
    Topics_Interface *_topicInterface;
};

#endif // SMARTDISPLAY_H

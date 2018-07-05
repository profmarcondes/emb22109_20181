#ifndef CONTROL_INTERFACE_H
#define CONTROL_INTERFACE_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <qpushbutton.h>
#include <QLabel>
#include <QtMqtt/QMqttClient>

class Control_Interface : public QObject
{
    Q_OBJECT
public:
    Control_Interface(QMqttClient *client);
    ~Control_Interface();
// GETTERS AND SETTERS
    QGroupBox * getControlBox() { return _controlGroupBox; }
private:
    QGroupBox *_controlGroupBox;
    QHBoxLayout *_controlLayout;
    QMqttClient *_client;

    QLabel *_statusWidget;
    QLabel *_hostStatus;
    QPushButton *_controlButton;
    QPushButton *_connectButton;
private slots:
    void updateLogStateChange(QMqttClient::ClientState state);
    void updateHostName();
    void configHandle();
    void connectHandle();
};

#endif // CONTROL_INTERFACE_H

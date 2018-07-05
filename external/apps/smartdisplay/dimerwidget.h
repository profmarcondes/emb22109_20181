#ifndef DIMERWIDGET_H
#define DIMERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>
#include <QSlider>
#include <QtMqtt/QMqttClient>

class DimerWidget : public QWidget
{
    Q_OBJECT
public:
    DimerWidget(QString topic,QMqttClient *client,QString msg);
    ~DimerWidget();

    QGroupBox* getDimerBox() {return _card;}
    void setDimer(QString value);
private:
    QMqttClient *_client;

    QLabel *_topic;
    QLabel *_dimerValue;
    QPushButton *_dimerIcon;
    QSlider *_dimerSlider;

    QGroupBox *_card;
    QLayout *_cardLayout;
private slots:
    void dimerHandle(int value);
};

#endif // DIMERWIDGET_H

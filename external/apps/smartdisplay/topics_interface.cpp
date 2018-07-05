#include "topics_interface.h"


Topics_Interface::Topics_Interface(QMqttClient* client)
{
    _topicBox = new QGroupBox;
    _topicLayout = new QGridLayout;

    _client = client;

    connect(_client, &QMqttClient::messageReceived, this, &Topics_Interface::messageHandle);

    _topicLayout->setHorizontalSpacing(20);
    _topicBox->setLayout(_topicLayout);
    _topicBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}

void Topics_Interface::messageHandle(const QByteArray &message, const QMqttTopicName &topic){
   const QString msgContent = message;

   const QString topicContent = topic.name();
   QStringList topicList = topicContent.split(QRegExp("/"));

   std::map<QString,void*>::iterator it;
   it = _widgetsTable.find(topicContent);
   if(it == _widgetsTable.end()){
       if((_widgetsTable.size() >= 7) && (_widgetsTable.size() < 14) ){
           if(QString(topicList.last()).contains("temp")){
               _widgetsTable[topicContent] = new TemperatureWidget(topicContent,msgContent);
               _topicLayout->addWidget(((TemperatureWidget*)_widgetsTable[topicContent])->getTempBox(),2,_widgetsTable.size()-7,Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("onoff")){
               _widgetsTable[topicContent] = new OnOffWidget(topicContent,_client,msgContent);
               _topicLayout->addWidget(((OnOffWidget*)_widgetsTable[topicContent])->getOnOffBox(),2,_widgetsTable.size()-7,Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("dimer")){
               _widgetsTable[topicContent] = new DimerWidget(topicContent,_client,msgContent);
               _topicLayout->addWidget(((DimerWidget*)_widgetsTable[topicContent])->getDimerBox(),2,_widgetsTable.size()-7,Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("humidity")){
               _widgetsTable[topicContent] = new HumidityWidget(topicContent,msgContent);
               _topicLayout->addWidget(((HumidityWidget*)_widgetsTable[topicContent])->getHumBox(),2,_widgetsTable.size()-7,Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("lumen")){
               _widgetsTable[topicContent] = new LumenWidget(topicContent,msgContent);
               _topicLayout->addWidget(((LumenWidget*)_widgetsTable[topicContent])->getLumenBox(),2,_widgetsTable.size()-7,Qt::AlignCenter);
           }

       }
       else if(_widgetsTable.size() < 7){
           if(QString(topicList.last()).contains("temp")){
               _widgetsTable[topicContent] = new TemperatureWidget(topicContent,msgContent);
               _topicLayout->addWidget(((TemperatureWidget*)_widgetsTable[topicContent])->getTempBox(),1,_widgetsTable.size(),Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("onoff")){
               _widgetsTable[topicContent] = new OnOffWidget(topicContent,_client,msgContent);
               _topicLayout->addWidget(((OnOffWidget*)_widgetsTable[topicContent])->getOnOffBox(),1,_widgetsTable.size(),Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("dimer")){
               _widgetsTable[topicContent] = new DimerWidget(topicContent,_client,msgContent);
               _topicLayout->addWidget(((DimerWidget*)_widgetsTable[topicContent])->getDimerBox(),1,_widgetsTable.size(),Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("humidity")){
               _widgetsTable[topicContent] = new HumidityWidget(topicContent,msgContent);
               _topicLayout->addWidget(((HumidityWidget*)_widgetsTable[topicContent])->getHumBox(),1,_widgetsTable.size(),Qt::AlignCenter);
           }
           else if(QString(topicList.last()).contains("lumen")){
               _widgetsTable[topicContent] = new LumenWidget(topicContent,msgContent);
               _topicLayout->addWidget(((LumenWidget*)_widgetsTable[topicContent])->getLumenBox(),1,_widgetsTable.size(),Qt::AlignCenter);
           }
       }
   }
   else{
       if(QString(topicList.last()).contains("temp")){
           ((TemperatureWidget*)_widgetsTable[topicContent])->setTemp(msgContent);
       }
       else if(QString(topicList.last()).contains("onoff",Qt::CaseInsensitive)){
           ((OnOffWidget*)_widgetsTable[topicContent])->setOnOff(msgContent);
       }
       else if(QString(topicList.last()).contains("dimer",Qt::CaseInsensitive)){
           ((DimerWidget*)_widgetsTable[topicContent])->setDimer(msgContent);
       }
       else if(QString(topicList.last()).contains("humidity",Qt::CaseInsensitive)){
           ((HumidityWidget*)_widgetsTable[topicContent])->setHumidity(msgContent);
       }
       else if(QString(topicList.last()).contains("lumen",Qt::CaseInsensitive)){
           ((LumenWidget*)_widgetsTable[topicContent])->setLumen(msgContent);
       }
   }
}

Topics_Interface::~Topics_Interface(){
    delete _topicBox;
    delete _topicLayout;
    std::map<QString,void*>::iterator it;
    it = _widgetsTable.begin();
    while(it != _widgetsTable.end()){
        if(QString(it->first).contains("temp",Qt::CaseInsensitive)){
            delete (TemperatureWidget*)it->second;
        }
        else if(QString(it->first).contains("onoff",Qt::CaseInsensitive)){
            delete (OnOffWidget*)it->second;
        }
        else if(QString(it->first).contains("dimer",Qt::CaseInsensitive)){
            delete (DimerWidget*)it->second;
        }
        else if(QString(it->first).contains("humidity",Qt::CaseInsensitive)){
            delete (HumidityWidget*)it->second;
        }
        else if(QString(it->first).contains("lumen",Qt::CaseInsensitive)){
            delete (LumenWidget*)it->second;
        }
        _widgetsTable.erase(it);
        it = _widgetsTable.begin();
    }
}



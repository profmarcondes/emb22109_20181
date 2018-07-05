/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/**************************LED PWM Pin Define*********************************/
#define LED_PIN 15
#define ONOFF_PIN 0

/*****************************DHT Defines*************************************/
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

/**************************TSL ID Definition**********************************/
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

/*************************Internal Functions**********************************/
void configureLumSensor(void)
{
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives better sensor resolution (402ms = 16-bit data) */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */

  /* Update these values depending on what you've set above! */  
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
}

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SmartFi"
#define WLAN_PASS       "smarthome"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "192.168.2.1"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "home"
#define AIO_KEY         "...your AIO key..."

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME);

/****************************** Feeds ***************************************/
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>

// Setup a feed called 'temperature' for publishing.
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");

// Setup a feed called 'humidity' for publishing.
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

// Setup a feed called 'luminosity' for publishing.
Adafruit_MQTT_Publish luminosity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/lumen");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");
Adafruit_MQTT_Publish onoff_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/onoff");

// Setup a feed called 'slider' for subscribing to changes.
Adafruit_MQTT_Subscribe slider = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/dimer");
Adafruit_MQTT_Publish slider_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dimer");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

/*************************Global Variables***********************************/
float hum;  //Stores humidity value
float temp; //Stores temperature value  

void setup() {
  Serial.begin(115200);

  // Init DHT
  dht.begin();

  // Setup the luminosity sensor gain and integration time
  configureLumSensor();

  pinMode(LED_PIN, OUTPUT);
  pinMode(ONOFF_PIN, OUTPUT);
  
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
  mqtt.subscribe(&slider);
  
  if (! slider_pub.publish(0)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  if (! onoff_pub.publish(0)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}

uint32_t x=0;

void loop() {
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp= dht.readTemperature();

  // Get a new sensor event 
  sensors_event_t event;
  tsl.getEvent(&event);

  MQTT_connect();
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      if (onoffbutton.lastread[0] == '0'){
        digitalWrite(ONOFF_PIN, 1);
      } else if (onoffbutton.lastread[0] == '1'){
        digitalWrite(ONOFF_PIN, 0);
      }
      //digitalWrite(ONOFF_PIN, (unsigned int)onoffbutton.lastread);
    }
    if (subscription == &slider) {
      Serial.print(F("Got: "));
      Serial.println((char *)slider.lastread);
      analogWrite(LED_PIN, 1023*100/(atoi((char*)slider.lastread)));
    }
  }

  // Now we can publish stuff!
  Serial.print(F("\nSending temperature val "));
  Serial.print(temp);
  Serial.println(" Celsius");
  Serial.print("...");
  if (! temperature.publish(temp)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  Serial.print(F("\nSending humidity val "));
  Serial.print(hum);
  Serial.print(" %");
  Serial.print("...");
  if (! humidity.publish(hum)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  Serial.print(F("\nSending luminosity val "));
  Serial.print(event.light);
  Serial.print(" lux");
  Serial.print("...");
  if (! luminosity.publish(event.light)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

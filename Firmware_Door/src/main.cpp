#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <mqtt/mqtt_service.h>
#include <time/time_control.h>
#include <DHT.h>


#define DHTPIN D5
#define magneticSensor D7
#define PINPUERTA D2
#define PINCORTINA D3

const char* ssid = "xx";
const char* password =  "xx";
const char* mqttServer = "xx";
//const char* mqttServer = "xx";
const int mqttPort = 	00;
const char* mqttUser = "xx";
const char* mqttPassword = "xx";

DHT dht;

const long utcOffsetInSeconds = -18000;

WiFiClient mqttCli;
PubSubClient client(mqttCli);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "south-america.pool.ntp.org", utcOffsetInSeconds);

String dataInv;
int doorStateAnt = HIGH;
int doorStateAct = HIGH;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void setup() {
  
  Serial.begin(115200);
  delay(10);

  //Connect to WiFi
  setup_wifi();

  //Connect to MQTT Broker
  mqtt_init();
 
  //MQTT Connection Validation
  mqtt_conect();

  //NTP client connection
  timeClient.begin();
  timeClient.update();
  sec_Ant = timeToNextRead();

  //Initilize humidity sensor
  dht.setup(DHTPIN);

  pinMode(PINPUERTA,OUTPUT);
  pinMode(PINCORTINA,OUTPUT);
  pinMode(magneticSensor, INPUT_PULLUP);
  doorStateAnt = digitalRead(magneticSensor);

  //attachInterrupt(digitalPinToInterrupt(magneticSensor), doorInterrupt(), CHANGE);

}

void loop() {
  client.loop();
  timeClient.update();
  sec_Act = timeClient.getSeconds();
  doorStateAct = digitalRead(magneticSensor);

  if(IsTimeToRead(sec_Act)){
    
    dataInv = ReadSensor();
    publishDataFormat(EnviromentTopic, dataInv);
    Serial.println(dataInv);
  }

  if(doorStateAct != doorStateAnt){
    doorInterrupt(doorStateAct);
    doorStateAnt = doorStateAct;
  }

  if (message_arrived)
  {
    message_arrived = false;
    jsonProcess(messageInTopic);
    Serial.println("llego mensaje");
    Serial.println(messageInTopic);
  }
}

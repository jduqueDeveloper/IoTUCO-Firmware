#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define InputTopic "input"
#define AliveTopic "alive"
#define GrowbedTopic "medicion/zona/1/invernadero/1/cama/1/ambiente"
#define controlCama "control/zona/1/invernadero/1/cama/1"
#define controlInvernadero "control/zona/1/invernadero/1"
#define controlZona "control/zona/1"
#define PINLUZ D2
#define PINVENTILADOR D3

extern const char* mqttServer;
extern const int mqttPort;
extern bool message_arrived;
extern PubSubClient client;
extern const char* mqttUser;
extern const char* mqttPassword;
extern String messageInTopic;
extern const char* topicIncome;

extern void mqtt_init();
extern void mqtt_conect();
extern void publishInTopic(const char* topic, const char* message);
extern void publishDataFormat(String message);
extern void jsonProcess(String topicMessage);
extern String getPeripheralName(char peripheralNum);

#endif
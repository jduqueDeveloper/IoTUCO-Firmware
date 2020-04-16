#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "time/time_control.h"

#define PINPUERTA D2 
#define PINCORTINA D3

extern const char* mqttServer;
extern const int mqttPort;
extern bool message_arrived;
extern PubSubClient client;
extern const char* mqttUser;
extern const char* mqttPassword;
extern String messageInTopic;
extern const char* topicIncome;

extern String DoorTopic;
extern String EnviromentTopic;
extern String controlInvernadero;
extern String controlZona;
extern String aliveTopic;

extern char DOOR_TOPIC [60];
extern char ENVIROMENT_TOPIC [60];
extern char CONTROL_GREENHOUSE [60];
extern char CONTROL_ZONE [60];
extern char ALIVE_TOPIC [60];

extern void mqtt_init();
extern void mqtt_conect();
extern void publishInTopic(const char* topic, const char* message);
extern void publishDataFormat(const char *topic, String message);
extern void jsonProcess(String topicMessage);
extern void buildTopicsNames();



#endif
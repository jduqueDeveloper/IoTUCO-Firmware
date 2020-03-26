#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>

#define InputTopic "input"
#define AliveTopic "alive"
#define GrowbedTopic "medicion/zona/x/invernadero/y/cama/z/ambiente"

extern const char* mqttServer;
extern const int mqttPort;
extern bool message_arrived;
extern PubSubClient client;
extern const char* mqttUser;
extern const char* mqttPassword;

extern void mqtt_init();
extern void mqtt_conect();
extern void publishInTopic(const char* topic, const char* message);
extern void publishDataFormat(String message);



#endif
#ifndef TIME_CONTROL_H
#define TIME_CONTROL_H


#include <NTPClient.h>
#include <WiFiUdp.h>
#include <mqtt/mqtt_service.h>
#include <DHT.h>

extern DHT dht;
extern int sec_Ant;
extern int sec_Act;

extern int DHTPIN;

extern int timeToNextRead();
extern bool IsTimeToRead(int sec_act);
extern String ReadSensor();
extern void publishDoor(String doorState);
extern void doorInterrupt(int state);
extern String deviceIdName();
extern String aliveMessage();

extern const int zone;
extern const int greenhouse;
extern String device_id;

extern const int sensorReadPeriod;

extern NTPClient timeClient;
#endif
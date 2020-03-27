#ifndef TIME_CONTROL_H
#define TIME_CONTROL_H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>

extern DHT dht;
extern int sec_Ant;
extern int sec_Act;

extern int DHTPIN;

extern int timeToNextRead();
extern bool IsTimeToRead(int sec_act);
extern String ReadSensor();

extern NTPClient timeClient;
#endif
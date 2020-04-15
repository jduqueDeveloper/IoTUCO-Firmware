#include "time_control.h"

int sec_Ant = 0;
int sec_Act = 0;
char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sábado"};
float humidity = 0.0;
float temperature = 0.0;

int timeToNextRead(){
    sec_Ant = timeClient.getSeconds() + sensorReadPeriod;

    if (sec_Ant >= 60)
    {
        sec_Ant = sec_Ant - 60; 
    }
    return sec_Ant;
}

bool IsTimeToRead(int sec_act){
    if(sec_act == sec_Ant){
        timeToNextRead();

        return true;
    }else{
        return false;
    }
}

String ReadSensor(){
  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

  String dataSensor;
  StaticJsonDocument<100> doc;
  doc["temperature"] = temperature;
  doc["zone"] = zone;
  doc["greenhouse"] = greenhouse;
  doc["hour"] = timeClient.getEpochTime();
  doc["device_id"] = device_id;
  serializeJson(doc, dataSensor);

  return dataSensor;    
}

void publishDoor(String doorState){
  String dataDoor;
  StaticJsonDocument<100> doc;
  doc["action"] = doorState;
  doc["zone"] = zone;
  doc["greenhouse"] = greenhouse;
  doc["hour"] = timeClient.getEpochTime();
  doc["device_id"] = device_id;
  serializeJson(doc, dataDoor);

  publishDataFormat(DOOR_TOPIC, dataDoor);
}

void doorInterrupt(int state){
  if(state == HIGH){
    publishDoor("Opened");
  }else{
    publishDoor("Closed");
  }
}

String deviceIdName(){
  String deviceName = (String)zone;
  deviceName += "_";
  deviceName += (String)greenhouse;

  return deviceName;
}

String aliveMessage(){
  String message;
  StaticJsonDocument<100> doc;
  doc["zone"] = zone;
  doc["greenhouse"] = greenhouse;
  doc["device_id"] = device_id;
  serializeJson(doc, message);

  return message;
}
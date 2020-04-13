#include "time_control.h"

int sec_Ant = 0;
int sec_Act = 0;
char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sábado"};
float humidity = 0.0;
float temperature = 0.0;

int timeToNextRead(){
    sec_Ant = timeClient.getSeconds() + 10;

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
    doc["temperatura"] = temperature;
    doc["humedad"] = humidity;
    doc["zona"] = zone;
    doc["invernadero"] = greenhouse;
    doc["cama"] = growbed;
    doc["hora"] = timeClient.getEpochTime();
    doc["device_id"] = device_id;
    serializeJson(doc, dataSensor);

    return dataSensor;
}

String deviceIdName(){
    String deviceName = (String)zone;
    deviceName += "_";
    deviceName += (String)greenhouse;
    deviceName += "_";
    deviceName += (String)growbed;

    return deviceName;
}

String aliveMessage(){
    String message;
    StaticJsonDocument<100> doc;
    doc["zona"] = zone;
    doc["invernadero"] = greenhouse;
    doc["cama"] = growbed;
    doc["device_id"] = device_id;
    serializeJson(doc, message);

    return message;
}
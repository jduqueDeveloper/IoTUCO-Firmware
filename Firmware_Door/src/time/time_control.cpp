#include "time_control.h"

int sec_Ant = 0;
int sec_Act = 0;
char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sábado"};
float humidity = 0.0;
float temperature = 0.0;

const int zona = 1;
const int invernadero = 1;

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

    String dataSensor = "{Temperatura: ";
    dataSensor += temperature;
    dataSensor += ", Zona: ";
    dataSensor += zona;
    dataSensor += ", Invernadero: ";
    dataSensor += invernadero;
    dataSensor += ", Hora: ";
    dataSensor += daysOfTheWeek[timeClient.getDay()];
    dataSensor += "/";
    dataSensor += timeClient.getFormattedTime();
    dataSensor += "}";

    return dataSensor;    
}

void publishDoor(String doorState){
    String dataDoor = "{accion: ";
    dataDoor += doorState;
    dataDoor += ", Zona: ";
    dataDoor += zona;
    dataDoor += ", Invernadero: ";
    dataDoor += invernadero;
    dataDoor += ", Hora: ";
    dataDoor += daysOfTheWeek[timeClient.getDay()];
    dataDoor += "/";
    dataDoor += timeClient.getFormattedTime();
    dataDoor += "}";

    publishDataFormat(DoorTopic, dataDoor);
}

void doorInterrupt(int state){
  if(state == HIGH){
    publishDoor("Abierto");
  }else{
    publishDoor("Cerrado");
  }
}

#include "mqtt_service.h"

bool message_arrived = false;
String messageInTopic = "";
const char* topicIncome = "";

enum peripheral
{
  luz,
  ventilador,
  puerta,
  cortinas
};


/********* MQTT Callback ***************************
   here is defined the logic to execute after
   a messages arrives in the desired
   topic, for this example the variable:
   InputTopic
************************************************/

void callback(char* topic, byte* payload, unsigned int length) {

  message_arrived = true;
  messageInTopic="";

  //Notify about message arrived 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  topicIncome=topic;

  for (int i = 0; i < length; i++) {
    messageInTopic += (char)payload[i];
  }
}

void mqtt_init(){
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
}


void mqtt_conect(){
  while (!client.connected()) {
    //Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
 
      Serial.println("Broker connected");
      client.subscribe(CONTROL_GREENHOUSE);
      client.subscribe(CONTROL_ZONE);
      publishDataFormat(ALIVE_TOPIC, aliveMessage()); 
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
}

void buildTopicsNames(){

  
//"medicion/zona/<zone>/invernadero/<greenhuose>/ingresos"
  DoorTopic = "medicion/zona/";
  DoorTopic += (String)zone;
  DoorTopic += "/invernadero/";
  DoorTopic += (String)greenhouse;
  DoorTopic += "/ingresos";
  DoorTopic.toCharArray(DOOR_TOPIC, 60);

//"medicion/zona/<zone>/invernadero/<greenhuose>/ambiente"
  EnviromentTopic = "medicion/zona/";
  EnviromentTopic += (String)zone;
  EnviromentTopic += "/invernadero/";
  EnviromentTopic += (String)greenhouse;
  EnviromentTopic += "/ambiente";
  EnviromentTopic.toCharArray(ENVIROMENT_TOPIC, 60);

//"control/zona/<zone>/invernadero/<greenhuose>"
  controlInvernadero = "control/zona/";
  controlInvernadero += (String)zone;
  controlInvernadero += "/invernadero/";
  controlInvernadero += (String)greenhouse;
  controlInvernadero.toCharArray(CONTROL_GREENHOUSE, 60);

//"control/zona/<zone>"
  controlZona = "control/zona/";
  controlZona += (String)zone;
  controlZona.toCharArray(CONTROL_ZONE, 60);
}

void publishInTopic(const char *topic, const char* message){

      if (client.state() < 0)
      {
      mqtt_conect();
      }

    client.publish(topic, message);
}

void publishDataFormat(const char *topic, String message){

      if (client.state() < 0)
      {
      mqtt_conect();
      }

    char data[100];
    message.toCharArray(data, 100);
    client.publish(topic, data);
    Serial.print("Published in: ");
    Serial.println(topic);
}

void jsonProcess(String topicMessage){
    StaticJsonDocument<94> doc;
    char messageChar[94];
    messageInTopic.toCharArray(messageChar, 94);
    deserializeJson(doc, messageChar);

    int periferico = doc["peripheral"];
    int valor = doc["value"];

    if(periferico == puerta){
      digitalWrite(PINPUERTA, valor);
    }else if(periferico == cortinas){
      digitalWrite(PINCORTINA, valor);
    }else{
      return;
    }

}


#include "mqtt_service.h"

bool message_arrived = false;


/********* MQTT Callback ***************************
   here is defined the logic to execute after
   a messages arrives in the desired
   topic, for this example the variable:
   InputTopic
************************************************/

void callback(char* topic, byte* payload, unsigned int length) {

  message_arrived = true;

  //Notify about message arrived 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  String timePetition = "";
  //urlTopic = url_api;
  for (int i = 0; i < length; i++) {
    timePetition += (char)payload[i];
    //urlTopic += (char)payload[i];
  }

  message_arrived = true;
}

void mqtt_init(){
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
}


void mqtt_conect(){
    while (!client.connected()) {
    //Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client")) {
 
      Serial.println("connected");
      //client.subscribe(InputTopic);
      publishInTopic(AliveTopic,"Alive"); 
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
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
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
   timePetition
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
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
 
      Serial.println("Broker connected");
      client.subscribe(controlCama);
      client.subscribe(controlInvernadero);
      client.subscribe(controlZona);
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

void publishDataFormat(String message){

    if (client.state() < 0)
    {
      mqtt_conect();
    }

    char data[100];
    message.toCharArray(data, 100);
    client.publish(GrowbedTopic, data);
    Serial.println("Output published");
}

void jsonProcess(String topicMessage){
    StaticJsonDocument<94> doc;
    char messageChar[94];
    messageInTopic.toCharArray(messageChar, 94);
    deserializeJson(doc, messageChar);

    char periferico = doc["Periferico"];
    char valor = doc["Valor"];

    String peripheralName = getPeripheralName(periferico);
    
    if(peripheralName == "luz"){
      digitalWrite(PINLUZ, valor);
    }else if(peripheralName == "ventilador"){
      digitalWrite(PINVENTILADOR, valor);
    }else{
      return;
    }

}

String getPeripheralName(char peripheralNum)
{

    switch (peripheralNum)
    {
    case luz:
        return "luz";
        break;
    case ventilador:
        return "ventilador";
        break;
    case puerta:
        return "puerta";
        break;
    case cortinas:
        return "cortinas";
        break;
    }
    return "";
}
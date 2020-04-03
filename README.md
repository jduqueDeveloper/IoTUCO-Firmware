# IoTUCO-Firmware

_Este es un proyecto de monitoreo y control en invernaderos de cultivos de flores basado en IoT. El micro-controlador empleado es  el NodeMCU v3 
que tiene un modulo wifi ESP8266 incorporado. En el diseño propuesto se tienen tres camas de flores por invernadero, para lo cual se emplea un 
NodeMCU por cada cama y otro adicional para la puerta.
Los micro-controladores de cada cama se encargan de medir la variables de temperatura y humedad en cada una de estas y publicar los valores en su 
respectivo tópico, así también deben estar suscritos a algunos tópicos donde recibirán un mensaje para controlar algunos periféricos. Ahora el 
micro-controlador de la puerta lee el valor de la temperatura del ambiente en el invernadero y de igual forma publica en el tópico y se suscribe a 
otros para manipular la cantonera ubicada en la puerta que permite el ingreso y maneja también las cortinas del invernadero en caso de que se tengan
que abrir o cerrar._

## Comenzando 🚀

_Se a creado un código diferente para los NodeMCU que serán ubicados en las camas(Firmware-Growbed) y los que serán ubicados en las puertas de los 
invernaderos(Firmware-Door), entonces se debe tener en cuenta que el código que se desea cargar al micro si corresponda con el de la cama(y cual cama es) 
o la puerta._

### Pre-requisitos 📋

_El entorno de desarrollo IDE que se utilizó es Platformio, en cuanto a estructura de código es igual que Arduino IDLE pero presta mejores servicios al 
momento de codificar.

A continuación se muestran las librerías utilizadas, se debe verificar que estén instaladas, sino se debe realizar su instalación para el correcto 
funcionamiento del código:_


```Arduino.h```    
```ESP8266WiFi.h```   
```PubSubClient.h```   
```ESP8266HTTPClient.h```  
```DHT.h```  
```ESP8266HTTPClient.h```   
```ArduinoJson.h```  
```NTPClient.h```  
```WiFiUdp.h```

### Configuración 🔧

_En el archivo __"main.cpp"__ de cada código se encuentran al inicio las credenciales necesarias para las conexiones wifi y mqtt, las cuales deben ser 
modificadas según la red LAN a la cual se valla a conectar el micro y también para la conexión al broker que se debe levantar previamente, ya sea de forma
 local o por medio de alguna plataforma en linea._

Para el manejo del broker MQTT se crean los tópicos en los archivos __"mqtt_service.h"__, por ejemplo un nombre de tópico que se podrá encontrar es 
"medicion/zona/x/invernadero/y/cama/z/ambiente", donde x,y & z deben ser reemplazados respectivamente por la zona, el invernadero y la cama a los cuales 
corresponde.
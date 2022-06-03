//Including all the required libraries
//DHT is used for collecting Temperature and Humidity data's
//Wifi is used to connect to wifi to establish a connection to our network for transmission of data
//ArduinoMqttClient these libraries are used for establishig a Mqtt connection in the web
#include "DHT.h"
#include "WiFi.h"
#include "ArduinoMqttClient.h"




//Defining the data pin where data should come 
//Defining the DHT sensor type
//Initiating the dht for reading data
#define DHTPIN 4
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);


//defining the Wifi name
//defining the password for the wifi
//defining the online mqtt broker(IP address) to which it should connect
#define ssid "DOTWORLD -JIO 2.4GHz" 
#define password "D0TW0RLD@2022"
#define server "test.mosquitto.org"


//defining the names for the topic to which it should subscribe and publish
//two topics Humidity for collecting room humidity and Temperature topic to collect Room temperature data
#define hum_topic "/humidity"
#define temp_topic "/temperature"

//defining the wifi
//defining the mqttclient
WiFiClient wifi;
MqttClient mqttClient(wifi);


const long interval = 8000;
unsigned long previousMillis = 0;

//int count = 0;

void setup() {

  Serial.begin(9600);
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(server);

  if (!mqttClient.connect(server, 1883)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  dht.begin();
}





void loop() {
  
// call poll() regularly to allow the library to send MQTT keep alive which
// avoids being disconnected by the broker
  mqttClient.poll();

//gives the current milliseconds 
  unsigned long currentMillis = millis();

//we are checking if the time exceeded more than 8 seconds if it exceeds we publish the data else we won't
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;


//reading the temperature and humidity data
    float Humidity = dht.readHumidity();
    float Temperature = dht.readTemperature();

//printing both the datas
    Serial.print("Sending message to topic humidity: ");
    Serial.println(hum_topic);
    Serial.println(Humidity);

    Serial.print("Sending message to topic Temperature: ");
    Serial.println(temp_topic);
    Serial.println(Temperature);

//publishing both the datas to the mqtt     
    mqttClient.beginMessage(hum_topic);
    mqttClient.print(Humidity);
    mqttClient.endMessage();

    mqttClient.beginMessage(temp_topic);
    mqttClient.print(Temperature);
    mqttClient.endMessage();

    Serial.println();
  }
}

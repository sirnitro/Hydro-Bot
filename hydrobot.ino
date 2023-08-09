//Code by Sir Nitro - 2023080802//
/* Water LVL */
#define H20_Power_Pin 7
#define H2O_Sensor_Pin A0
int waterLVL = 0;

/*Pump Relays*/
int p1Status = 0;
int p2Status = 0;
int p3Status = 0;
int p4Status = 0;

/*DHT*/
#include <dht.h>
dht DHT;
#define DHT22_PIN 7
float hum;  //Stores humidity value
float temp; //Stores temperature value
float tempF;

/*TDS*/
#include <EEPROM.h>
#include "GravityTDS.h"
#define TdsSensorPin A1
GravityTDS gravityTds;
float temperature = 25,tdsValue = 0;

void setup() {

/*Water LVL*/
        Serial.begin(9600);
        while (!Serial);
        pinMode(H20_Power_Pin, OUTPUT);
        digitalWrite(H20_Power_Pin, LOW);

/*TDS*/
        gravityTds.setPin(TdsSensorPin);
        gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
        gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
        gravityTds.begin();  //initialization
}

void loop() {

/*Water LVL*/
   digitalWrite(H20_Power_Pin, HIGH);  // turn the sensor ON
   delay(10);                      // wait 10 milliseconds
   waterLVL = analogRead(H2O_Sensor_Pin); // read the analog value from sensor
   digitalWrite(H20_Power_Pin, LOW);   // turn the sensor OFF
   Serial.print(waterLVL);
/*DHT*/
   int chk = DHT.read22(DHT22_PIN);
   hum = DHT.humidity;
   temp = DHT.temperature;
   tempF = ((int)round(1.8*temp+32));
   Serial.print("**");
   Serial.print(hum);
   Serial.print("**");
   Serial.print(tempF);
/*TDS*/
   gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
   gravityTds.update();  //sample and calculate
   tdsValue = gravityTds.getTdsValue();  // then get the value
   Serial.print("**");
   Serial.print(tdsValue,0);
   Serial.print("**");
/*Dweet*/
      String posturl = "/usr/bin/curl -k \"https://dweet.io:443/dweet/for/CHANGEME?water_level=";
      posturl.concat(waterLVL);
      posturl.concat("&Temp=");
      posturl.concat(tempF);
      posturl.concat("&Humidity=");
      posturl.concat(hum);
      posturl.concat("&TDS=");
      posturl.concat(tdsValue);
      posturl.concat("&p1=");
      posturl.concat(p1Status);
      posturl.concat("&p2=");
      posturl.concat(p2Status);
      posturl.concat("&p3=");
      posturl.concat(p3Status);
      posturl.concat("&p4=");
      posturl.concat(p4Status);
      posturl.concat("\"");

  Serial.print(posturl);

      delay(30000);
}

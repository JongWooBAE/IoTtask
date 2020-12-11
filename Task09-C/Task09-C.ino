#include <AWS_IOT.h>
#include <WiFi.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C
AWS_IOT hornbill;
const char* ssid = "Monica";
const char* password = "Monica5741";
char HOST_ADDRESS[]="a1ydyc938z7k9e-ats.iot.ap-northeast-2.amazonaws.com";
char CLIENT_ID[]= "ChoiESP32";
char sTOPIC_NAME[]= "ESP32/LED";  // subscribe topic name // publish topic name
char pTOPIC_NAME[]= "ESP32/BME280"; 
int status = WL_IDLE_STATUS;
int msgCount=0,msgReceived = 0;
char payload[512];
char rcvdPayload[512];
const int buttonPin = 15; // pushbutton pin
unsigned long preMil = 0;
const long intMil = 5000; 
const int ledPin = 17; 

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
  strncpy(rcvdPayload,payLoad,payloadLen);
  rcvdPayload[payloadLen] = 0;
  msgReceived = 1;
}

void setup() {
  Serial.begin(115200);
  bme.begin(0x76);
//++choi This is here to force the ESP32 to reset the WiFi and initialise correctly.
  Serial.print("WIFI status = ");
  Serial.println(WiFi.getMode());
  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  delay(1000);
  Serial.print("WIFI status = ");
  Serial.println(WiFi.getMode()); //++choi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to wifi");
  if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0) {
    Serial.println("Connected to AWS");
    delay(1000);
    if(0==hornbill.subscribe(sTOPIC_NAME,mySubCallBackHandler)) {
      Serial.println("Subscribe Successfull");
    }
    else {
      Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
      while(1);
    }
    }
  else {
    Serial.println("AWS connection failed, Check the HOST Address");
    while(1);
  }
// initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  pinMode(ledPin,OUTPUT);
  delay(2000);
}


void loop() {

if(msgReceived == 1)
{
msgReceived = 0;
Serial.print("Received Message:");
Serial.println(rcvdPayload);
// Parse JSON
JSONVar myObj = JSON.parse(rcvdPayload);
JSONVar state = myObj["state"];
String led = (const char*) state["led"];
Serial.print("LED will be ");
Serial.println(led);
if (led == "ON")
digitalWrite(ledPin, HIGH);
else if (led == "OFF")
digitalWrite(ledPin, LOW);
}

if((millis()-preMil) > intMil) {
  // read the state of the pushbutton value
  if (digitalRead(buttonPin)) {
    Serial.println("btn pressed");
    int temp = bme.readTemperature();
    int humid = bme.readHumidity();
 
    preMil = millis();
    sprintf(payload,"{\"temp\": %d,\"humid\":%d}",temp,humid);
    //sprintf(payload,"ESP32-Button:001 Pressed!!");
  if(hornbill.publish(pTOPIC_NAME,payload) == 0) {
    Serial.print("Publish Message:");
    Serial.println(payload);
  }
  else
    Serial.println("Publish failed");
  }
}


}

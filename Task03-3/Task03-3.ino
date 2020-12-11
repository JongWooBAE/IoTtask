//ESP32 Touch Test
//Just test touch pin - TouchO is TO which is on GPIO 4.
void setup(){
  Serial.begin(115200);
  delay(1000); //give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop(){
  Serial.println(touchRead(4)); //get value of Touch O pin = GPIO4
  delay(1000);
}

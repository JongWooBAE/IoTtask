#define timeSeconds 3

const int led = 16;
const int motionSensor = 36;

unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

void IRAM_ATTR detectsMovement(){
  Serial.println("MOTION DETECTED!!");
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void setup(){
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
}

void loop(){
  now = millis();
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))){
    Serial.println("Motion stopped...");
    digitalWrite(led,LOW);
    startTimer = false;
  }
}

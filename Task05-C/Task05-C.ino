#define timeSeconds 20

const int ledPin0 = 18;
const int ledPin1 = 17;
const int ledPin2 = 16;
const int motionSensor = 36;
int num = 0;

unsigned long now = millis();
unsigned long lastTrigger0 = 0;
unsigned long lastTrigger1 = 0;
unsigned long lastTrigger2 = 0;
boolean startTimer0 = false;
boolean startTimer1 = false;
boolean startTimer2 = false;

void IRAM_ATTR detectsMovement(){
  if(num%3==0){
    Serial.println("MOTION DETECTED!!(0)");
    digitalWrite(ledPin0, HIGH);
    startTimer0 = true;
    lastTrigger0 = millis();
  }
  if(num%3==1){
    Serial.println("MOTION DETECTED!!(1)");
    digitalWrite(ledPin1, HIGH);
    startTimer1 = true;
    lastTrigger1 = millis();
  }
  if(num%3==2){
    Serial.println("MOTION DETECTED!!(2)");
    digitalWrite(ledPin2, HIGH);
    startTimer2 = true;
    lastTrigger2 = millis();
  }
  num += 1;
}
void setup(){
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin0, OUTPUT);
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin0,LOW);
}

void loop(){
  now = millis();
  if(startTimer0 && (now - lastTrigger0 > (timeSeconds*1000))){
    Serial.println("Motion stopped...(0)");
    digitalWrite(ledPin0, LOW);
    startTimer0 = false;
  }
  if(startTimer1 && (now - lastTrigger1 > (timeSeconds*1000))){
    Serial.println("Motion stopped...(1)");
    digitalWrite(ledPin1, LOW);
    startTimer1 = false;
  }
  if(startTimer2 && (now - lastTrigger2 > (timeSeconds*1000))){
    Serial.println("Motion stopped...(2)");
    digitalWrite(ledPin2, LOW);
    startTimer2 = false;
  }
}

//set pin numbers
const int touchPin = 4;
const int ledPin = 16;
const int buttonPin = 15;
//change with your threshold value
const int threshold = 20;
//variable for storing the touch pin value
int touchValue;
int buttonState = 0;

void setup(){
  Serial.begin(115200);
  delay(1000);  //time to bring up serial monitor
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  //read the touch value
  touchValue = touchRead(touchPin);
  //check if the touchValue below the threshold
  //if it is, set ledPin to HIGH
  if(touchValue>=threshold and buttonState == LOW){
    //turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println("LED off");
  }
  else{
    //turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println("LED on");
  }
}

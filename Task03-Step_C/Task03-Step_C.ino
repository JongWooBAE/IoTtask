const int buttonPin = 15;
int buttonState = 0;
char serState = NULL;
int state=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Test");
  pinMode(buttonPin,INPUT);
  //pinMode(ledPin,OUTPUT);
  
}

void loop() {

  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    delay(500);
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      state = state + 1;
      Serial.println("change status");
    }
  }
  
  

  
  
  if(state%2 == 1){
    Serial.println("HI");
    delay(500);
  }

}

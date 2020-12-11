const int trigPin = 22;
const int echoPin = 23;
const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 19;
const int duty = 128;

void playNote(int note, int dur) {
  ledcSetup(ledChannel, note, resolution);
  ledcWrite(ledChannel, duty);
  
  Serial.println(note);
  delay(dur);
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ledcAttachPin(buzPin, ledChannel);
}

void loop() {
  long duration, distance;

  //Triggering by 10us pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //getting duration for echo pulse
  duration = pulseIn(echoPin, HIGH);

  //sound speed = 340 m/s = 34/1000 cm/us
  //distance = duration*34/1000*1/2
  distance = duration*17/1000;

  playNote(4000-(distance*100), 250);
  
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

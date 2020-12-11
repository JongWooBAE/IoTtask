//make tones by using pwm
// freq -> pitch
// duty -> volume(?)

//setting PWM properties
//const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 23;
const int duty = 128;

#define C 262 //도
#define D 294 //레
#define E 330 //미
#define G 392 //솔
#define CC 523 //높은도


//variables
int sVal;
int a = 125;
int b = 250;
int c = 1000;
//notes
//enum Notes{C3=0, CS3, D3, DS3, E3, F3};
int nFrq[] = {/*131,139,147,156,165,175*/262, 277, 294, 311, 330, 349};
int dur[49] = {b, a, a, b, b, b, a, a, b, b,  a, a, b, a, a, b,  b, b, b, b,
               b, b, b, b,   b, b, b, b,    b, b, b, b,      b, b, b, b,
               b, b, b, b,   c,          b, b, b, b,      b, b, b, b
              };
int note[49] = {C, C, C, C, C,  E, G, G, E, C,  G, G, E, G, G, E,  C, C, C, '.',
                G, G, E, C,    G, G, G, '.',    G, G, E, C,      G, G, G, '.',
                G, G, E, C,    '.',          CC, G, CC, G,    E, D, C, '.'
               };

void playNote(int note, int dur) {
  ledcSetup(ledChannel, note, resolution);
  ledcWrite(ledChannel, duty);
  
  Serial.println(note);
  delay(dur);
}

void setup() {
  Serial.begin(115200);
  ledcAttachPin(buzPin, ledChannel);
}

void loop() {
  for (int i = 0; i <= 48; i++) {
    playNote(note[i], dur[i]);
  }

}

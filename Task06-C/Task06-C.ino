// music play station by using pwm
// freq -> pitch
// duty -> volume (?)
// setting PWM properties

#include <EEPROM.h>
#define EEPROM_SIZE 1000
// 아마 다 바꿀듯
int pairNum = 0;  // EEPROM에 저장된 페어 개수
int saveNum = 3;  // EEPROM에 저장하기 위한 정수(3부터 저장이라서)
int ex;
bool saveState = false;   //저장 해야하는지 아닌지 판단하는 bool값 True면 저장o
/*const int buttonPin = 15; // the number of the pushbutton pin
const int ledPin = 16; // the number of the LED pin
// Variables will change:
int ledState = HIGH; // the current state of the output pin
int buttonState; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers
*/

const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 23;
const int duty = 128;
// variables
int vNote=0, vDur=0;
const int dDur = 250; // default duration
// notes
//enum Notes {C3=0, CS3, D3, DS3, E3, F3};
int nFrq[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523};
int nDur[] = { 2000, 1500, 1000, 750, 500, 375, 250 };


void playNote(int note, int dur) {
  if (note == -1) {
    ledcSetup(ledChannel, 0, resolution);
    ledcWrite(ledChannel, 0);
  }
  else {
    ledcSetup(ledChannel, nFrq[note], resolution);
    ledcWrite(ledChannel, duty);
  }
  Serial.println(String(note)+","+String(dur));
    delay(nDur[dur]);
}


void setup() {
  Serial.begin(115200);

// initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);
  
// attach the channel to the GPIOs
  ledcAttachPin(buzPin, ledChannel);

  

  if(EEPROM.read(0) == 0xBB and EEPROM.read(1) == 0x55){
    Serial.println("hi");
    Serial.println();
    for(int i = 3; i<(EEPROM.read(2)*2+3); i+=2){
      Serial.print(EEPROM.read(i));
      Serial.print(",,");
      Serial.println(EEPROM.read(i+1));
    }
    for(int i = 3 ; i<(EEPROM.read(2)*2+3) ; i+=2){
      vNote = EEPROM.read(i);
      vDur = EEPROM.read(i+1);
      if(vNote == 255){
        vNote = -1;
      }
      playNote(vNote, vDur);
    }
  }

}

void loop(){
  if (Serial.available() > 0) {
    ex = Serial.read();
    if(ex == '<'){
      saveState = true;
      EEPROM.write(0, 0xBB);
      EEPROM.write(1, 0x55);
      vNote = Serial.read();  
    }
    else if(ex == '>'){
      saveState = false;
      EEPROM.write(2, pairNum);
      EEPROM.commit();
      Serial.println();
      for(int i = 3; i<(pairNum*2+3); i+=2){
        Serial.print(EEPROM.read(i));
        Serial.print("   ");
        Serial.println(EEPROM.read(i+1));
      }
      vNote = Serial.read();
    }
    else{
      vNote = ex;
    }
    
    if (Serial.available() > 0) {
        vDur = Serial.read();
      if (vDur <= '6' && vDur >= '0')
        vDur -= '0';
      else vDur = dDur;
      if (vNote <= '9' && vNote >= '0')
        vNote -= '0';
      else if (vNote <= 'c' && vNote >= 'a')
        vNote = vNote - 'a' + 10;
      else /* if (vNote == ',') */
        vNote = -1; // rest
      if(saveState == true){
        EEPROM.write(saveNum, vNote);
        EEPROM.write(saveNum+1, vDur);
        saveNum += 2;
        pairNum += 1;
      }
      playNote(vNote, vDur);
    }
  }
}

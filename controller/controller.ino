#include <HID-Project.h>
#include <HID-Settings.h>
#include <Keypad.h>

#define ENABLE_PULLUPS

const byte ROWS = 2;
const byte COLS = 2;

byte keys[ROWS][COLS] = {
  {1,2},
  {3,4},
};

byte rowPins[ROWS] = {3,2};
byte colPins[COLS] = {A4,A5};

const int ignitionTogglePin = 13;
const int lowLightsTogglePin = 12;
const int highLightsTogglePin = 11;
const int wipersTogglePin = 10;
const int parkingBrakeTogglePin = 9;

const int ignitionToggleGamepadKey = 15;
const int highLightsToggleGamepadKey = 16;
const int lowLightsToggleGamepadKey = 17;
const int wipersToggleGamepadKey = 18;
const int parkingBrakeToggleGamepadKey = 19;

int previousIgnitionToggleState = 0;
int previousHighLightsToggleState = 0;
int previousLowLightsToggleState = 0;
int previousWipersToggleState = 0;
int previousParkingBrakeToggleState = 0;

Keypad kpd = Keypad ( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(ignitionTogglePin, INPUT_PULLUP);
  pinMode(highLightsTogglePin, INPUT_PULLUP);
  pinMode(lowLightsTogglePin, INPUT_PULLUP);
  pinMode(wipersTogglePin, INPUT_PULLUP);
  pinMode(parkingBrakeTogglePin, INPUT_PULLUP);

  Serial.begin(9600);
  Gamepad.begin();
}

void loop() {
   Gamepad.release(ignitionToggleGamepadKey);
   Gamepad.release(highLightsToggleGamepadKey);
   Gamepad.release(lowLightsToggleGamepadKey);
   Gamepad.release(wipersToggleGamepadKey);
   Gamepad.release(parkingBrakeToggleGamepadKey);

   Gamepad.write();
    
  // put your main code here, to run repeatedly:
  if(kpd.getKeys()){
    for (int i = 0; i<LIST_MAX; i++){
           if ( kpd.key[i].stateChanged ){
            switch(kpd.key[i].kstate){
              case PRESSED: {
                Gamepad.press(kpd.key[i].kchar);
                Gamepad.write();
                break;
              }
              case RELEASED: {
                Gamepad.release(kpd.key[i].kchar);
                Gamepad.write();
                break;
              }
            }
      } 
    }
  }
  
  int ignitionToggleState = digitalRead(ignitionTogglePin);
  if(ignitionToggleState != previousIgnitionToggleState){
    Serial.println("Ignition state changed");
    Gamepad.press(ignitionToggleGamepadKey);
    Gamepad.write();
  }
  
  int highLightsToggleState = digitalRead(highLightsTogglePin);
  if(highLightsToggleState == LOW && highLightsToggleState != previousHighLightsToggleState){
    Serial.println("High lights state changed");
    Gamepad.press(highLightsToggleGamepadKey);
    Gamepad.write();
  }

  int lowLightsToggleState = digitalRead(lowLightsTogglePin);
  if(lowLightsToggleState == LOW && lowLightsToggleState != previousLowLightsToggleState){
    Serial.println("Low lights state changed");
    Gamepad.press(lowLightsToggleGamepadKey);
    Gamepad.write();
  }
  
  int wipersToggleState = digitalRead(wipersTogglePin);
  if(wipersToggleState != previousWipersToggleState){
    Serial.println("Wipers state changed");
    Gamepad.press(wipersToggleGamepadKey);
    Gamepad.write();
  }

  int parkingBrakeToggleState = digitalRead(parkingBrakeTogglePin);
  if(parkingBrakeToggleState != previousParkingBrakeToggleState){
    Serial.println("Parking Brake state changed");
    Gamepad.press(parkingBrakeToggleGamepadKey);
    Gamepad.write();
  }

  previousIgnitionToggleState = ignitionToggleState;
  previousHighLightsToggleState = highLightsToggleState;
  previousLowLightsToggleState = lowLightsToggleState;
  previousWipersToggleState = wipersToggleState;
  previousParkingBrakeToggleState = parkingBrakeToggleState;

  delay(100);
}

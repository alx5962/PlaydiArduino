/*
  Playdia remote
  
  The circuit:
  - 6 pushbuttons attached to +5V with a 10k ohms resistor
  - 200 ohms resistor attached to infrared led pin 2 

  Arduino Code by alx5962, using header code by Armin Joachimsmeyer.
*/

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

uint8_t sRepeats = 0;
uint64_t msRepeatPeriod = 100;

const int buttonLeftPin = 6;
const int buttonUpPin = 7;
const int buttonRightPin = 8;
const int buttonDownPin = 9;
const int buttonAPin = 10;
const int buttonBPin = 11;

int buttonStateUp = 0; 
int buttonStateDown = 0;
int buttonStateLeft = 0;
int buttonStateRight = 0;
int buttonStateA = 0;
int buttonStateB = 0;

void setup() {
    Serial.begin(115200);

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.println(F("Ready to receive IR signals at pin " STR(IR_RECEIVE_PIN)));
    Serial.print(F("Ready to send IR signals at pin "));    
    Serial.println(IR_SEND_PIN);

    pinMode(buttonUpPin, INPUT);
    pinMode(buttonDownPin, INPUT);
    pinMode(buttonLeftPin, INPUT);
    pinMode(buttonRightPin, INPUT);
    pinMode(buttonAPin, INPUT);
    pinMode(buttonBPin, INPUT);

}

void loop() {
  buttonStateUp = digitalRead(buttonUpPin);
  buttonStateDown = digitalRead(buttonDownPin);
  buttonStateLeft = digitalRead(buttonLeftPin);
  buttonStateRight = digitalRead(buttonRightPin);
  buttonStateA = digitalRead(buttonAPin);
  buttonStateB = digitalRead(buttonBPin);
 
  if (buttonStateUp == HIGH) {
    Serial.println("btn up pressed ! ");  
    uint32_t tRawDataU[]={0x95C};
    IrSender.sendPulseDistanceWidthFromArray(38, 500, 900, 300, 2050, 300, 850, &tRawDataU[0], 12, PROTOCOL_IS_LSB_FIRST, msRepeatPeriod, sRepeats);          
  } else if (buttonStateDown == HIGH) {
    Serial.println("btn down pressed ! ");  
    uint32_t tRawDataD[]={0x93A};
    IrSender.sendPulseDistanceWidthFromArray(38, 550, 900, 300, 2000, 300, 850, &tRawDataD[0], 12, PROTOCOL_IS_LSB_FIRST, msRepeatPeriod, sRepeats);       
  } else if (buttonStateLeft == HIGH) {
    Serial.println("btn left pressed ! ");  
    uint32_t tRawDataL[]={0xB6D};
    IrSender.sendPulseDistanceWidthFromArray(38, 550, 850, 300, 2000, 300, 850, &tRawDataL[0], 12, PROTOCOL_IS_LSB_FIRST, msRepeatPeriod, sRepeats);       
  } else if (buttonStateRight == HIGH) {
    Serial.println("btn right pressed ! ");
    uint32_t tRawDataR[]={0xF4B};
    IrSender.sendPulseDistanceWidthFromArray(38, 550, 900, 250, 2050, 250, 850, &tRawDataR[0], 12, PROTOCOL_IS_LSB_FIRST, msRepeatPeriod, sRepeats);         
  } else if (buttonStateA == HIGH) {
    Serial.println("btn A pressed ! ");  
    uint32_t tRawDataA[]={0x78F};
    IrSender.sendPulseDistanceWidthFromArray(38, 500, 900, 250, 2050, 250, 900, &tRawDataA[0], 12, PROTOCOL_IS_LSB_FIRST, msRepeatPeriod, sRepeats);
  } else if (buttonStateB == HIGH) {
    Serial.println("btn B pressed ! "); 
    uint32_t tRawDataB[]={0x97E};
    IrSender.sendPulseDistanceWidthFromArray(38, 500, 950, 250, 2050, 250, 850, &tRawDataB[0], 12, PROTOCOL_IS_LSB_FIRST, msRepeatPeriod, sRepeats); 
  }

  delay(100);
}

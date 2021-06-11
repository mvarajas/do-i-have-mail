//modified from the Mail_Scale_Calibrator_Sparkfun file

#include "HX711.h"
#define DOUT 3
#define CLK 2

HX711 scale;

float calibration_factor = -12200;  //This is the calibration factor for a 100g load cell. ensures most accurate readings


void setup() {
  Serial.begin(9600);         //The serial lines were just used to see what the scale was reading.
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  scale.set_scale(calibration_factor);            //The scale is set to the calibration factor

  float current_weight = (-1) *scale.get_units(30);   //Take 30 readings to ensure that an accurate weight is found at that moment
  Serial.print(current_weight);
  Serial.print(" g");
  Serial.println();

  if(current_weight > 2){             //If the weight that is on the scale is above 2 grams, the light will turn on, letting the user know there is mail in the mailbox
                                      //2 grams was chosen as the threshold because a postcard (lightest thing that would be put in a mailbox)is 4.5 grams 
                                      //2 grams is high enough that it avoids any noise or discrepencies when the scale is zeroed out.
    digitalWrite(LED_BUILTIN, HIGH);
  }else 
    digitalWrite(LED_BUILTIN, LOW); //LED is off when no weight is place on scale
}

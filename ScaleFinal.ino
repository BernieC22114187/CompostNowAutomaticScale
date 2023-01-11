#include <Keyboard.h>
#include "Arduino.h"
#include "HX711.h"

// Pin Definitions
#define SCALE_1_PIN_DAT	3
#define SCALE_1_PIN_CLK	2
#define SCALE_2_PIN_DAT	5
#define SCALE_2_PIN_CLK	4
#define SCALE_3_PIN_DAT	7
#define SCALE_3_PIN_CLK	6
#define SCALE_4_PIN_DAT	9
#define SCALE_4_PIN_CLK	8

#define calibration_factor -0.000248

String input;

HX711 scale1; HX711 scale2; HX711 scale3; HX711 scale4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Test");
  scale1.begin(SCALE_1_PIN_DAT, SCALE_1_PIN_CLK); scale2.begin(SCALE_2_PIN_DAT, SCALE_2_PIN_CLK); 
  scale3.begin(SCALE_3_PIN_DAT, SCALE_3_PIN_CLK); scale4.begin(SCALE_4_PIN_DAT, SCALE_4_PIN_CLK);
  
  scale1.set_scale(); scale2.set_scale(); scale3.set_scale(); scale4.set_scale();
  scale1.tare(); scale2.tare(); scale3.tare(); scale4.tare(); 
  Serial.println("Tare done...");
  Keyboard.begin();
}

void loop() {
  delay(1000);
  if (scale1.is_ready() && scale2.is_ready() && scale3.is_ready() && scale4.is_ready() ) {
    
    Serial.println("Place a weight on the scale...");
    delay(1000);
    double reading = scale1.get_units(10) + scale2.get_units(10) + scale3.get_units(10) + scale4.get_units(10);
    // average of 10 readings per load cell
    reading = reading / 4;
    reading = reading * calibration_factor;
    reading = reading + 0.073;
    Serial.print("Reading: ");
    Serial.print(reading); //scale.get_units() returns a float
    Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
    if(reading >= 1){
      
      String input = String(reading);
      
      for(int i = 0; i < input.length(); i++){
          int temp = (int) ( (char)input[i] );
          Keyboard.write(temp);
      }
    }
    
  } 
  else {
    Serial.println("HX711 not found.");
  }
}


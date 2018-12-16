/*

  Flopper ESP32 / Led
  
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT

*/
#include <analogWrite.h>

///////////////////////////////////////////////////////////////////


void setup_led() {
  analogWriteResolution(PIN_LED_R, 12);
  analogWriteResolution(PIN_LED_G, 12);
  analogWriteResolution(PIN_LED_B, 12);

}

void loop_led(void * parameter ) {

  analogWrite(PIN_LED_R, 6);
  analogWrite(PIN_LED_G, 10);
  analogWrite(PIN_LED_B, 10);

// digitalWrite(PIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
 // digitalWrite(PIN_LED, LOW);    // turn the LED off by making the voltage LOW
  analogWrite(PIN_LED_R, 0);
  analogWrite(PIN_LED_G, 0);
  analogWrite(PIN_LED_B, 0);

   delay(1000);
  loop_led(NULL);
}

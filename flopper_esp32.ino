/*

  Flopify ESP32
  
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT

*/

String current_floppy_uid = "";
String current_floppy_url = "https://soundcloud.com/trippie-hippie-2/1400999-freestyle-ft-juice-wrld";

String url_to_rec = "";

uint8_t PIN_LED_R = 14; 
uint8_t PIN_LED_G = 27; 
uint8_t PIN_LED_B = 26; 

uint8_t PIN_SPI_SS = 5; 

uint8_t PIN_TOUCH_PREV = T3; // 15 = T3
uint8_t PIN_TOUCH_NEXT = T2; // 2 = T2
uint8_t PIN_TOUCH_RANDOM = T0; // 32 = T9
uint8_t PIN_TOUCH_PAUSE = T8;  // 4 = T0

uint8_t PIN_TOUCH_REC = T4;  // 13 = T4
uint8_t PIN_TOUCH_LIKE = T5; // 12 = T5



uint8_t PIN_POT_OUT = 25; 
uint8_t PIN_POT_IN = 36; 




////////////////////////////////////////////////////////////////

void setup() {



  
  delay(1000);
  Serial.begin(115200);

  Serial.println();
  Serial.println("Flopify boot!");

  setup_pot();

  setup_nfc();
  
//  setup_network();

  setup_touch();
 
  setup_led();

// xTaskCreate(
//                    loop_network,          /* Task function. */
//                    "Network",        /* String with name of task. */
//                    10000,            /* Stack size in words. */
//                    NULL,             /* Parameter passed as input of the task */
//                    1,                /* Priority of the task. */
//                    NULL);            /* Task handle. */
 
  xTaskCreate(
                   loop_nfc,          /* Task function. */
                    "NFC",        /* String with name of task. */
                    30000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 
 xTaskCreate(
                    loop_led,          /* Task function. */
                    "LED",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 
 
 xTaskCreate(
                    loop_touch,          /* Task function. */
                    "TOUCH",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */


  
 xTaskCreate(
                    loop_pot,          /* Task function. */
                    "POT",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 

}

////////////////////////////////////////////////////////////////

void loop() {



  
 
}

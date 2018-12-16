/*

  Flopify ESP32 / NFC
  
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT

*/
////////////////////////////////////////////////////////////////


#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, PIN_SPI_SS);
NfcAdapter nfc = NfcAdapter(pn532spi);

////////////////////////////////////////////////////////////////

void setup_nfc(){

  nfc.begin();

}

void loop_nfc(void * parameter ){

    // https://forums.adafruit.com/viewtopic.php?f=31&t=58903&start=15

    if(url_to_rec==""){
    readNDEF();  
    }
  
/*
    Serial.print("URL:");
    Serial.println(current_floppy_url);

   Serial.print("UID:");
    Serial.println(current_floppy_uid);
*/

    delay(100);
    loop_nfc(NULL);

}

////////////////////////////////////////////////////////////////


void nfcSaveUrl(){

      Serial.println("nfcSaveUrl!");

  if(url_to_rec!=""){
      writeNDEF(url_to_rec);
      url_to_rec = "";
    } else {
      Serial.println("nothing to rec!");
      // httpShowRecPage();  
    }
}

void writeNDEF(String url){

    bool success = false;

    Serial.println("REC: Insert floppy to reader!");
    //if (nfc.tagPresent()) {

      Serial.println("REC: Floppy inserted!");

      NfcTag tag = nfc.read();
      if (tag.hasNdefMessage()){
          Serial.println("REC: Floppy is already NDEF formatted, overwriting!");
          success = true;
      } else {
          Serial.println("REC: Floppy is formatted to NDEF!");
          success = nfc.format();
          if(!success){
            Serial.println("REC: Floppy format failed!");
          }
      }
       
      if (success) {
          
          NdefMessage message = NdefMessage();
          message.addUriRecord(url);
  
          success = nfc.write(message);
          if (success) {
            Serial.println("REC: Floppy write success!");        
          } else {
            Serial.println("REC: Floppy write failed!");
          }
      }
       
   // } else {
     // delay(3000);
     // writeNDEF(url);
   // }
    
}

////////////////////////////////////////////////////////////////

void readNDEF(){

  Serial.println("\nScan a NFC tag\n");

  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    Serial.println(tag.getTagType());
    Serial.print("UID: ");
    Serial.println(tag.getUidString());

    if(current_floppy_uid==tag.getUidString()){
      return;
    }
    
    current_floppy_uid = tag.getUidString();

    if (tag.hasNdefMessage()) // every tag won't have a message
    {

      NdefMessage message = tag.getNdefMessage();
      Serial.print("\nThis NFC Tag contains an NDEF Message with ");
      Serial.print(message.getRecordCount());
      Serial.print(" NDEF Record");
      if (message.getRecordCount() != 1) {
        Serial.print("s");
      }
      Serial.println(".");

      // cycle through the records, printing some info from each
      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++)
      {
        Serial.print("\nNDEF Record ");Serial.println(i+1);
        NdefRecord record = message.getRecord(i);
        // NdefRecord record = message[i]; // alternate syntax

        Serial.print("  TNF: ");Serial.println(record.getTnf());
        Serial.print("  Type: ");Serial.println(record.getType()); // will be "" for TNF_EMPTY

        // The TNF and Type should be used to determine how your application processes the payload
        // There's no generic processing for the payload, it's returned as a byte[]
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);

        // Print the Hex and Printable Characters
        Serial.print("  Payload (HEX): ");
        PrintHexChar(payload, payloadLength);

        // Force the data into a String (might work depending on the content)
        // Real code should use smarter processing
        String payloadAsString = "";
        for (int c = 0; c < payloadLength; c++) {
          payloadAsString += (char)payload[c];
        }

     
        
        Serial.print("  Payload (as String): ");
        Serial.println(payloadAsString);
        Serial.println(payloadAsString.length());

        if(payloadAsString.length()>10){

           current_floppy_url = "";
          for (int c = 0; c < payloadLength; c++) {
            current_floppy_url += (char)payload[c];
          }
          
        } else {
          current_floppy_url = "";
   
        }
    
         

        // id is probably blank and will return ""
        String uid = record.getId();
        if (uid != "") {
          Serial.print("  ID: ");Serial.println(uid);
        }
      }
    }
      delay(1000);
  }

  
}

////////////////////////////////////////////////////////////////

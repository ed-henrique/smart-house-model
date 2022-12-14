#include <SPI.h>
#include <MFRC522.h>

#define LED D1
#define SS_PIN D8
#define RST_PIN D0

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

void setup() {
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
}

void loop() {

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("The NUID tag is: "));
  String id = getId(rfid.uid.uidByte, rfid.uid.size);
  Serial.println(id);
  Serial.println();
  
  checkId(id);

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

String getId(byte *buffer, byte bufferSize) {
  String id = "";

  for (byte i = 0; i < bufferSize; i++) {
    id.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    id.concat(String(buffer[i], HEX));
  }

  id.toUpperCase();
  
  return id;
}

void checkId(String id) {
  if (id.substring(1) == "45 D4 D4 35") {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
  }
}
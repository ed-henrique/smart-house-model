#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>

int pos = 0;
Servo portao;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  portao.attach(6);
}

void loop(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;
  
  String conteudo= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  conteudo.toUpperCase();

  if (conteudo.substring(1) == "15 5B 0E 88") {
    Serial.println("Acesso liberado!");
    openGarage();
  }
}

void openGarage() {
  for (pos = 0; pos < 180; pos++) {
    portao.write(pos);
    delay(15);
  }

  delay(5000);

  for (pos = 180; pos > 0; pos--) {
    portao.write(pos);
    delay(15);
  }
}

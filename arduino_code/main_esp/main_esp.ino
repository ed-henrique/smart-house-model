/*
Este código contém a implementação da parte do RFID na sala de estar, usando o ESP8266 DevKit v2.
Esta, por sua vez, é composta por um leitor RFID e um LED, simulando assim uma autenticação para
liga o LED (representando a abertura de uma porta).

Este modulo foi designado para Rosialdo Vicente, que o implementou.
*/

#include <SPI.h>
#include <MFRC522.h>

#define LED D1
#define SS_PIN D8
#define RST_PIN D0

MFRC522 leitor_rfid(SS_PIN, RST_PIN);

void setup() {
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  leitor_rfid.PCD_Init();
}

void loop() {
    if (!leitor_rfid.PICC_IsNewCardPresent()) return;
    if (!leitor_rfid.PICC_ReadCardSerial()) return;

    String id = lerUID();
    bool idEstaCorreto = verificarId(id);

    Serial.print("[SALA DE ESTAR] A tag tentada foi: ");
    Serial.println(id);
    Serial.println();

    if (idEstaCorreto) {
        Serial.println("[SALA DE ESTAR] Porta foi aberta!");
        piscarLED();
    }
}

String lerUID() {
  String id = "";

  for (byte i = 0; i < leitor_rfid.uid.size; i++) {
    id.concat(String(leitor_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    id.concat(String(leitor_rfid.uid.uidByte[i], HEX));
  }

  id.toUpperCase();
  
  return id;
}

void piscarLED() {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
}

bool verificarId(String id) {
  return id.substring(1) == "45 D4 D4 35";
}
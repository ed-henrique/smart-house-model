/*
Este código contém a implementação da garagem no Arduino Nano. Esta, por sua vez, é composta por
um leitor RFID e um servo motor, simulando assim uma autenticação para abertura de portão.
Este modulo foi designado para Lucas Ribeiro, que o implementou.
*/

#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>

int posicao = 0;
Servo portao;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 leitor_rfid(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);
    SPI.begin();
    leitor_rfid.PCD_Init();
    portao.attach(6);
}

void loop() {
    if (!leitor_rfid.PICC_IsNewCardPresent()) return;
    if (!leitor_rfid.PICC_ReadCardSerial()) return;

    String id = lerUID();
    bool idEstaCorreto = verificarId(id);

    if (idEstaCorreto) {
        Serial.println("[GARAGEM] Portão foi aberto!");
        abrirGaragem();
    }
}

String lerUID() {
    String id = "";

    for (byte i = 0; i < leitor_rfid.uid.size; i++)  {
        id.concat(String(leitor_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
        id.concat(String(leitor_rfid.uid.uidByte[i], HEX));
    }

    id.toUpperCase();

    return id;
}

void abrirGaragem() {
    for (posicao = 0; posicao < 90; posicao++) {
        portao.write(posicao);
        delay(15);
    }

    delay(5000);

    for (posicao = 90; posicao > 0; posicao--) {
        portao.write(posicao);
        delay(15);
    }
}

bool verificarId(String id) {
  return id.substring(1) == "15 5B 0E 88";
}
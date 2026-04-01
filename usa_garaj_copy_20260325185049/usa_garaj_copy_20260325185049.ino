#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RFID_SS_PIN 10
#define RFID_RST_PIN 9
#define SERVO_PIN 4

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);
Servo servoMotor;

String cardPermis[] = {"13", "93", "4B", "F5"};


void setup() {
  setup_usa_garaj();
}

void loop() {
  loop_usa_garaj();
}

void setup_usa_garaj() {
    Serial.begin(9600);

  // Pornim RFID-ul
  SPI.begin();
  rfid.PCD_Init();

  // Servo si LED-uri
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(0);

 



  Serial.println("Sistemul este pregatit! Apropie un card.");
}

void loop_usa_garaj() {
  while (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {

  }
  Serial.print("Card scanat: ");
  String cardID[4];

  for (byte i = 0; i < 4; i++) {
    cardID[i] = String(rfid.uid.uidByte[i], HEX);

    if (cardID[i].length() == 1) {
      cardID[i] = "0" + cardID[i];
    }
    cardID[i].toUpperCase();
    Serial.print(cardID[i] + " ");
  }
  Serial.println();

  // verificarea
  bool cardCorect = true;
  for (byte i = 0; i < 4; i++) {
    if (cardID[i] != cardPermis[i]) {
      cardCorect = false;
      break;
    }
  }

  if (cardCorect) {
    Serial.println("Card corect!");

   
    servoMotor.write(90);

    delay(3000);

    
    servoMotor.write(0);
  }
  else {
    Serial.println("Card gresit!");

   
}
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

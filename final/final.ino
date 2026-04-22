// Ce pini sunt folositi
#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#include<DHT.h>
#include<LiquidCrystal_I2C.h>


Servo CADOURI_servomotor;


const int CADOURI_SERVO_PIN = 4;
const int CADOURI_BTN_PIN = 5;

int CADOURI_unghi = 0;
int DHT_PIN = 11;

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHT_PIN, DHT11);

#define RFID_SS_PIN 10
#define RFID_RST_PIN 9
#define SERVO_PIN 6

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);
Servo servoMotor;

String cardPermis[] = {"13", "93", "4B", "F5"};

void setup() {
  setup_usa_garaj();
  setup_usa_intrare();
  cadouri_surpriza_setup();
  setup_temp_sensors();
}

void loop() {
  loop_usa_garaj();
  loop_usa_intrare();
  cadouri_surpriza_loop();
  loop_temp_sensors();
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

void setup_usa_intrare() {
  // setarile initiale
}

void loop_usa_intrare() {
  // toata logica din loop
}

void cadouri_surpriza_setup() {
  Serial.begin(9600);
  CADOURI_servomotor.attach(CADOURI_SERVO_PIN);
  CADOURI_servomotor.write(CADOURI_unghi);
  delay(2000);
  pinMode(CADOURI_BTN_PIN, INPUT_PULLUP);

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

void cadouri_surpriza_loop() {
   if (digitalRead(CADOURI_BTN_PIN) == LOW){

    CADOURI_unghi = 180;
    

  }

  CADOURI_servomotor.write(CADOURI_unghi);
  
  if (digitalRead(CADOURI_BTN_PIN) == HIGH){

    CADOURI_unghi = 0;

  }

}

void setup_temp_sensors() {
delay(100);
lcd.init();
dht.begin();
lcd.backlight();
}

void loop_temp_sensors() {
 
float temperatura =dht.readTemperature();
float umiditate = dht.readHumidity();

lcd.clear();
lcd.print("Temp:");
lcd.print(temperatura);
lcd.setCursor(0,1);
lcd.print("umid:");
lcd.print(umiditate);
delay(1000);

}
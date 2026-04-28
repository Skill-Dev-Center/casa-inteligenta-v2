// Ce pini sunt folositi
#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// PINS
const int CADOURI_SERVO_PIN = 4;
const int CADOURI_BTN_PIN = 5;
const int TEMP_SENSORS_DHT_PIN = 7;
const int USA_INTRARE_BTN_PIN = 3;
const int USA_INTRARE_SERVO_PIN = 8;
const int USA_GARAJ_RFID_SS_PIN = 10;
const int USA_GARAJ_RFID_RST_PIN = 9;
const int USA_GARAJ_SERVO_PIN = 6;

// COMPONENTS
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(TEMP_SENSORS_DHT_PIN, DHT11);
MFRC522 rfid(USA_GARAJ_RFID_SS_PIN, USA_GARAJ_RFID_RST_PIN);
Servo USA_GARAJ_servoMotor;
Servo CADOURI_servomotor;
Servo USA_INTRARE_servomotor;

// HELPERS
String cardPermis[] = {"13", "93", "4B", "F5"};
int usa_intrare_unghi = 0;
int CADOURI_unghi = 0;
bool USA_GARAJ_verify = false;

void setup() {
  // setup_usa_intrare();
  cadouri_surpriza_setup();
  setup_temp_sensors();
  setup_usa_garaj();
}

void loop() {
  // loop_usa_intrare();
  cadouri_surpriza_loop();
  loop_temp_sensors();
  loop_usa_garaj();
}

// =======================================
// ============== USA GARAJ ==============
// =======================================
void setup_usa_garaj() {
  Serial.begin(9600);

  // Pornim RFID-ul
  SPI.begin();
  rfid.PCD_Init();

  // Servo si LED-uri
  USA_GARAJ_servoMotor.attach(USA_GARAJ_SERVO_PIN);
  USA_GARAJ_servoMotor.write(0);

  Serial.println("Sistemul este pregatit! Apropie un card.");
}

void loop_usa_garaj() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    USA_GARAJ_verify = false;  
  } 
  else {
    USA_GARAJ_verify = true;
  }

  if (USA_GARAJ_verify) {
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
      USA_GARAJ_servoMotor.write(90);
      delay(3000);
      USA_GARAJ_servoMotor.write(0);
    }
    else {
      Serial.println("Card gresit!");
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}


// =======================================
// ============= USA CADOURI =============
// =======================================
void cadouri_surpriza_setup() {
  pinMode(CADOURI_BTN_PIN, INPUT_PULLUP);
  CADOURI_servomotor.attach(CADOURI_SERVO_PIN);
  CADOURI_servomotor.write(CADOURI_unghi);
}

void cadouri_surpriza_loop() {
  if (digitalRead(CADOURI_BTN_PIN) == LOW){
    CADOURI_unghi = 180;
    CADOURI_servomotor.write(CADOURI_unghi);
    delay(3000);
  }
  if (digitalRead(CADOURI_BTN_PIN) == HIGH) {
    CADOURI_unghi = 0;
    CADOURI_servomotor.write(CADOURI_unghi);
  }
}

// =======================================
// ============= TENO & UMID =============
// =======================================
void setup_temp_sensors() {
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

// =======================================
// ============= USA INTRARE =============
// =======================================
void setup_usa_intrare() {
  pinMode(USA_INTRARE_BTN_PIN, INPUT_PULLUP);
  USA_INTRARE_servomotor.attach(USA_INTRARE_SERVO_PIN);
  USA_INTRARE_servomotor.write(usa_intrare_unghi);
}

void loop_usa_intrare() {
  if (digitalRead(USA_INTRARE_BTN_PIN) == LOW) {
    usa_intrare_unghi = 180;
    delay(3000);
    USA_INTRARE_servomotor.write(usa_intrare_unghi);
  }
  if (digitalRead(USA_INTRARE_BTN_PIN) == HIGH) {
    usa_intrare_unghi = 0;
    USA_INTRARE_servomotor.write(usa_intrare_unghi);
  }
}
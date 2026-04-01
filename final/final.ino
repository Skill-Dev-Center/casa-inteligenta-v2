// Ce pini sunt folositi
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

void setup() {
  setup_usa_intrare();
  cadouri_surpriza_setup();
  setup_temp_sensors();
}

void loop() {
  loop_usa_intrare();
  cadouri_surpriza_loop();
  loop_temp_sensors();
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






















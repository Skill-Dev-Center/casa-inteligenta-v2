#include <Wire.h>
#include<DHT.h>
#include<LiquidCrystal_I2C.h>
int DHT_PIN = 11;

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHT_PIN, DHT11);

void setup() {
setup_temp_sensors();
}

void loop() {
loop_temp_sensors();
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

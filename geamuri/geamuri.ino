/*
- Row1 -> Pin 5
- Row2 -> Pin 6
- Row3 -> Pin 7
- Row4 -> Pin 8

- Column1 -> Pin 9
- Column2 -> Pin 10
- Column3 -> Pin 11
- Column4 -> Pin 12
*/

// WINDOWS

// LIBRARIES
#include <Keypad.h>

// GLOBALS
String currentCode = "";

// CONSTANTS
const byte ROWS = 4;
const byte COLS = 4;
const String keypadCode = "5#C1";

// DEFINE KEYPAD KEYS
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {9, 10, 11, 12};

// Keypad Initialization
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// FUNCTIONS
void setup() {
  Serial.begin(9600);
  setupKeypad();
}

void loop() {
  keypadMain();
}

void setupKeypad() {
  keypad.setHoldTime(500);
  keypad.setDebounceTime(50);

  Serial.println("Initialized keypad!");
}

void keypadMain() {
  char key = keypad.getKey();

  if (currentCode.length() >= keypadCode.length()) {
    if (currentCode == keypadCode) {
      Serial.println("Windows open.");
    } else {
      Serial.println("Attempt to open windows with code " + currentCode + "!");
    }

    currentCode = "";
    
  } else if (key) {
    currentCode += key;
    Serial.println("CODE: " + currentCode);
  }
}

void setupWindows() {

}

void loopWindows() {

}
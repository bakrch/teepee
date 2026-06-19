#include <Arduino.h>

// put function declarations here:
int printText(const char*);
HardwareSerial printer(2);

void setup() {
  // put your setup code here, to run once:
  delay(2000);   // critical
  printer.begin(
    9600,
    0x800001c,
    16,
    17
  );
  printer.println("");
  printer.println("");
  delay(50);
  printer.println("******************************");
  delay(50);
  printer.println("********* HELLO BABY *********");
  delay(50);
  printer.println("******************************");
  delay(50);
  printer.println("");
  printer.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int printText(const char* str) {
  printer.println(str);
}
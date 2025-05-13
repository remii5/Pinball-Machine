#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 10, 11, 5, 4, 3, 2);

char arr1[] = "SPEED";

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,1);
  lcd.print("SPEED"); 
}


void loop() {}

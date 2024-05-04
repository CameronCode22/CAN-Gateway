#include <LiquidCrystal.h>

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  delay(100);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("Hello World");

  // set the cursor to column 0, line 1
  // Line 1 is second row, as it begins at 0
 
}

void loop() {


}
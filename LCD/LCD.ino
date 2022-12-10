#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int buzz = 9;

void setup()
{
}

void loop()
{
  lcd.print("HELLO");
  delay(500);
  lcd.clear();
  delay(500);
}

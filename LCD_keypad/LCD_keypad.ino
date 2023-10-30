
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

uint8_t ho[8] =
{
    0b00100,
    0b11111,
    0b00000,
    0b01110,
    0b10001,
    0b01110,
    0b00100,
    0b11111,
};


void setup()
{
    lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
    lcd.backlight();

    lcd.createChar(0, ho);

}

void loop()
{

  delay(500);
  lcd.setCursor(4, 0);
  lcd.print('2');
  
  delay(500);
  lcd.setCursor(6, 0);
  lcd.print('0');
  
  delay(500);
  lcd.setCursor(8, 0);
  lcd.print('1');
  
  delay(500);
  lcd.setCursor(10, 0);
  lcd.write(ho);



}

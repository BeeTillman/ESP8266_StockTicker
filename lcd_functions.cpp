#include "lcd_functions.h"

byte check[8] = {
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000,
  B00000
};

byte downArrow[8] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00000
};

byte upArrow[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000
};

byte loadingOne[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B11111
};

byte loadingTwo[8] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B00000,
  B00000
};

byte funkyChar[8] = {
  B10010,
  B01100,
  B01100,
  B10010,
  B01001,
  B00110,
  B00110,
  B01001
};

byte newDollar[8] = {
  B00100,
  B11111,
  B10100,
  B11111,
  B00101,
  B11111,
  B00100,
  B00000
};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void createCustomChars(){
  lcd.createChar(0, loadingOne);
  lcd.createChar(1, loadingTwo);
  lcd.createChar(2, check);
  lcd.createChar(3, upArrow);
  lcd.createChar(4, downArrow);
  lcd.createChar(5, funkyChar);
  lcd.createChar(6, newDollar);
}

void displayInitialStartup(){
  lcd.init();
  lcd.backlight();
  createCustomChars();
  lcd.setCursor(0,0);
  lcd.write(' ');
  lcd.write(' ');
  lcd.write(5);
  lcd.print(" Welcome ");
  lcd.write(5);
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("ESP Stock Ticker");
  delay(6000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(0,0);
  lcd.write(' ');
  lcd.write(5);
  lcd.print(" Created By ");
  lcd.write(5);
  delay(2500);
  lcd.setCursor(0,1);
  lcd.print("Billups Tillman");
  delay(6500);
}

void displayStockResult(String ticker, float float_pchange, String currentPrice){
    lcd.clear();
    lcd.setCursor(0,0);
    if (float_pchange < 0){
      lcd.write(6);
      lcd.print(ticker + " ");
      lcd.write(4);
      lcd.write(' ');
      lcd.print(String(float_pchange) + "%");
      //lcd.print("$" + ticker + " | " + float_pchange + "%");
      lcd.setCursor(0,1);
      lcd.write(6);
      lcd.print(String(currentPrice));
    }else{
      lcd.write(6);
      lcd.print(ticker + " ");
      lcd.write(3);
      lcd.write(' ');
      lcd.print(String(float_pchange) + "%");
      //lcd.print("$" + ticker + " | +" + float_pchange + "%");
      lcd.setCursor(0,1);
      lcd.write(6);
      lcd.print(String(currentPrice));
    }
}

void clearResetLCD(){
  lcd.clear();
  lcd.setCursor(0, 0);
}

void displayReconnectingCycle(){
    clearResetLCD();
    lcd.print("Reconnecting...");
    lcd.setCursor(0, 1);
    int sent = 0;
    while (sent < 15){
      lcd.write(0);
      delay(300);
      sent++;
    }
    sent = 0;
    while (sent < 14){
      if (sent != 0){
        lcd.setCursor(sent-1, 1);
        lcd.write(0);
      }
      lcd.setCursor(sent+1, 1);
      lcd.write(1);
      delay(450);
      sent++;
    }
}

void displayWifiSuccess(){
  clearResetLCD();
  lcd.print("WiFi Connected!");
  lcd.setCursor(0, 1);
  int sent = 15;
  while (sent > 0){
    lcd.write(2);
    delay(200);
    sent--;
  }
  delay(500);
}
#include "lcd_functions.h"
#include "customChars.h"

#define introDelay 6500 // The delay between the intro sequence and the Initial wifi connection

bool lcd2004 = true; // If you are using a 16x2, set this to false.

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD(){
if(lcd2004){
  lcd = LiquidCrystal_I2C(0x27, 20, 4);
}
}


void createCustomChars(){
  lcd.createChar(0, loadingOne);
  lcd.createChar(1, loadingTwo);
  lcd.createChar(2, check);
  lcd.createChar(3, upArrow);
  lcd.createChar(4, downArrow);
  lcd.createChar(5, funkyChar);
  lcd.createChar(6, newDollar);
  lcd.createChar(7, borderTB);
}

void displayInitialStartup(){
  lcd.init();
  lcd.backlight();
  createCustomChars();
  lcd.setCursor(0,0);
  lcd.write(' ');
  lcd.write(' ');
  if(lcd2004){
    lcd.write(' ');
    lcd.write(' ');
  }
  lcd.write(5);
  if(lcd2004){
    lcd.print(" Welcome! ");
  }
  else{
    lcd.print(" Welcome ");
  }
  lcd.write(5);
  delay(2000);
  lcd.setCursor(0,1);
  if(lcd2004){
    lcd.write(' ');
    lcd.write(' ');
  }
  lcd.print("ESP Stock Ticker");
  delay(3000);
  if(lcd2004){
    lcd.setCursor(0,2);
    lcd.write(' ');
    lcd.write(' ');
    lcd.write(' ');
    lcd.write(5);
    lcd.print(" Created By ");
    lcd.write(5);
    delay(1500);
    lcd.setCursor(0,3);
    lcd.write(' ');
    lcd.write(' ');
    lcd.write(2);
    lcd.print("Billups Tillman");
  }
  else{
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
  }
  delay(introDelay);
}

void displayStockResult(String ticker, float float_pchange, String currentPrice){
    clearResetLCD()
    if(lcd2004) printBorders();
    if (float_pchange < 0){
      lcd.write(6);
      lcd.print(ticker + " ");
      lcd.write(4);
      lcd.write(' ');
      lcd.print(String(float_pchange) + "%");
      if(lcd2004) lcd.setCursor(0,2);
      else lcd.setCursor(0,1);
      lcd.write(6);
      lcd.print(String(currentPrice));
    }else{
      lcd.write(6);
      lcd.print(ticker + " ");
      lcd.write(3);
      lcd.write(' ');
      lcd.print(String(float_pchange) + "%");
      if(lcd2004) lcd.setCursor(0,2);
      else lcd.setCursor(0,1);
      lcd.write(6);
      lcd.print(String(currentPrice));
    }
}

void clearResetLCD(){
  lcd.clear();
  lcd.setCursor(0, 0);
}

void printBorders(){
  lcd.setCursor(0,0);
  for(int i = 0; i <= 20; i++){
    lcd.write(7);
  }
  lcd.setCursor(0,3);
  for(int i = 0; i <= 20; i++){
    lcd.write(7);
  }
  lcd.setCursor(0,1);
}
void displayReconnectingCycle(){
    clearResetLCD();
    if(lcd2004){
      printBorders();
      lcd.write(' ');
      lcd.write(' ');
    }
    lcd.print("Reconnecting...");
    lcd.setCursor(0, 1);
    if(lcd2004){
      lcd.setCursor(0, 2);
      int sent = 0;
      while (sent < 20){
        lcd.write(0);
        delay(300);
        sent++;
      }
      sent = 0;
      while (sent < 19){
        if (sent != 0){
          lcd.setCursor(sent-1, 2);
          lcd.write(0);
        }
      lcd.setCursor(sent+1, 2);
      lcd.write(1);
      delay(450);
      sent++;
      }  
    }
    else{
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
}

void displayWifiSuccess(){
  clearResetLCD();
  if(lcd2004){
    printBorders();
    lcd.write(' ');
    lcd.write(' ');
  }
  lcd.print("WiFi Connected!");
  if(lcd2004){
    lcd.setCursor(0,2);
    lcd.write(' ');
    lcd.write(' ');
  } 
  else lcd.setCursor(0,1);
  int sent = 15;
  while (sent > 0){
    lcd.write(2);
    delay(200);
    sent--;
  }
  delay(500);
}
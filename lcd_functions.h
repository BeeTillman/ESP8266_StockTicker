#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void createCustomChars();

void displayInitialStartup();

void displayStockResult(String ticker, float float_pchange, String currentPrice);

void clearResetLCD();

void displayReconnectingCycle();

void displayWifiSuccess();

#endif
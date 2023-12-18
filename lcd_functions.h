#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void initLCD();

void createCustomChars();

void displayInitialStartup();

void displayStockResult(String ticker, float float_pchange, String currentPrice);

void clearResetLCD();

void displayReconnectingCycle();

void displayWifiSuccess();

void printBorders();

#endif
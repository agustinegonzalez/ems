#include "inicializar-lcd.h"

// Dirección I2C típica del módulo PCF8574
// Puede ser 0x27 o 0x3F según el adaptador
#define LCD_ADDR 0x27

#define LCD_COLS 16
#define LCD_ROWS 2

//efinición del objeto LCD
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void inicializarLCD() {
    lcd.init();           // Inicializa el módulo
    lcd.backlight();      // Enciende la retroiluminación
}


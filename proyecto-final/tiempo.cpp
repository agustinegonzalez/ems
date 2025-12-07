#include <Arduino.h>
#include "tiempo.h"
#include "inicializar-lcd.h"
#include "inicializar-teclado.h"

int capturarTiempo() {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tiempo en seg:");
  lcd.setCursor(0,1);

  String buffer = "";

  while (true) {
    char t = teclado.getKey();
    if (!t) continue;

    // Si es un número, lo añade
    if (t >= '0' && t <= '9') {
      if (buffer.length() < 4) {        // máximo 9999s
        buffer += t;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tiempo en seg:");
        lcd.setCursor(0,1);
        lcd.print(buffer);
      }
    }

    // Confirmar con C
    if (t == 'C') {
      if (buffer.length() > 0) {
        return buffer.toInt();
      }
    }

    // Borrar último dígito con D
    if (t == 'D') {
      if (buffer.length() > 0) {
        buffer.remove(buffer.length() - 1);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tiempo en seg:");
        lcd.setCursor(0,1);
        lcd.print(buffer);
      }
    }

    // Cancelar con A
    if (t == 'A') {
      return 0;
    }
  }
}


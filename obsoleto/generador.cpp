#include <Arduino.h>
#include "generador.h"
#include "inicializar-lcd.h"

static const int tablaSize = 256;
static uint8_t tablaSeno[tablaSize];

int pinDAC_global = 25;

void iniciarDAC(int pinDAC) {
  pinDAC_global = pinDAC;

  for (int i = 0; i < tablaSize; i++) {
    float a = (2.0f * PI * i) / tablaSize;
    tablaSeno[i] = (uint8_t)(128 + 127 * sin(a));
  }
}

void generarSenoConCuentaAtras(float frecuencia, int duracion_ms) {

  float periodo = 1.0 / frecuencia;
  float tiempo_micro = (periodo / tablaSize) * 1e6;

  unsigned long fin = millis() + duracion_ms;
  int tiempoRestante = duracion_ms / 1000;

  unsigned long proximaActualizacion = millis() + 1000;

  // Mostrar estado inicial
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Terapia activa");
  lcd.setCursor(0,1);
  lcd.print("Faltan: ");
  lcd.print(tiempoRestante);
  lcd.print("s");

  while (millis() < fin) {

    for (int i = 0; i < tablaSize; i++) {

      //Parar ensguida si se presiona "D"
      char t = teclado.getKey();
      if (t == 'D') {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Cancelada!");
        delay(1000);
        return;   //salir inmediatamente 
      }

      dacWrite(pinDAC_global, tablaSeno[i]);
      delayMicroseconds((int)tiempo_micro);

      // actualizar cuenta regresiva
      if (millis() >= proximaActualizacion) {
        tiempoRestante--;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Terapia activa");
        lcd.setCursor(0,1);
        lcd.print("Faltan: ");
        lcd.print(tiempoRestante);
        lcd.print("s");

        proximaActualizacion = millis() + 1000;
      }

      if (millis() >= fin) break;
    }
  }
}



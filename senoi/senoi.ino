// Generador de onda senoidal con DAC en ESP32 (NodeMCU-32S)
// Autor: ChatGPT (GPT-5)
// Pin de salida: GPIO25 (DAC1)

#include <Arduino.h>

const int dacPin = 25;      // DAC1 (GPIO25)
const int numMuestras = 100; // cantidad de puntos por ciclo
const float frecuencia = 100.0; // frecuencia de la onda senoidal (Hz)


uint8_t tablaSeno[numMuestras];

void setup() {
  // tabla de valores senoidales
  for (int i = 0; i < numMuestras; i++) {
    float angulo = 2.0 * PI * i / numMuestras;
    tablaSeno[i] = (uint8_t)(127.5 + 127.5 * sin(angulo)); // 0–255
  }
}

void loop() {
  // Periodo total de una onda
  float periodo = 1.0 / frecuencia; // segundos
  // Tiempo entre muestras
  float tiempoPorMuestra = periodo / numMuestras; // segundos

  // conversion a microsegundos
  int delayMicro = (int)(tiempoPorMuestra * 1e6);

  // Recorrem tabla para una onda completa
  for (int i = 0; i < numMuestras; i++) {
    dacWrite(dacPin, tablaSeno[i]);
    delayMicroseconds(delayMicro);
  }
}

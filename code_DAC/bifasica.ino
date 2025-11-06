// Generador de onda compuesta: caída lineal desde mitad, rampa ascendente y caída exponencial
// Salida analógica DAC GPIO25
// Autor: ChatGPT (GPT-5)

#include <Arduino.h>

const int dacPin = 25;           // DAC1 (GPIO25)
const int numMuestras = 180;     // número total de puntos
const float frecuencia = 10.0;   // frecuencia de repetición en Hz

uint8_t formaOnda[numMuestras];

void setup() {
  // Dividimos el ciclo en 3 secciones
  int parte1 = numMuestras / 4;        // caída lineal (127 → 0)
  int parte2 = numMuestras / 3;        // subida lineal (0 → 255)
  int parte3 = numMuestras - parte1 - parte2; // caída exponencial (255 → 0)

  // --- 1️⃣ Caída lineal desde mitad (127) a 0 ---
  for (int i = 0; i < parte1; i++) {
    formaOnda[i] = map(i, 0, parte1 - 1, 127, 0);
  }

  // --- 2️⃣ Rampa ascendente desde 0 a 255 ---
  for (int i = parte1; i < parte1 + parte2; i++) {
    formaOnda[i] = map(i, parte1, parte1 + parte2 - 1, 0, 255);
  }

  // --- 3️⃣ Caída exponencial desde 255 a 0 ---
  float tau = 14.0; // constante de decaimiento (ajustable)
  int idx = 0;
  for (int i = parte1 + parte2; i < numMuestras; i++) {
    float x = idx++;
    float val = 255.0 * exp(-x / tau);
    formaOnda[i] = (uint8_t)val;
  }
}

void loop() {
  // Tiempo entre muestras
  float periodo = 1.0 / frecuencia;
  float tiempoPorMuestra = periodo / numMuestras;
  int delayMicro = (int)(tiempoPorMuestra * 1e6);

  // Recorre el buffer para una onda completa
  for (int i = 0; i < numMuestras; i++) {
    dacWrite(dacPin, formaOnda[i]);
    delayMicroseconds(delayMicro);
  }
}


#ifndef GENERADOR_ONDA_H
#define GENERADOR_ONDA_H

void iniciarDAC(int pinDAC = 25);  
void generarSeno(float frecuencia, int duracion_ms);
void generarSenoConCuentaAtras(float frecuencia, int duracion_ms);

#endif


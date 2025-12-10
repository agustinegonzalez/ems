#include "terapias.h"
#include "generador.h"

void terapiaRecuperacion(int segundos) {
    generarSenoConCuentaAtras(200.0f, segundos * 1000);
}

void terapiaRelax(int segundos) {
    generarSenoConCuentaAtras(400.0f, segundos * 1000);
}

void terapiaOtra(int segundos) {
    generarSenoConCuentaAtras(1000.0f, segundos * 1000);
}


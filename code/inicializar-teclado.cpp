#include "inicializar-teclado.h"
const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//pines conectados a las filas y columnas del teclado (empieza desde la izquierda visto de frente)
byte pinesFilas[FILAS] = {32, 33, 23, 26};     // F1, F2, F3, F4
byte pinesColumnas[COLUMNAS] = {27, 14, 12, 13}; // C1, C2, C3, C4

//Inicialización del teclado
//Declaracion de la clase -> Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

void inicializarTeclado() {
  //teclado.setDebounceTime(20);
}

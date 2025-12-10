1#include <Arduino.h>
#include "inicializar-teclado.h"
#include "inicializar-lcd.h"
#include "generador.h"
#include "terapias.h"
#include "tiempo.h"
int opcion = 0;                // índice del menú (0,1,2)
const int totalOpciones = 3;
//A = subir
//B = bajar
//C = seleccionar
//D = salir o volver
void mostrarMenuConCursor();

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22); 
  inicializarLCD();
  inicializarTeclado();
  iniciarDAC(25);
  lcd.clear();
  lcd.print("Electroestimulador");
  lcd.setCursor(0,1);
  lcd.print("'C' para ir al menu");

  // esperamos tecla C para entrar al menú
  while (true) {
    char t = teclado.getKey();
    if (t == 'C') break;
  }

  mostrarMenuConCursor();
}

void loop() {

  char t = teclado.getKey();

  //check error
  if (!t) return;

  if (t == 'A') {  // Subir
    opcion--;
    if(opcion < 0)
      opcion = totalOpciones - 1;
    mostrarMenuConCursor();
  }

  if (t == 'B') {  // Bajar
    opcion++;
    if(opcion >= totalOpciones)
      opcion = 0;
    mostrarMenuConCursor();
  }

  // Opción seleccionada con C

 if (t == 'C') {

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tiempo?");

    int tiempo = capturarTiempo();   // pedir tiempo al usuario

    if (tiempo == 0) {
      lcd.clear();
      lcd.print("Cancelado");
      delay(1000);
      mostrarMenuConCursor();
      return;
    }

    lcd.clear();
    lcd.print("Ejecutando...");
    lcd.setCursor(0,1);
    lcd.print(String(tiempo) + " seg");

    if(opcion == 0) terapiaRecuperacion(tiempo);
    if(opcion == 1) terapiaRelax(tiempo);
    if(opcion == 2) terapiaOtra(tiempo);

    lcd.clear();
    lcd.print("Fin terapia");
    delay(1000);
    mostrarMenuConCursor();
}


  // Volver con D
  if (t == 'D') {
    lcd.clear();
    lcd.print("Regresando...");
    delay(1000);

    mostrarMenuConCursor();
  }
}
void mostrarMenuConCursor() {
  lcd.clear();

  if(opcion == 0) {
    lcd.setCursor(0,0); lcd.print(">1:Recup 200Hz");
    lcd.setCursor(0,1); lcd.print(" 2:Relax 400Hz");
  }
  else if(opcion == 1) {
    lcd.setCursor(0,0); lcd.print(" 1:Recup 200Hz");
    lcd.setCursor(0,1); lcd.print(">2:Relax 400Hz");
  }
  else if(opcion == 2) {
    lcd.setCursor(0,0); lcd.print(" 2:Relax 400Hz");
    lcd.setCursor(0,1); lcd.print(">3:Otra 1000Hz");
  }
}

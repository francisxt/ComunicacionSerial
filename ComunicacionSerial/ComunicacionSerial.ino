#include <LiquidCrystal.h>

//#include "serial.h"
//#include <dynmem.h>

#define MAX_BUFFER 100
#define END_CMD_CHAR '#'
#define DIV_CMD_CHAR '|'

LiquidCrystal Pantalla(4, 5, 6, 7, 8, 9);
char caracter;
String cadena;
 // Almacenamos el estado como variable global
int estado=LOW;
int estado_transf=LOW;
// Almacenamos también el número de milisegundos anterior
unsigned long momento_anterior=0;
unsigned long bytes_recibidos=0;

void setup() {
  // put your setup code here, to run once:
  Pantalla.begin(16,2);
  Pantalla.setCursor(1,0);
  Pantalla.print("Reproductor");
  Pantalla.setCursor(7,1);
  Pantalla.print("Musical");
  delay(1750);  
  Pantalla.clear();
  Serial.begin(9600);
  //pinMode(STATUS_LED, OUTPUT);
  // Queremos salida por el led de transferencia
  //pinMode(TRANSF_LED, OUTPUT);
  }

// serial1
// Hace un eco con el puerto serie del Arduino, leyendo una cadena completa
/*
int serialGetString(char *string, int max)
{
  unsigned i=0;
  char sIn;
  // Queremos que la cadena se rellene hasta max-2 para que en el carácter
  // max-1 (el último) podamos meter el terminador \0
  --max;        
  while (Serial.available() && i<max)
    {
      sIn=Serial.read();
      string[i++]=sIn;
      // La recepción tiene una latencia, se produce a través de una interrupción, que a lo mejor se ejecuta
      // un poco después del Serial.available() por lo que el dato no entraría, por eso hacemos una pequeña espera
      delayMicroseconds(500);
    }
  string[i++]='\0';
  return i;
}

void loop () 
{  
  int recibe;
  unsigned long momento_actual=millis();
  char buf[MAX_BUFFER];
// No bloqueante, si hay algo para leer entramos, si no, no.
  if(Serial.available()) 
    {
      serialGetString(buf, MAX_BUFFER);
      // Escribimos el buffer completo
      //Serial.println((char*)buf);
      Pantalla.setCursor(1,0);
      Pantalla.clear();
      Pantalla.print(buf);
      Pantalla.scrollDisplayLeft();
      delay(1900);
      
    }
}
  // No usamos delay para el parpadeo porque nos entorpece la comunicación con el serial
  /*if (momento_actual-momento_anterior>=BLINK_DELAY)
    {
      // Cambiamos el estado siguiente. Si era HIGH (1) ahora será 
      // LOW (0). He leído en algún lado que el valor de HIGH no 
      // siempre es 1; pero en este caso sí es así. 
      estado=!estado;
      // Escribimos el estado actual del led
      digitalWrite(STATUS_LED, estado);
      // Establecemos el momento anterior como actual.
      momento_anterior=momento_actual;
    }
}*/
void loop() {
  // put your main code here, to run repeatedly:
 
   while (Serial.available())  {
      char c = Serial.read();  //gets one byte from serial buffer
      delay(5);
      if (c == END_CMD_CHAR) { // if we the complete string has been read
        Pantalla.print(cadena);
        delay(150);
        Pantalla.clear();
        // add your code here
        break;
      }              
      else {
        if (c !=  DIV_CMD_CHAR) {
          cadena += c; 
          delay(5);
        }
      }
    }
}


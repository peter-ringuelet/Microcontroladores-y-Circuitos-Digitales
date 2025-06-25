/*
 * salidas.c
 *
 * Created: 12/5/2024 22:37:33
 *  Author: barcala
 */ 

#include <avr/io.h>
#include "lcd.h"


void pGanador(uint8_t m1, uint8_t m2, uint8_t s1, uint8_t s2, uint8_t ms1, uint8_t ms2, uint8_t ms3){
	LCDclr();
	LCDGotoXY(4,0);
	LCDstring("GANADOR",7);
	LCDGotoXY(0,1);
	LCDstring("TIME:",5);
	LCDsendChar(m1);
	LCDsendChar(m2);
	LCDsendChar(':');
	LCDsendChar(s1);
	LCDsendChar(s2);
	LCDsendChar(':');
	LCDsendChar(ms1);
	LCDsendChar(ms2);
	LCDsendChar(ms3);
}

void pInicio() {
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring("RECORDAR LA", 11);
	LCDGotoXY(0,1);
	LCDstring("CONTRASENA (*)", 14);
}

void pJugando(){
	LCDclr();
	LCDGotoXY(4,0);
	LCDstring("JUGANDO",7);
	LCDGotoXY(0,1);
	LCDstring("INGRESE NUM:",12);
}

void pNum(uint8_t n1, uint8_t n2, uint8_t n3){
	LCDGotoXY(12,1);
	LCDsendChar(n1);
	LCDsendChar(n2);
	LCDsendChar(n3);
	LCDGotoXY(12,1);
}

void pMostrarPalabra(const char* palabra) {
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring("Memoriza:", 9);
	LCDGotoXY(0,1);
	LCDstring(palabra, strlen(palabra));
}

void pIngresarCodigo() {
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring("Palabra:", 8);
	LCDGotoXY(0,1);
	LCDstring("Codigo ASCII:", 13);
}

void pMostrarCodigo(uint8_t* codigo, uint8_t longitud) {
	LCDGotoXY(13,1);
	for(uint8_t i = 0; i < longitud; i++) {
		LCDsendChar(codigo[i]);
	}
}

void pMostrarPalabraIngresada(const char* palabra) {
	LCDGotoXY(9,0);
	LCDstring(palabra, strlen(palabra));
	LCDGotoXY(0,1);
	LCDstring("Codigo ASCII:", 13);
}

void pMostrarError(uint8_t numErrores) {
	LCDGotoXY(0,1);
	LCDstring("Error ", 6);
	LCDsendChar(numErrores + '0');
	LCDstring(" de 3", 5);
	_delay_ms(1000);
	LCDGotoXY(0,1);
	LCDstring("Codigo ASCII:", 13);
}

void pVictoria(uint32_t t) {
	uint8_t m1, m2, s1, s2, ms1, ms2, ms3;
	getTime(t, &m1, &m2, &s1, &s2, &ms1, &ms2, &ms3);
	
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring("VICTORIA!", 9);
	LCDGotoXY(0,1);
	LCDstring("Tiempo:", 7);
	LCDsendChar(m1);
	LCDsendChar(m2);
	LCDsendChar(':');
	LCDsendChar(s1);
	LCDsendChar(s2);
	LCDsendChar(':');
	LCDsendChar(ms1);
	LCDsendChar(ms2);
	LCDsendChar(ms3);
}

void pDerrota() {
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring("DERROTA!", 8);
	LCDGotoXY(0,1);
	LCDstring("Intentalo de nuevo", 18);
}
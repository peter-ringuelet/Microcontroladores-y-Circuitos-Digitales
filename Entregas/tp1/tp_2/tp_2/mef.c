/*
 * mef.c
 *
 * Created: 11/5/2024 00:45:09
 *  Author: barcala
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "timer.h"
#include "lcd.h"
#include "salidas.h"
#include <string.h>

typedef enum{nulo, inicial, mostrando, ingresando, victoria, derrota} state;

state estado, estadoAnt;
static uint8_t errores, posActual;
static uint8_t codigoActual[3]; // Para almacenar el código ASCII que se está ingresando
static uint8_t indiceCodigoActual;
static char palabraSeleccionada[6]; // 5 caracteres + terminador 
static char palabraIngresada[6];

// Diccionario de palabras
const char* diccionario[] = {
    "Arbol", "Boton", "CDyMC", "ClavE", "Facil", "Gafas", "Hojas", "LiBro", 
    "Lanza", "Nieve", "PeRro", "PecES", "PiAno", "PrYKe", "RUEDa", "SERIE", 
    "SalUd", "Salud", "Silla", "Tecla", "Valor", "Verde", "YnHRz", "hARdD", "silla"
};
#define NUM_PALABRAS (sizeof(diccionario)/sizeof(diccionario[0]))

static uint32_t tiempo_mostrar_palabra = 0;

void Iniciar_MEF(){
	estado = inicial;
	estadoAnt = nulo;
	errores = 0;
	posActual = 0;
	indiceCodigoActual = 0;
	memset(codigoActual, 0, sizeof(codigoActual));
	memset(palabraIngresada, 0, sizeof(palabraIngresada));
}

void Actualizar_MEF(uint8_t* car){
	switch(estado){
		case inicial:
		if(estadoAnt != inicial) {
			estadoAnt = inicial;
			pInicio(); // Mostrar pantalla de inicio
		}
		if(*car == '*') {
			estado = mostrando;
			GameCountInit(); // Inicia el contador del juego
			// Elegí la palabra
			uint8_t indice = rand() % NUM_PALABRAS;
			strcpy(palabraSeleccionada, diccionario[indice]);
			// Guardá el tiempo de inicio para el delay de 2 segundos
			tiempo_mostrar_palabra = ActualTime();
		}
		break;

		case mostrando:
		if(estadoAnt != mostrando) {
			estadoAnt = mostrando;
			pMostrarPalabra(palabraSeleccionada);
		}
		// Espera 2 segundos mostrando la palabra
		if(ActualTime() - tiempo_mostrar_palabra >= 200) { // 200 x 10ms = 2s si tu Timer_Init(10)
			estado = ingresando;
			pIngresarCodigo();
		}
		break;
			
		case ingresando:
			/*if(car >= '0' && car <= '9') {
				// Agregar dígito al código actual
				if(indiceCodigoActual < 3) {
					codigoActual[indiceCodigoActual++] = car;
					pMostrarCodigo(codigoActual, indiceCodigoActual);
				}
			} 
			else if(car == '#') {
				// Procesar el código ASCII ingresado
				if(indiceCodigoActual > 0) {
					uint8_t valorASCII = 0;
					for(uint8_t i = 0; i < indiceCodigoActual; i++) {
						valorASCII = valorASCII * 10 + (codigoActual[i] - '0');
					}
					
					// Verificar si es una letra y si es correcta
					if((valorASCII >= 'A' && valorASCII <= 'Z') || 
					   (valorASCII >= 'a' && valorASCII <= 'z')) {
						
						if(valorASCII == palabraSeleccionada[posActual]) {
							// Caracter correcto
							palabraIngresada[posActual] = valorASCII;
							posActual++;
							pMostrarPalabraIngresada(palabraIngresada);
							
							// Verificar si completó la palabra
							if(posActual >= strlen(palabraSeleccionada)) {
								estado = victoria;
							}
						} else {
							// Caracter incorrecto
							errores++;
							pMostrarError(errores);
							
							if(errores >= 3) {
								estado = derrota;
							}
						}
					} else {
						// No es una letra
						errores++;
						pMostrarError(errores);
						
						if(errores >= 3) {
							estado = derrota;
						}
					}
					
					// Reiniciar para el siguiente código
					indiceCodigoActual = 0;
					memset(codigoActual, 0, sizeof(codigoActual));
				}
			}
			
			if(estadoAnt != ingresando) {
				estadoAnt = ingresando;
				pIngresarCodigo(); // Pantalla para ingresar códigos
			}*/
			break;
			
		case victoria:
			/*if(estadoAnt != victoria) {
				estadoAnt = victoria;
				TCCR0B = 0b00000000; // Detener el timer
				pVictoria(*t); // Mostrar pantalla de victoria con el tiempo
				
				// Esperar 5 segundos y volver al inicio
				_delay_ms(5000);
				estado = inicial;
			}*/
			break;
			
		case derrota:
			/*if(estadoAnt != derrota) {
				estadoAnt = derrota;
				TCCR0B = 0b00000000; // Detener el timer
				pDerrota(); // Mostrar pantalla de derrota
				
				// Esperar 5 segundos y volver al inicio
				_delay_ms(5000);
				estado = inicial;
			}*/
			break;
	}
}
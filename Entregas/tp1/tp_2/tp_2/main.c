/*
 * TP2MICROCHIP.c
 *
 * Created: 22/4/2024 14:37:28
 * Author : Barcala
 */ 
#define F_CPU 16000000UL
#define F_CLK 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "teclado.h"
#include "mef.h"
#include "timer.h"    // Asegurate de incluir el correcto
#include "salidas.h"

void Iniciar_LCD(){
	_delay_ms(50);
	LCDinit();
	_delay_ms(50);
	LCDclr();
	LCDGotoXY(2,0);
	_delay_ms(50);
}

int main(void)
{
	Iniciar_LCD();
	Timer_Init(10);       // por ejemplo, MEF cada 10ms
	Iniciar_MEF();

	srand(1234);

	uint8_t car;
	while(1){
		if (GetFLAG_MEF()) {           // ¡Solo cada "tick" de la MEF!
			// Si querés, podés escanear el teclado acá o adentro de la MEF
			if(!KEYPAD_Scan(&car)){
				car=0xFF;
			}
			Actualizar_MEF(&car);     // o como corresponda en tu lógica
			SetFLAG_MEF(0);           // Resetea el flag
		}
	}
}

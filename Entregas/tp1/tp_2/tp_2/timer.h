#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

ISR(IRQ_request);

// Inicializacion del timer
void Timer_Init(uint8_t top);

// Tiempo desde que inicio el programa
uint32_t ActualTime();

// Contador de juego
void GameCountInit();
uint32_t GameCountStop();

// Contador de fin de juego
void WinCountInit(uint16_t cant);
uint16_t WinCount();

// Getters y Setters del FLAG_MEF
void SetFLAG_MEF(uint8_t flag);
uint8_t GetFLAG_MEF();

#endif
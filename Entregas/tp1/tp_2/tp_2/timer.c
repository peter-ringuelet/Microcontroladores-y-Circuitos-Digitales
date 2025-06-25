#include "Timer.h"
#define F_CPU 16000000UL
#define F_CLK 16000000UL
static uint8_t FLAG_MEF=0, FLAG_COUNTING=0;
static uint8_t cuentaMEF=0, topMEF=0;
static uint16_t cuentaW=0;
static uint32_t cuentaG=0, init_count=0;

ISR(TIMER0_COMPA_vect) { // Rutina de servicio a interrupcion
	init_count++; // Se incrementa el tiempo global
	cuentaMEF++; //Se incrementa el contador para el flag MEF
	if (cuentaMEF == topMEF){ // Si se llego al limite para la MEF
		FLAG_MEF = 1; // Se indica que ya se llego al limite
		cuentaMEF = 0; // Se reinicia la cuenta para la MEF
	}
	if (FLAG_COUNTING){ // Si se esta jugando
		cuentaG++; // Se aumenta el contador "Game"
	}
	if (cuentaW){ // Si todavia no termino el temporizador "Win"
		cuentaW--; // Se decrementa el contador
	}
}

// Inicializacion del timer
void Timer_Init(uint8_t top){
	cli();
	
	//Se inicializa el tiempo de cuenta global
	init_count = 0;
	
	//Se establece el tiempo para el flag de la MEF
	topMEF = top;
	
	// Modo CTC TOP: OCRA
	TCCR0A |= (1<<WGM01);
	TCCR0A &= ~(1<<WGM00);
	TCCR0B &= ~(1<<WGM02);
	
	// Prescaler clk/64
	TCCR0B |= (1<<CS01)|(1<<CS00);
	TCCR0B &= ~(1<<CS02);
	
	// Comparador en el valor para la cuenta cada 1 ms
	OCR0A = 250;
	
	// Se habilita la interrupcion COMP A
	TIMSK0 |= (1<<OCIE0A);
	
	sei();
}
// Tiempo desde que inicio el programa
uint32_t ActualTime(){
	return init_count;
}

// Contador de juego
void GameCountInit(){
	cuentaG = 0; // Se reinicia el contador
	FLAG_COUNTING = 1; // Se indica que se esta contando
}
uint32_t GameCountStop(){
	FLAG_COUNTING = 0; // Se indica que no se debe contar más
	return cuentaG; // Se devuelve el tiempo transcurrido
}

// Contador de fin de juego
void WinCountInit(uint16_t cant){
	cuentaW = cant; // Se inicializa el temporizador
}
uint16_t WinCount(){
	return cuentaW; // Se devuelve el tiempo restante
}

// Getters y Setters del FLAG_MEF
void SetFLAG_MEF(uint8_t flag){
	FLAG_MEF = flag;
}
uint8_t GetFLAG_MEF(){
	return FLAG_MEF;
}

#include <avr/io.h>
#define F_CPU 1000000UL // O 16000000UL segun la frecuencia en Proteus
#include <util/delay.h>

const uint8_t sec_1[] = {
	0b01010101,
	0b10101010
};
const uint8_t sec_2[] = {
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000
};
const uint8_t sec3[] = {
	0b10000000,
	0b01000000,
	0b00100000,
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000
};

void cambiar_secuencia(uint8_t* sec) {
	if (*sec == 1) {
		*sec = 2;
	}
	else if (*sec == 2) {
		*sec = 3;
	}
	else {
		*sec = 1;
	}
}

void mostrar_numero(uint8_t sec) {
	if (sec == 1) {
		PORTB |= (1 << PORTB3);      // 01
	}
	else if (sec == 2) {
		PORTB |= (1 << PORTB4);      // 10
	}
	else {
		PORTB |= (1 << PORTB3) | (1 << PORTB4); // 11
	}
}

int main(void) {
	uint8_t num_sec = 1;
	uint8_t i = 0;

	DDRD = 0xFF; // LEDs como salida
	DDRB |= (1 << PORTB3) | (1 << PORTB4); // Salidas para mostrar el numero
	DDRC &= ~((1 << PORTC0) | (1 << PORTC1)); // Entradas
	PORTC |= (1 << PORTC0) | (1 << PORTC1); // Pull-up internos

	while (1) {
		// Cambio de secuencia
		if (!(PINC & (1 << PINC0))){
			cambiar_secuencia(&num_sec);
			i = 0;
			_delay_ms(200);
		}
		// Mostrar numero si se presiona PC1
		if (!(PINC & (1 << PINC1))) {
			mostrar_numero(num_sec);
			} else {
			PORTB &= ~((1 << PORTB3) | (1 << PORTB4)); // Apagar indicadores
		}
		if (num_sec == 1){
			PORTD = sec_1[i];
			i = (i + 1) % 2;
			}else if (num_sec == 2){
			PORTD = sec_2[i];
			i = (i + 1) % 8;
			}else {
			PORTD = sec3[i];
			i = (i + 1) % 15;
		}
		_delay_ms(100);
	}
}

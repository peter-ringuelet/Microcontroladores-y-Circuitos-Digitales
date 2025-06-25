#include <avr/io.h>
#define F_CPU 16000000UL // Frecuencia en 16 MHz
#include <util/delay.h>

// Prototipos de funciones
void cambiar_secuencia(uint8_t* sec); // Recibe el número de secuencia actual por referencia y lo cambia a la siguiente (1 ? 2 ? 3 ? 1 ? ...)
void mostrar_numero(uint8_t sec);     // Enciende los pines PB3 y PB4 para mostrar el número de secuencia actual en binario con LEDs
void actualizar_secuencia(uint8_t num_sec, uint8_t* i); // Muestra la combinación correspondiente en PORTD según la secuencia actual y actualiza el índice

// Defino vectores con las combinaciones de LEDs para cada secuencia
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

int main(void) {
	uint8_t num_sec = 1; // Número de secuencia actual; comienza en 1 como indica la consigna
	uint8_t i = 0;       // Índice para recorrer los vectores de secuencias
	uint8_t aux = 0;     // Bandera para detectar el momento en que se suelta el botón

	DDRD = 0xFF; // Puerto D como salida para los LEDs
	DDRB |= (1 << PORTB3) | (1 << PORTB4); // Pines PB3 y PB4 como salida para mostrar el número de secuencia
	DDRC &= ~((1 << PORTC0) | (1 << PORTC1)); // Pines PC0 y PC1 como entrada
	PORTC |= (1 << PORTC0) | (1 << PORTC1);   // Activar resistencias pull-up internas en PC0 y PC1

	while (1) {
		// Detectar si se presiona el botón de cambio de secuencia (PC0)
		if (!(PINC & (1 << PINC0))) {
			aux = 1; // Si se presiona el botón, activamos la bandera
		}

		// Si la bandera está activada y el botón fue soltado, cambiamos la secuencia
		if (aux) {
			if ((PINC & (1 << PINC0))) {
				cambiar_secuencia(&num_sec); // Cambiar a la siguiente secuencia
				i = 0;     // Reiniciar el índice para comenzar la nueva secuencia desde el principio
				aux = 0;   // Limpiar la bandera
			}
		}

		// Mostrar el número de la secuencia actual si se presiona PC1
		if (!(PINC & (1 << PINC1))) {
			mostrar_numero(num_sec);
			} else {
			PORTB &= ~((1 << PORTB3) | (1 << PORTB4)); // Apagar los indicadores si no se presiona
		}
		
		actualizar_secuencia(num_sec, &i); // Mostrar el paso actual de la secuencia y actualizar el índice

		_delay_ms(100); // Pequeño retardo entre cada paso de la secuencia
	}
}

void cambiar_secuencia(uint8_t* sec) {
	// Cambia la secuencia de forma cíclica entre 1, 2 y 3
	if (*sec == 1) {
		*sec = 2;
		} else if (*sec == 2) {
		*sec = 3;
		} else {
		*sec = 1;
	}
}

void mostrar_numero(uint8_t sec) {
	// Enciende PB3 y/o PB4 según el número de secuencia actual
	if (sec == 1) {
		PORTB |= (1 << PORTB3);           // 01
		} else if (sec == 2) {
		PORTB |= (1 << PORTB4);           // 10
		} else {
		PORTB |= (1 << PORTB3) | (1 << PORTB4); // 11
	}
}

void actualizar_secuencia(uint8_t num_sec, uint8_t* i) {
	// Muestra la combinación correspondiente en PORTD según la secuencia actual
	// y avanza el índice circularmente
	if (num_sec == 1) {
		PORTD = sec_1[*i];
		*i = (*i + 1) % 2;
		} else if (num_sec == 2) {
		PORTD = sec_2[*i];
		*i = (*i + 1) % 8;
		} else {
		PORTD = sec3[*i];
		*i = (*i + 1) % 15;
	}
}

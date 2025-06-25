#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "RTC.h"
#include "SerialPort.h"

#define BR9600 0x67 // Para 9600 baudios @ 16MHz

// Variables globales
volatile char RX_Buffer[32];
volatile uint8_t RX_index = 0;
volatile uint8_t command_ready = 0;

RTC_t currentTime;
Hora_t alarma;
uint8_t mostrar_hora = 0;
uint8_t alarma_activa = 0;
uint8_t alarma_triggered = 0;
uint8_t alarma_count = 0;

char mensaje[100];

uint8_t hora_igual(Hora_t *a, Hora_t *b) {
	return (a->Hour == b->Hour) && (a->Minute == b->Minute) && (a->Second == b->Second);
}

int main(void) {
	SerialPort_Init(BR9600);
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();
	sei();

	SerialPort_Send_String("UART FUNCIONANDO\n\r");

	RTC_Init();
	_delay_ms(10);

	SerialPort_Send_String("Bienvenido al reloj!\n\r");
	SerialPort_Send_String("Comandos disponibles: ON, OFF, SET TIME, SET ALARM\n\r");

	while (1) {
		RTC_GetTime(&currentTime);

		if (alarma_activa && !alarma_triggered && hora_igual(&currentTime.hora, &alarma)) {
			alarma_triggered = 1;
			alarma_count = 5;
		}

		if (mostrar_hora) {
			uint8_t h = bcd_to_dec(currentTime.hora.Hour);
			uint8_t m = bcd_to_dec(currentTime.hora.Minute);
			uint8_t s = bcd_to_dec(currentTime.hora.Second);
			uint8_t d = bcd_to_dec(currentTime.fecha.Day);
			uint8_t mo = bcd_to_dec(currentTime.fecha.Month);
			uint8_t y = bcd_to_dec(currentTime.fecha.Year);

			sprintf(mensaje, "FECHA: %02d/%02d/%02d HORA:%02d:%02d:%02d\n\r", d, mo, y, h, m, s);
			SerialPort_Send_String(mensaje);
		}

		if (alarma_triggered && alarma_count > 0) {
			SerialPort_Send_String("ALARMA\n\r");
			alarma_count--;
		}

		if (command_ready) {
			command_ready = 0;
			RX_Buffer[RX_index] = '\0';

			if (strcmp((char*)RX_Buffer, "ON") == 0) {
				mostrar_hora = 1;
				SerialPort_Send_String("Mostrando hora...\n\r");

				} else if (strcmp((char*)RX_Buffer, "OFF") == 0) {
				mostrar_hora = 0;
				SerialPort_Send_String("Hora pausada.\n\r");

				} else if (strcmp((char*)RX_Buffer, "SET TIME") == 0) {
				mostrar_hora = 0;
				SerialPort_Send_String("Ingrese la hora con el formato hh:mm:ss dd/mm/aa\n\r");

				RX_index = 0;
				while (!command_ready);
				command_ready = 0;
				RX_Buffer[RX_index] = '\0';

				uint8_t hh, mm, ss, dd, mo, yy;
				sscanf((char*)RX_Buffer, "%hhu:%hhu:%hhu %hhu/%hhu/%hhu", &hh, &mm, &ss, &dd, &mo, &yy);

				currentTime.hora.Hour = dec_to_bcd(hh);
				currentTime.hora.Minute = dec_to_bcd(mm);
				currentTime.hora.Second = dec_to_bcd(ss);
				currentTime.fecha.Day = dec_to_bcd(dd);
				currentTime.fecha.Month = dec_to_bcd(mo);
				currentTime.fecha.Year = dec_to_bcd(yy);
				RTC_SetTime(&currentTime);
				SerialPort_Send_String("Hora seteada.\n\r");

				} else if (strcmp((char*)RX_Buffer, "SET ALARM") == 0) {
				SerialPort_Send_String("Ingrese la alarma con el formato hh:mm:ss\n\r");

				RX_index = 0;
				while (!command_ready);
				command_ready = 0;
				RX_Buffer[RX_index] = '\0';

				uint8_t ah, am, as;
				sscanf((char*)RX_Buffer, "%hhu:%hhu:%hhu", &ah, &am, &as);

				alarma.Hour = dec_to_bcd(ah);
				alarma.Minute = dec_to_bcd(am);
				alarma.Second = dec_to_bcd(as);
				alarma_activa = 1;
				alarma_triggered = 0;
				alarma_count = 0;
				SerialPort_Send_String("Alarma seteada.\n\r");

				} else {
				SerialPort_Send_String("Comando desconocido.\n\r");
			}

			RX_index = 0;
		}

		_delay_ms(1000);
	}
}

ISR(USART_RX_vect) {
	char c = UDR0;
	if (c == '\n' || c == '\r') {
		command_ready = 1;
		} else {
		if (RX_index < sizeof(RX_Buffer) - 1) {
			RX_Buffer[RX_index++] = c;
		}
	}
}

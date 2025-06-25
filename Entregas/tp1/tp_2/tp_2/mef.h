/*
 * mef.h
 *
 * Created: 11/5/2024 00:44:54
 *  Author: barcala
 */ 

#include <avr/io.h>

typedef enum{nulo, inicial, mostrando, ingresando, victoria, derrota} state;

#ifndef MEF_H_
#define MEF_H_

void Iniciar_MEF();

void Actualizar_MEF(uint8_t car);


#endif /* MEF_H_ */
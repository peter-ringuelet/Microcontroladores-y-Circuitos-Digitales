/*
 * salidas.h
 *
 * Created: 12/5/2024 22:37:47
 *  Author: barcala
 */ 


#ifndef SALIDAS_H_
#define SALIDAS_H_

void pGanador(uint8_t m1, uint8_t m2, uint8_t s1, uint8_t s2, uint8_t ms1, uint8_t ms2, uint8_t ms3);
void pInicio();
void pJugando();
void pNum(uint8_t n1, uint8_t n2, uint8_t n3);
void pMostrarPalabra(const char* palabra);
void pIngresarCodigo();
void pMostrarCodigo(uint8_t* codigo, uint8_t longitud);
void pMostrarPalabraIngresada(const char* palabra);
void pMostrarError(uint8_t numErrores);
void pVictoria(uint32_t tiempo);
void pDerrota();



#endif /* SALIDAS_H_ */
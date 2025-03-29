/*
 * Ejemplo de configuración de puertos en ATmega328P
 * 
 * Este programa demuestra el uso de los registros DDRC y PORTC
 * para configurar y controlar los pines del puerto C.
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    /*
     * DDRC=0x0F; (00001111 en binario)
     * Esta instrucción configura la dirección de los pines del puerto C:
     * - Los 4 bits menos significativos (PC0-PC3) se configuran como salidas (1)
     * - Los 4 bits más significativos (PC4-PC7) se configuran como entradas (0)
     */
    DDRC = 0x0F;
    
    /*
     * PORTC=0x0C; (00001100 en binario)
     * Esta instrucción:
     * - Para los pines configurados como salidas (PC0-PC3):
     *   - PC2 y PC3 se establecen en ALTO (1)
     *   - PC0 y PC1 se establecen en BAJO (0)
     * - Para los pines configurados como entradas (PC4-PC7):
     *   - Se desactivan las resistencias pull-up internas (0)
     */
    PORTC = 0x0C;
    
    // Bucle infinito para mantener la configuración
    while (1) {
        // Podríamos agregar código aquí para cambiar los estados de los pines
        // o leer las entradas, pero para este ejemplo simplemente mantenemos
        // la configuración inicial
        _delay_ms(100);
    }
    
    return 0; // Nunca se alcanza en un sistema embebido típico
}

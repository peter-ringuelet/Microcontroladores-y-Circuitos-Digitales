#include <stdio.h>
#include <stdint.h>
#include <unistd.h> // Para sleep()

// Función que envía un número bit por bit
void enviarSerie(uint8_t numero) {
    // Iteramos por cada bit, comenzando por el menos significativo
    for (int i = 0; i < 8; i++) {
        // Extraemos el bit menos significativo
        uint8_t bit = (numero >> i) & 1; // Desplazamos el número i bits a la derecha y aplicamos AND con 1 para obtener el bit menos significativo
        
        // Imprimimos el bit
        printf("Bit %d: %d\n", i, bit);
        
        // Esperamos 1 segundo
        sleep(1);
    }
}

int main() {
    uint8_t numero;
    
    printf("Ingrese un número (0-255): ");
    scanf("%hhu", &numero);
    
    printf("Enviando número %d en serie...\n", numero);
    enviarSerie(numero);
    
    return 0;
}


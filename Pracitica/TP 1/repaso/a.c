#include <stdio.h>
#include <stdint.h>

// Función recursiva que suma los números consecutivos de 1 hasta N
uint16_t sumaConsecutivos(uint8_t N) {
    if (N == 1) {
        return 1;
    }
    return (uint16_t)N + (uint16_t)sumaConsecutivos(N-1);
}

int main() {
    uint8_t numero;
    
    printf("Ingrese un número (0-255): ");
    scanf("%hhu", &numero);
    
    uint16_t resultado = sumaConsecutivos(numero);
    printf("La suma de los números del 1 al %u es: %u\n", numero, resultado);
    
    return 0;
}

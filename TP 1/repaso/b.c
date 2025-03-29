#include <stdio.h>
#include <stdint.h>

// Función que invierte el orden de los elementos de un vector a nivel de bytes
void invertirVector(void* vector, size_t tamano) {
    uint8_t* bytes = (uint8_t*)vector;
    size_t tamElemento = sizeof(int);  // Tamaño de cada elemento
    uint8_t temp;
    
    // Iteramos por cada elemento
    for (size_t i = 0; i < tamano/2; i += tamElemento) {
        // Intercambiamos byte por byte del elemento completo
        for (size_t j = 0; j < tamElemento; j++) {
            temp = bytes[i + j];
            bytes[i + j] = bytes[tamano - tamElemento - i + j];
            bytes[tamano - tamElemento - i + j] = temp;
        }
    }
}

// Función para imprimir un vector de enteros
void imprimirVector(void* vector, size_t tamanoTotal, size_t tamanoElemento, const char* mensaje) {
    int* elementos = (int*)vector;
    size_t cantidadElementos = tamanoTotal / tamanoElemento;
    
    printf("%s", mensaje);
    for (size_t i = 0; i < cantidadElementos; i++) {
        printf("%d ", elementos[i]);
    }
    printf("\n");
}

int main() {
    // Ejemplo con un vector de enteros
    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t tamano = sizeof(numeros);
    
    imprimirVector(numeros, tamano, sizeof(int), "Vector original: ");
    
    invertirVector(numeros, tamano);
    
    imprimirVector(numeros, tamano, sizeof(int), "Vector invertido: ");
    
    return 0;
}

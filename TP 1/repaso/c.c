#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Función que convierte un número binario de 8 bits sin signo en una cadena
// que contiene sus dígitos en formato ASCII.
// El número se pasa como parámetro y se retorna una cadena con el resultado.
char* numToAscii(uint8_t num) {
    // Como el número máximo (255) tiene 3 dígitos, reservamos 4 bytes (3 dígitos + '\0')
    char *cadena = malloc(4 * sizeof(char));
    if (cadena == NULL) {
        return NULL;  // En caso de error en la asignación de memoria.
    }
    
    // Convertimos el número a cadena usando sprintf.
    sprintf(cadena, "%u", num);
    
    return cadena;
}

// Función para convertir una cadena binaria a un número decimal
uint8_t binarioADecimal(const char *binario) {
    uint8_t decimal = 0;
    
    while (*binario) {
        if (*binario == '0' || *binario == '1') {
            decimal = decimal * 2 + (*binario - '0');
        } else {
            // Si hay un carácter que no es 0 ni 1, retornamos un valor inválido
            return 255;  // Usamos 255 como indicador de error
        }
        binario++;
    }
    
    return decimal;
}

// Función para imprimir los caracteres individuales de una cadena
void imprimirCaracteresIndividuales(const char *cadena) {
    printf("Caracteres individuales: ");
    while (*cadena) {
        printf("\"%c\" ", *cadena);
        cadena++;
    }
    printf("\n");
}

int main(void) {
    char opcion;
    uint8_t numero;
    char entrada[9];  // 8 bits + terminador nulo
    
    printf("¿Desea ingresar un número en formato binario o decimal? (b/d): ");
    scanf(" %c", &opcion);
    
    if (opcion == 'b' || opcion == 'B') {
        printf("Ingrese un número binario (máximo 8 bits): ");
        scanf("%8s", entrada);
        
        // Convertimos el binario a decimal
        numero = binarioADecimal(entrada);
        
        // Verificamos si el número es válido (no tiene caracteres no binarios)
        if (numero == 255 && entrada[0] != '1') {
            printf("Entrada inválida. Solo se permiten 0s y 1s.\n");
            return 1;
        }
    } else if (opcion == 'd' || opcion == 'D') {
        int temp;
        printf("Ingrese un número decimal (0-255): ");
        scanf("%d", &temp);
        
        // Verificamos que el número esté en el rango válido
        if (temp < 0 || temp > 255) {
            printf("Entrada inválida. El número debe estar entre 0 y 255.\n");
            return 1;
        }
        
        numero = (uint8_t)temp;
    } else {
        printf("Opción inválida. Debe ingresar 'b' para binario o 'd' para decimal.\n");
        return 1;
    }
    
    // Llamamos a la función para obtener la cadena de dígitos ASCII.
    char *resultado = numToAscii(numero);
    if (resultado == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }
    
    printf("El valor decimal es: %u\n", numero);
    printf("Los dígitos ASCII del número son: %s\n", resultado);
    
    // Imprimimos los caracteres individuales
    imprimirCaracteresIndividuales(resultado);
    
    free(resultado);
    
    return 0;
}

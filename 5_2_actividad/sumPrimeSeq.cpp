/*
 * This program computes the sum of
 * prime numbers from 0 to input number
 * sequentially.
 * José Manuel García Zumaya
 * 2024-06-07
 */

#include<stdio.h>
#include<stdlib.h>
#include<cmath>

// Definición de una constante NUMBER con el valor 5000000.
#define DEFAULT_NUMBER 5000000

// Función que determina si un número es primo.
bool isPrime(int n) {
    // Si el número es menor que 2, no es primo.
    if (n < 2) return false;

    // Bucle para verificar divisibilidad desde 2 hasta la raíz cuadrada de n.
    for (int i = 2; i <= sqrt(n); i++) {
        // Si n es divisible por cualquier número en este rango, no es primo.
        if (n % i == 0) {
            return false;
        }
    }

    // Si pasa todas las pruebas de divisibilidad, es primo.
    return true;
}

int main(int argc, char *argv[]) {
    // Establece el valor predeterminado para NUMBER.
    int NUMBER = DEFAULT_NUMBER;

    // Si se proporciona un argumento, lo usa como valor para NUMBER.
    if (argc > 1) {
        NUMBER = atoi(argv[1]);
    }

    // Variable para contar la suma de números primos.
    long sum_counter = 0;

    // Bucle para iterar desde 0 hasta NUMBER.
    for (int i = 0; i < NUMBER; i++) {
        // Si el número i es primo, se añade a sum_counter.
        if (isPrime(i)) {
            sum_counter += i;
        }
    }

    // Imprime el valor final de la suma de todos los números primos encontrados.
    printf("FINAL VALUE: %ld\n", sum_counter);

    return 0;
}

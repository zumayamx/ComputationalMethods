/*
 * Adding into a single variable from multiple threads
 * Using a mutex to protect the variable
 *
 * Base code from Gilberto Echeverría
 *
 * José Manuel García Zumaya
 * 2024-06-07
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<cmath>

#define DEFAULT_NUMBER 5000000 

// Structure to send data to the threads
typedef struct {
    int id;
    long * counter_ptr;
    pthread_mutex_t * mutex_ptr;
    int inf_range;
    int sup_range;
} thread_data_t;

// Function declarations
void * thread_func(void *);

int main(int argc, char* argv[])
{
    // Establece el valor predeterminado para NUMBER.
    int NUMBER = DEFAULT_NUMBER;

    int num_threads = 4;
    int status;
    // Variable that will be used by all threads
    long counter = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    if (argc == 2) {
        num_threads = atoi(argv[1]);
    }

    if (argc == 3) {
        num_threads = atoi(argv[1]);
        NUMBER = atoi(argv[2]);
    }

    // Array to store the thread id's
    pthread_t tids[num_threads];
    // Array for the data to be sent to the threads
    thread_data_t data[num_threads];
    
    int limit = 0;
    int reminder = NUMBER % num_threads;
    int div = NUMBER / num_threads;
    
    for(int i=0; i<num_threads; i++) {
        // Fill the data in the structure
        data[i].id = i;
        data[i].counter_ptr = &counter;
        data[i].mutex_ptr = &mutex;

        //if (i == num_threads - 1) limit++;

        // Set a inferior limit begin in 0
        data[i].inf_range = limit;
        printf("The inf limit for t: %d is: %d\n", i, limit);
        
        // Sum a div range to limit
        limit += div - 1;

        // Sum the reminder to final range
        if (i == num_threads - 1) {
            limit++;
            limit += reminder;
        }

        data[i].sup_range = limit;
        printf("The sup limit for t: %d is: %d\n", i, limit);

        // Limit inf to next thread don't take the same limit sup like inferior
        limit++;

        // pthread_create arguments:
        // - pointer to id variable
        // - pointer to thread options
        // - pointer to function
        // - pointer to funtion argument
        status = pthread_create(&tids[i], NULL, &thread_func, &data[i]);
        if (status == -1) {
            printf("Unable to create threads\n");
            exit(1);
        }
        printf("Created thread %d with id: %lu\n", i, (unsigned long)tids[i]);
    }

    // Wait for the threads to finish
    for(int i=0; i<num_threads; i++) {
        status = pthread_join(tids[i], NULL);
        printf("Thread %d finished\n", i);
    }

    printf("FINAL VALUE: %ld (Expected %ld)\n", counter, (long) num_threads * NUMBER);


    return 0;
}

// Function to know if a number is prime or not
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

void * thread_func(void * args)
{
    thread_data_t * data = (thread_data_t *)args;
    long local_counter = 0;

    printf("This is thread %d\n", data->id);
    
    for (int x = data->inf_range; x <= data->sup_range; x++) {
        if (isPrime(x)){
            local_counter+=x;
        }
    }

    pthread_mutex_lock(data->mutex_ptr);
        *data->counter_ptr += local_counter;
    pthread_mutex_unlock(data->mutex_ptr);

    pthread_exit(NULL);
}
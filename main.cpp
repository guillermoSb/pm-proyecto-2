#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

double pi = 0;  // Variable que almacena el resultado final
pthread_mutex_t mutex;  // Variable mutex que bloquea el uso de pi

/**
 * @brief Calcula el valor de la serie de pi
 * 
 * @param params El numero de iteracion para la serie <int>
 * @return void* 
 */
void *series_pi(void *params);


int main() {
    pthread_t th[100];  // Declare the vector that contains all the threeads

    // * Create all the threads
    for (int i = 0; i < 100; i++)
    {
        // * Initialize the thread and search for errors
        if (pthread_create(&th[i], NULL, &series_pi, NULL) != 0) {
            printf("[ERROR] - Creating threads");
        }
        printf("Thread %d has started\n", i);
    }

    // * Wait for all the threads to finish
    for (int i = 0; i < 100; i++)
    {
        pthread_join(th[i], NULL);
    }

    // * Print the result
    printf("[RESULT] The value of PI is: %d\n", pi);


}

void *series_pi(void *params) {
    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
using namespace std;

double pi = 0;  // Variable que almacena el resultado final
pthread_mutex_t mutex;  // Variable mutex que bloquea el uso de pi

/**
 * @brief Calcula el valor de la serie de pi
 * 
 * @param params El numero de iteracion para la serie <int>
 * @return void* 
 */
void *series_pi(void *params);

// definicion del bloqueo (uno por region critica)
pthread_mutex_t lock;

int main() {     
    pthread_t th[100];  // Declare the vector that contains all the threeads


    //Inicializar variables
    int numberOfThread;
    //Pedir el numero de threads
    cout << "Ingrese el numero de hilos que desea (del 1 al 100): " ;
    cin >> numberOfThread;  


    // * Create all the threads
    for (int i = 0; i < numberOfThread; i++)
    {

         //Condicional por si incerta mal el hilo 
        if (numberOfThread > 100){
            pthread_mutex_lock(&lock);
            cout << "[ERROR] Ingrese un valor de hilos validos (Entre 0 y 100)";
        }

        // * Initialize the thread and search for errors
        if (pthread_create(&th[i], NULL, &series_pi, NULL) != 0) {
            printf("[ERROR] - Creando hilos");
        }
        printf("Hilo %d ha comenzado\n", i);   
            
    }

    // * Wait for all the threads to finish
    for (int i = 0; i < 100; i++)
    {
        pthread_join(th[i], NULL);
    }

    // * Print the result
    printf("[RESULTADO] El valor de PI es: %d\n", pi);


}

void *series_pi(void *params) {
    return 0;
}
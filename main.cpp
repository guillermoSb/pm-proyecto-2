#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cmath>
using namespace std;

double pi = 0; // Variable que almacena el resultado final
int stepForIntegral = 500000;
int numberOfThread;
pthread_mutex_t mutex; // Variable mutex que bloquea el uso de pi

/**
 * @brief Calcula el valor de la serie de pi
 * 
 * @param params El numero de iteracion para la serie <int>
 * @return void* 
 */
void *series_pi(void *params);

// definicion del bloqueo (uno por region critica)
pthread_mutex_t lock;

int main()
{
    pthread_t th[100]; // Declare the vector that contains all the threeads
                       //Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\nERROR: Mutex init failed");
        return 1;
    }

    //Inicializar variables

    //Pedir el numero de threads
    cout << "Ingrese el numero de hilos que desea (del 1 al 100): ";
    cin >> numberOfThread;

    //Condicional por si incerta mal la cantidad de hilos
    if (numberOfThread > 100 or numberOfThread < 1)
    {

        cout << "[ERROR] Ingrese un valor de hilos validos (Entre 1 y 100)";
    }
    else
    {
        // * Create all the threads
        for (int i = 0; i < numberOfThread; i++)
        {

            // * Initialize the thread and search for errors
            if (pthread_create(&th[i], NULL, &series_pi, (void *)i) != 0)
            {
                printf("[ERROR] - Creando hilos");
            }
            printf("Hilo %d ha comenzado\n", i);
        }
        // * Wait for all the threads to finish
        for (int i = 0; i < numberOfThread; i++)
        {

            pthread_join(th[i], NULL);
        }
        pthread_mutex_destroy(&lock);
        pi *= 4;
        // * Print the result
        printf("[RESULTADO] El valor de PI es: %f\n", pi);
    }
    return 0;
}

void *series_pi(void *params)
{
    //bloqueo del mutex
    double h = 1.0 / numberOfThread;
    int i = (int)params;
    double m = i * h;
    double k = (i + 1) * h;
    double step = (k - m) / (double)stepForIntegral;
    pthread_mutex_lock(&lock);
    for (int j = 0; j < stepForIntegral; j++)
    {
        pi += (1/(1+ m*m)) * step;
        m += (k - m) / (double)stepForIntegral;
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}
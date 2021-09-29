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
    //Initialize mutex
   if(pthread_mutex_init(&lock,NULL)!=0){
        printf("\nERROR: Mutex init failed");
        return 1;
    }

    //Inicializar variables
    int numberOfThread;
    //Pedir el numero de threads
    cout << "Ingrese el numero de hilos que desea (del 1 al 100): " ;
    cin >> numberOfThread;  
 

     //Condicional por si incerta mal la cantidad de hilos 
    if (numberOfThread > 100 or numberOfThread<1){

        cout << "[ERROR] Ingrese un valor de hilos validos (Entre 1 y 100)";
    }else{
              // * Create all the threads
        for (int i = 0; i < numberOfThread; i++)
        {

            // * Initialize the thread and search for errors
            if (pthread_create(&th[i], NULL, &series_pi, (void *) i) != 0) {
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
    
        // * Print the result
        printf("[RESULTADO] El valor de PI es: %d\n", pi);
        
    }


  return 0;


}

void* series_pi(void *params) {
    //bloqueo del mutex
    pthread_mutex_lock(&lock);
    long i;
    i= (long) params; 
    //Proceso del metodo
    pi+=i;

    //Desbloqueo del mutex
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}
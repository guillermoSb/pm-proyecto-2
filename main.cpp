#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include<bits/stdc++.h>


using namespace std;
void multi(int F[2][2], int M[2][2]); // Función auxiliar que multiplica 2 en matrices
void potencia(int F[2][2], int n); // Funcion calcula F subiendo a la potencia
int fibo(int n)
{
    int F[2][2] = { { 1, 1 }, { 1, 0 } };
     
    if (n == 0)
        return 0;
         
    potencia(F, n - 1);
     
    return F[0][0];
}
 
void multi(int F[2][2], int M[2][2])
{
    int x = F[0][0] * M[0][0] +
            F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] +
            F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] +
            F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] +
            F[1][1] * M[1][1];
     
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
 
void potencia(int F[2][2], int n)
{
    int i;
    int M[2][2] = { { 1, 1 }, { 1, 0 } };
     
    // n - 1 veces multiplo de las matrices
    for(i = 2; i <= n; i++)
        multi(F, M);
}


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
    
    //Eje. Fibonacci
    int n = 9;
    cout << " " <<  fibo(n);
     
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
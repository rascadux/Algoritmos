#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>
#include "p4.h"

#define INFINITO INT_MAX


void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


// COLA ----------------------------------------------------------------------
void crear_cola(cola *c) {
    c->tamano = 0;
    c->cabeza = 0;
    c->final = -1;
}

int cola_vacia(cola c) {
    return (c.tamano == 0);
}

void incrementar(int *x) { /* privado */
    if (++(*x) == TAM_MAX)
        *x = 0;
}

void insertar(tipo_elemento x, cola *c) {
    if (c->tamano == TAM_MAX) {
        printf("error: cola llena: %d\n", c->tamano);
        exit(EXIT_FAILURE);
    }
    c->tamano++;
    incrementar(&(c->final));
    c->vector[c->final] = x;
}

tipo_elemento primero(cola c) {
    if (cola_vacia(c)) {
        printf("error: cola vacia\n"); exit(EXIT_FAILURE);
    }
    return(c.vector[c.cabeza]);
}

tipo_elemento quitar_primero(cola *c) {
    tipo_elemento x;
    if (cola_vacia(*c)) {
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    c->tamano--;
    x = c->vector[c->cabeza];
    incrementar(&(c->cabeza));
    return x;
}

void imprimir_cola(cola *Cola) {
    int i;
    int pesos=0;
    if (cola_vacia(*Cola)){
        printf(" \n VACIA \n");
    } else {
        printf("\nAristas:  ");
        for (i = Cola->cabeza; i != Cola->final; i = (i + 1) % TAM_MAX) {
            printf("(%d, %d), ", Cola->vector[i].x, Cola->vector[i].y);
            pesos += Cola->vector[i].peso;
        }
        printf("(%d, %d)", Cola->vector[i].x, Cola->vector[i].y);
        pesos += Cola->vector[i].peso;
        printf("\nPeso:     %d\n", pesos);
    }
}

// MATRIZ --------------------------------------------------------------------
matriz crear_matriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL){
        return NULL;
    }
    for (i=0; i<n; i++){
        if ((aux[i] = malloc(n*sizeof(int))) == NULL){
            return NULL;
        }
    }
    return aux;
}

void inicializar_matriz(matriz m, int n) {
    /* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
    int i, j;
    for (i=0; i<n; i++){
        for (j=i+1; j<n; j++){
            m[i][j] = rand() % n + 1;
        }
    }

    for (i=0; i<n; i++){
        for (j=0; j<=i; j++){
            if(i==j){
                m[i][j] = 0;
            } else{
                m[i][j] = m[j][i];
            }
        }
    }
}

void liberar_matriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++){
        free(m[i]);
    }
    free(m);
}

void print_matriz(matriz m, int n) {
    int i,j;
    for (i = 0; i < n; i++) {
        printf("[");
        for (j = 0; j < n; j++) {
            printf(" %2i ",m[i][j]);
        }
        printf("]\n");
    }
}


//ALGORITMO ------------------------------------------------------------------

void prim (matriz m, int nodos, cola *aristas){
    /* calcular el árbol de recubrimiento mínimo devolviendo
    las aristas del arbol en la cola ’aristas’ */
    int min, i, j, x, k=0;
    arista a;
    int *masProximo = (int *) malloc(nodos*sizeof(int));
    int *distanciaMinima = (int *) malloc(nodos*sizeof(int));
    crear_cola(aristas);
    distanciaMinima[0] = -1;
    for(i = 1; i < nodos; i++){
        masProximo[i] = 0;
        distanciaMinima[i] = m[i][0];
    }
    for(x=1; x < nodos; x++){ // Bucle Voraz
        min = INFINITO;
        for(j = 1; j < nodos; j++){
            if((0 <= distanciaMinima[j]) && (distanciaMinima[j] < min)){
                min = distanciaMinima[j];
                k = j;
            }
        }
        a.x = masProximo[k];
        a.y = k;
        a.peso = m[a.x][a.y];

        insertar(a, aristas);
        distanciaMinima[k] = -1;
        for(j = 1; j < nodos; j++){
            if(m[j][k] < distanciaMinima[j]){
                distanciaMinima[j] = m[j][k];
                masProximo[j] = k;
            }
        }
    }
    free(masProximo);
    free(distanciaMinima);
}

void test_prim(cola *Cola){
    int i,j;
    matriz m;
    int temp[][5] = {{0,1,8,4,7},{1,0,2,6,5},{8,2,0,9,5},
                      {4,6,9,0,3},{7,5,5,3,0}};
    m = crear_matriz(5);
    for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++) m[i][j] = temp[i][j];
    }
    printf("Test de funcionamiento del algoritmo de Prim:\n");
    printf("Matriz de adyacencia del grafo:\n");
    print_matriz(m,5);
    prim(m, 5, Cola);
    imprimir_cola(Cola);
    liberar_matriz(m,5);
}

void test_prim2(cola *Cola){
    int i,j;
    matriz m;
    int temp[][4] = {{0,1,4,7},{1,0,2,8},{4,2,0,3},{7,8,3,0}};
    m = crear_matriz(4);
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++) m[i][j] = temp[i][j];
    }
    printf("Test de funcionamiento del algoritmo de Prim:\n");
    printf("Matriz de adyacencia del grafo:\n");
    print_matriz(m,4);
    prim(m, 4, Cola);
    imprimir_cola(Cola);
    liberar_matriz(m,4);
}

void test_prim3(cola *Cola){
    int i,j;
    matriz m;
    int temp[][7] =
    {{0,7,99,5,99,99,99},
    {7,0,8,9,7,99,99},
    {99,8,0,99,5,99,99},
    {5,9,99,0,15,6,99},
    {99,7,5,15,0,8,9},
    {99,99,99,6,8,0,11},
    {99,99,99,99,9,11,0}};
    m = crear_matriz(7);
    for (i = 0; i < 7; i++){
        for (j = 0; j < 7; j++) m[i][j] = temp[i][j];
    }
    printf("Test de funcionamiento del algoritmo de Prim:\n");
    printf("Matriz de adyacencia del grafo:\n");
    print_matriz(m,7);
    prim(m, 7, Cola);
    imprimir_cola(Cola);
    liberar_matriz(m,7);
}
// TIEMPOS -------------------------------------------------------------------

double medir_tiempo(int nodos, cola *Cola){
    double t_ini = 0.0; //tiempo de inicio
    double t_fin = 0.0; //tiempo de fin
    double t_test = 0.0; //tiempo del test
    double t_test_init = 0.0; //tiempo de test+inicializacion
    double t_init = 0.0; //tiempo de solo inicialización
    int i; //Iterador
    matriz m;
    m = crear_matriz(nodos);
    inicializar_matriz(m, nodos);
    t_ini = microsegundos();
    prim(m, nodos, Cola);
    t_fin = microsegundos();
    t_test = t_fin - t_ini;
    if (t_test < 500){
        printf("(*)");
        t_ini = microsegundos();
        for (i = 0; i < 1000; i++){
            inicializar_matriz(m, nodos);
            prim(m, nodos, Cola);
        }
        t_fin = microsegundos();
        t_test_init = t_fin-t_ini;
        t_ini = microsegundos();
        for (i = 0; i<1000; i++){

            inicializar_matriz(m, nodos);
        }
        t_fin = microsegundos();
        t_init = t_fin - t_ini;
        t_test = (t_test_init - t_init) / 1000;
    }
    liberar_matriz(m, nodos);
    return t_test;
}

void test_prim_aleatorio(cola *Cola){
    double tiempo = 0.0;
    int n; //Iterador
    printf("\nAlgoritmo de Prim:\n\n");
    printf("%12s%34s%23s", "n", "t(n)", "t(n)/n^1.7");
    printf("%22s%25s\n\n","t(n)/n^2", "t(n)/n^2.3");
    for (n=2; n<=1100; n*=2){
        tiempo = medir_tiempo(n, Cola);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n",
        n, tiempo, tiempo/(pow(n,1.6)), tiempo/(pow(n,2)), tiempo/(pow(n,2.4)));
    }
    printf("\n");

}



int main(){
    int i;
    inicializar_semilla();
    cola Micola;
    printf("TEST 1\n\n");
    test_prim(&Micola);
    printf("------------------------------");
    printf("----------------------------\n");
    test_prim2(&Micola);
    printf("------------------------------");
    printf("----------------------------\n");
    test_prim3(&Micola);
    printf("------------------------------");
    printf("----------------------------\n");
    printf("------------------------------");
    printf("----------------------------\n");
    for(i=0; i<3; i++){
         test_prim_aleatorio(&Micola);
         printf("------------------------------");
         printf("----------------------------\n");
    }

}

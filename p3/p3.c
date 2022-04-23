#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define ROJO     "\x1b[31m"
#define BRILLANTITO "\x1b[1m"
#define RESET   "\x1b[0m"

#define UMBRAL 100
#define MAX_V 1

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

void intercambiar(int v[], int pos1, int pos2){
     int aux;

     aux = v[pos1];
     v[pos1] = v[pos2];
     v[pos2] = aux;
}


void ord_ins(int v[], int n){
     int i, j, x;
     for(i=1; i<=n; i++){
          x = v[i];
          j = i-1;
          while(j>=0 && v[j] > x){
               v[j+1] = v[j];
               j = j-1;
          }
          v[j+1] = x;
     }
}

double medir_tiempo (void (*ordena)(int [], int),
void (*inicializar)(int [], int), int *alinear, int i){

     int j;
     int vector[i];
     double a1, b1, a2, b2;
     double tiempo1, tiempo2, tiempo;
     inicializar(vector, i); //genera vector de i numeros
     a1 = microsegundos();
     ordena(vector, i);
     b1 = microsegundos();
     tiempo = b1 - a1;
     if(tiempo < 500){
        printf("(*)");
        *alinear = 1;
        a1 = microsegundos();
        for(j=0; j<1000; j++){// Lo ejecutamos 1000 veces
          inicializar(vector, i);
          ordena(vector, i);
        }
        b1 = microsegundos();
        tiempo1 = b1 - a1;
        a2 = microsegundos();
        for(j=0; j<1000; j++){// Lo ejecutamos 1000 veces
          inicializar(vector, i);
        }
        b2 = microsegundos();
        tiempo2 = b2 - a2;
        tiempo = (tiempo1 - tiempo2)/1000;
     }
     return tiempo;
}

void mediana3 (int v[], int i, int j) {
     int k;

     k = (i + j) / 2 ;
     if(v[k] > v[j]) {
          intercambiar (v, k, j);
     }
     if(v[k] > v[i]) {
          intercambiar (v, k, i);
     }
     if(v[i] > v[j]){
          intercambiar (v, i, j);
     }
}


void rapida_aux (int v[], int izq, int der) { //Falta por hacer
     int pivote=0, i=0, j=0;
     if(izq + UMBRAL <= der){ /* UMBRAL >= 1 */
          mediana3(v, izq, der);/* el pivote está en ’izq’ y en ’der’ habrá */
                              /* un valor mayor o igual que el pivote */
          pivote = v[izq];
          i = izq;
          j = der;
          do{
               do{
                    i++;
               }while(v[i] < pivote);

               do{
                    j--;
               }while(v[j] > pivote);

               intercambiar (v, i, j);
          }while(j > i);

          intercambiar (v, i, j);
          intercambiar (v, izq, j);
          rapida_aux (v, izq, j-1);
          rapida_aux (v, j+1, der);
     }
}

void ord_rapida (int v[], int n) {
     rapida_aux(v, 0, n-1);
     if(UMBRAL > 1){
          ord_ins(v, n);
     }
}

void aleatorio(int v[], int n) {
     int i, m=2*n+1;
     for (i=0; i < n; i++)
          v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

void ascendente(int v [], int n) {
     int i;
     for (i=0; i < n; i++)
          v[i] = i;
}

void descendente(int v [], int n) {
     int i;
     for (i=0; i < n; i++)
          v[i] = n-i;
}

void listar_vector(int v[], int n){ //imprime el vector por pantalla
     for(int i=0; i<n; i++){
          if(i==n-1){ //para que no imprima la coma en el ultimo numero
               printf("%2d", v[i]);
          }else
          printf("%2d,  ", v[i]);
     }
}

int ordenado(int v[], int n){
     int i;
     for(i=0; i < n-1; i++){
          if(v[i] > v[i+1]){
               return 0;
          }
     }
     return 1;
}

void test(){
     int n = MAX_V;
     int v[n];

     printf("Ordenacion por insercion con inicializacion aleatoria\n");
     aleatorio(v, n);
     listar_vector(v, n); printf("\n");
     printf("ordenado?  %d\n", ordenado(v, n));
     printf("ordenando...\n");
     ord_rapida(v, n);
     listar_vector(v, n); printf("\n");

     if(ordenado(v, n)){
          printf("esta ordenado\n");
     } else printf("esta desordenado\n");

     printf("Ordenacion por insercion con inicializacion ascendente\n");
     ascendente(v, n);
     listar_vector(v, n); printf("\n");
     printf("ordenado?  %d\n", ordenado(v, n));
     printf("ordenando...\n");
     ord_rapida(v, n);
     listar_vector(v, n); printf("\n");
     if(ordenado(v, n)){
          printf("esta ordenado\n");
     } else printf("esta desordenado\n");

     printf("Ordenacion por insercion con inicializacion descendente\n");
     descendente(v, n);
     listar_vector(v, n); printf("\n");
     printf("ordenado?  %d\n", ordenado(v, n));
     printf("ordenando...\n");
     ord_rapida(v, n);
     listar_vector(v, n); printf("\n");
     if(ordenado(v, n)){
          printf("esta ordenado\n");
     } else printf("esta desordenado\n");

}

void test_ascendente(){
     double tiempos;
     int i;
     int alinear; //si imprime (*) necesitamos alinearlo de nuevo bien
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por quicksort con inicializacion ASCENDENTE: ");
     printf(ROJO BRILLANTITO "%36s = %d" RESET "\n\n\n", "UMBRAL",UMBRAL);

     if(UMBRAL == 1){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^1");
          printf("%17s%16s\n\n","t(n)/n^1.08", "t(n)/n^1.2");
     }else if(UMBRAL == 10){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.95");
          printf("%17s%16s\n\n","t(n)/n^1.13", "t(n)/n^1.35");
     }else if(UMBRAL == 100){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.95");
          printf("%17s%16s\n\n","t(n)/n^1.2", "t(n)/n^1.35");
     }

     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_rapida, ascendente, &alinear, i);
          if(UMBRAL == 1){
               n1 = pow(i, 1); n2 = pow(i, 1.08); n3 = pow(i, 1.2);
          }else if(UMBRAL == 10){
               n1 = pow(i, 0.95); n2 = pow(i, 1.13); n3 = pow(i, 1.35);
          }else if(UMBRAL == 100){
               n1 = pow(i, 1.05); n2 = pow(i, 1.2); n3 = pow(i, 1.35);
          }
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }
     }
}

void test_descendente(){
     double tiempos;
     int i;
     int alinear;
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por quicksort con inicializacion DESCENDENTE: ");
     printf(ROJO BRILLANTITO "%35s = %d" RESET "\n\n\n", "UMBRAL",UMBRAL);
     if(UMBRAL == 1){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^1");
          printf("%17s%16s\n\n","t(n)/n^1.08", "t(n)/n^1.2");
     }else if(UMBRAL == 10){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.95");
          printf("%17s%16s\n\n","t(n)/n^1.12", "t(n)/n^1.25");
     }else if(UMBRAL == 100){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.95");
          printf("%17s%16s\n\n","t(n)/n^1.16", "t(n)/n^1.35");
     }
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_rapida, descendente, &alinear, i);
          if(UMBRAL == 1){
               n1 = pow(i, 1); n2 = pow(i, 1.08); n3 = pow(i, 1.2);
          }else if(UMBRAL == 10){
               n1 = pow(i, 0.95); n2 = pow(i, 1.12); n3 = pow(i, 1.25);
          }else if(UMBRAL == 100){
               n1 = pow(i, 0.95); n2 = pow(i, 1.16); n3 = pow(i, 1.35);
          }
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }
     }
}

void test_aleatorio(){
     double tiempos;
     int i;
     int alinear;
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por quicksort con inicializacion ALEATORIA: ");
     printf(ROJO BRILLANTITO "%37s = %d" RESET "\n\n\n", "UMBRAL",UMBRAL);
     if(UMBRAL == 1){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.9");
          printf("%17s%16s\n\n","t(n)/n*log(n)", "t(n)/n^1.4");
     }else if(UMBRAL == 10){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.95");
          printf("%22s%13s\n\n","t(n)/n*log(n^0.97)", "t(n)/n^1.3");
     }else if(UMBRAL == 100){
          printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.7");
          printf("%22s%11s\n\n","t(n)/n*log(n^0.75)", "t(n)/n^1.2");
     }

     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_rapida, aleatorio, &alinear, i);
          if(UMBRAL == 1){
               n1 = pow(i, 0.9); n2 = i * log(i); n3 = pow(i,1.4);
          }else if(UMBRAL == 10){
               n1 = pow(i, 0.9); n2 = i * log(pow(i, 0.97)); n3 = pow(i, 1.3);
          }else if(UMBRAL == 100){
               n1 = pow(i, 0.9); n2 = i * log(pow(i, 0.75)); n3 = pow(i, 1.2);
          }

          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }
     }
}


void test_ascendente_ins(){
     double tiempos;
     int i;
     int alinear; //si imprime (*) necesitamos alinearlo de nuevo bien
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por insercion con inicializacion ASCENDENTE: \n\n");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.9");
     printf("%15s%16s\n\n","t(n)/n^1", "t(n)/n^1.10");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_ins, ascendente, &alinear, i);
          n1 = pow(i, 0.9); n2 = pow(i, 1); n3 = pow(i,1.10);
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }
     }
}

void test_descendente_ins(){
     double tiempos;
     int i;
     int alinear;
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por insercion con inicializacion DESCENDENTE: \n\n\n");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/(n^1.8/2)");
     printf("%15s%16s\n\n","t(n)/(n^2/2)", "t(n)/(n^2.2/2)");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_ins, descendente, &alinear, i);
          n1 = pow(i, 1.8)/2; n2 = pow(i, 2)/2; n3 = pow(i,2.2)/2;
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }
     }
}

void test_aleatorio_ins(){
     double tiempos;
     int i;
     int alinear;
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por insercion con inicializacion ALEATORIA: \n\n\n");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^1.8");
     printf("%15s%16s\n\n","t(n)/n^2", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_ins, aleatorio, &alinear, i);
          n1 = pow(i, 1.8); n2 = pow(i, 2); n3 = pow(i,2.2);
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }
     }
}

int main(void){
     int i;
     inicializar_semilla();
     test();



     for(i=0; i<3; i++){
          test_ascendente_ins();
          printf("--------------------------------------------------");
          printf("--------------------------------------------------\n");
          test_descendente_ins();
          printf("--------------------------------------------------");
          printf("--------------------------------------------------\n");
          test_aleatorio_ins();
          printf("--------------------------------------------------");
          printf("--------------------------------------------------\n");
          test_ascendente();
          printf("--------------------------------------------------");
          printf("--------------------------------------------------\n");
          test_descendente();
          printf("--------------------------------------------------");
          printf("--------------------------------------------------\n");
          test_aleatorio();
          printf("--------------------------------------------------");
          printf("--------------------------------------------------\n");
     }


}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


#define MAX_V 17

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

void ord_sel(int v[], int n){
     int i=0, j=0;
     int minj=0, minx=0;
     for(i=0; i < n; i++){
          minj=i; minx=v[i];
          for(j = i+1; j < n; j++){
               if(v[j] < minx){
                    minj=j; minx=v[j];
               }
          }
          v[minj] = v[i]; v[i] = minx;
     }
}

void ord_shell(int v[], int n){
     int incremento = n;
     int seguir = 0;
     int tmp=0;
     int i=0, j=0;
  while(incremento != 1){
    incremento = incremento/2;
    for(i = incremento; i < n; i++){
      tmp = v[i];
      j = i;
      seguir = 1;
      while(j-incremento >= 0 && seguir){
        if(tmp < v[j-incremento]){
          v[j] = v[j-incremento];
          j = j-incremento;
        }
        else seguir = 0;
      }
      v[j] = tmp;
    }
}
}

void listar_vector(int v[], int n){ //imprime el vector por pantalla
  for(int i=0; i<n; i++){
       if(i==n-1){ //para que no imprima la coma en el ultimo numero
            printf("%2d", v[i]);
       }else
       printf("%2d,  ", v[i]);
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

int ordenado(int v[]){
     for(int i=0; i<MAX_V; i++){
          if (v[i] > v[i+1]){
               return 0;
          }
     }
     return 1;
}


void test(){
     int v[MAX_V];

     //ORDENACION
     printf("ORD_SEL:\n\n");
     printf("Inicializacion aleatoria\n");
     aleatorio(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Ordenacion por Seleccion\n");
     ord_sel(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Inicializacion ascendente\n");
     ascendente(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Ordenacion por Seleccion\n");
     ord_sel(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Inicializacion descendente\n");
     descendente(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Ordenacion por Seleccion\n");
     ord_sel(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));

     //ORDENACION SHELL
     printf("-----------------------------------------------");
     printf("---------------------------------------------\n");
     printf("ORD_SHELL:\n\n");
     printf("Inicializacion aleatoria\n");
     aleatorio(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Ordenacion por Seleccion\n");
     ord_shell(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Inicializacion ascendente\n");
     ascendente(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Ordenacion por Seleccion\n");
     ord_sel(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Inicializacion descendente\n");
     descendente(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
     printf("Ordenacion por Seleccion\n");
     ord_shell(v, MAX_V);
     listar_vector(v, MAX_V); printf("\n");
     printf("ordenado?  %d\n", ordenado(v));
}

void test_ascendente(){
     double tiempos;
     int i;
     int alinear; //si imprime (*) necesitamos alinearlo de nuevo bien
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por seleccion con inicializacion ASCENDENTE: \n");
     printf("%s\n\n","Ord_sel");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^1.8");
     printf("%15s%16s\n\n","t(n)/n^2", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_sel, ascendente, &alinear, i);
          n1 = pow(i, 1.8); n2 = pow(i, 2); n3 = pow(i,2.2);
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
     printf("Ordenacion por seleccion con inicializacion DESCENDENTE: \n");
     printf("%s\n\n","Ord_sel");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^1.8");
     printf("%15s%16s\n\n","t(n)/n^2", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_sel, descendente, &alinear, i);
          n1 = pow(i, 1.8); n2 = pow(i, 2); n3 = pow(i,2.2);
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
     printf("Ordenacion por seleccion con inicializacion ALEATORIA: \n");
     printf("%s\n\n","Ord_sel");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^1.8");
     printf("%15s%16s\n\n","t(n)/n^2", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_sel, aleatorio, &alinear, i);
          n1 = pow(i, 1.8); n2 = pow(i, 2); n3 = pow(i,2.2);
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos, t1, t2, t3);
          }
     }
}

void test_ascendente_2(){
     double tiempos;
     int i;
     int alinear;
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por seleccion con inicializacion ASCENDENTE: \n");
     printf("%s\n\n","Ord_shell");
     printf("%12s%18s%18s", "n", "t(n)", "t(n)/n^0.7");
     printf("%18s%16s\n\n","t(n)/n^1.10", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_shell, ascendente, &alinear, i);
          n1 = pow(i, 0.7); n2 = pow(i, 1.10); n3 = pow(i,2.2);
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.9f%17.9f%17.9f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.9f%17.9f%17.9f\n", i, tiempos, t1, t2, t3);
          }
     }
}



void test_descendente_2(){
     double tiempos;
     int i;
     int alinear;
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por seleccion con inicializacion DESCENDENTE: \n");
     printf("%s\n\n","Ord_shell");
     printf("%12s%18s%18s", "n", "t(n)", "t(n)/n^0.7");
     printf("%18s%16s\n\n","t(n)/n^1.15", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_shell, descendente, &alinear, i);
          n1 = pow(i, 0.7); n2 = pow(i, 1.15); n3 = pow(i, 2.2);
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.9f%17.9f%17.9f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.9f%17.9f%17.9f\n", i, tiempos, t1, t2, t3);
          }
     }
}

void test_aleatorio_2(){
     double tiempos;
     int i;
     int alinear;
     double n1, n2, n3, t1, t2, t3;
     printf("Ordenacion por seleccion con inicializacion ALEATORIA: \n");
     printf("%s\n\n","Ord_shell");
     printf("%12s%18s%15s", "n", "t(n)", "t(n)/n");
     printf("%22s%15s\n\n","t(n)/n*log(n)^2", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
          alinear=0;
          tiempos = medir_tiempo(ord_shell, aleatorio, &alinear, i);
          n1 = i; n2 = i * pow((log(i)), 2); n3 = pow(i,1.25);
          t1 = tiempos/n1; t2 = tiempos/n2; t3 = tiempos/n3;
          if(alinear){
               printf("%10d%18.3f%17.9f%17.9f%17.9f\n", i, tiempos, t1, t2, t3);
          }else {
               printf("%13d%18.3f%17.9f%17.9f%17.9f\n", i, tiempos, t1, t2, t3);
          }
     }
}


int main(void){
     inicializar_semilla();
     test();
  
     printf("------------------------------------------------");
     printf("------------------------------------------------\n");
     test_ascendente();
     printf("------------------------------------------------");
     printf("------------------------------------------------\n");
     test_descendente();     
     printf("-----------------------------------------------");
     printf("-----------------------------------------------\n");
     test_aleatorio();
     printf("------------------------------------------------");
     printf("------------------------------------------------\n");
     test_ascendente_2();
     printf("------------------------------------------------");
     printf("------------------------------------------------\n");
     test_descendente_2();
     printf("-----------------------------------------------");
     printf("-----------------------------------------------\n");
     test_aleatorio_2();
     printf("-----------------------------------------------");
     printf("-----------------------------------------------\n");
     return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

void inicializar_semilla() {
srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

void aleatorio(int v[], int n) {
     int i, m=2*n+1;
     for (i=0; i < n; i++)
     v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

int sumaSubMax1(int v[], int n){
  int sumaMax = 0, estaSuma;
  int i, j;

  for(i=0; i<n; i++){
    estaSuma = 0;
    for(j=i; j<n; j++){
      estaSuma = estaSuma + v[j];
      if(estaSuma > sumaMax){
        sumaMax = estaSuma;
      }
    }
  }
  return sumaMax;
}

int sumaSubMax2(int v[], int n){
     int estaSuma = 0, sumaMax=0;
     int j;

     for(j=0; j<n; j++){
          estaSuma = estaSuma + v[j];
          if(estaSuma > sumaMax){
               sumaMax = estaSuma;
          } else if(estaSuma<0){
               estaSuma = 0;
          }
     }
     return sumaMax;
}

void listar_vector(int v[], int n){ //imprime el vector por pantalla
  int i;
  for(i=0; i<n; i++){
    printf("%2d  ", v[i]);
  }
}

void test1(){ //test para ver si funcionan sumaSubMax1 y sumaSubMax2
     int v1[] = {-9, 2, -5, -4, 6};
     int v2[] = {4, 0, 9, 2, 5};
     int v3[] = {-2, -1, -9, -7, -8};
     int v4[] = {9, -2, 1, -7, -8};
     int v5[] = {15, -2, -5, -4, 16};
     int v6[] = {7, -5, 6, 7, -7};
     printf("\ntest1:\n");
     printf("%33s%23s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
     printf("[ "); listar_vector(v1, 5); printf("]");
     printf("%31d%15d\n", sumaSubMax1(v1, 5), sumaSubMax2(v1, 5));
     printf("[ "); listar_vector(v2, 5); printf("]");
     printf("%31d%15d\n", sumaSubMax1(v2, 5), sumaSubMax2(v2, 5));
     printf("[ "); listar_vector(v3, 5); printf("]");
     printf("%31d%15d\n", sumaSubMax1(v3, 5), sumaSubMax2(v3, 5));
     printf("[ "); listar_vector(v4, 5); printf("]");
     printf("%31d%15d\n", sumaSubMax1(v4, 5), sumaSubMax2(v4, 5));
     printf("[ "); listar_vector(v5, 5); printf("]");
     printf("%31d%15d\n", sumaSubMax1(v5, 5), sumaSubMax2(v5, 5));
     printf("[ "); listar_vector(v6, 5); printf("]");
     printf("%31d%15d\n", sumaSubMax1(v6, 5), sumaSubMax2(v6, 5));

}




void test2(){
     int i, a, b;
     int v[9];

     printf("\ntest2:\n");
     printf("%33s%23s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
     for(i=0; i<10; i++){
          aleatorio(v,9);
          printf("[ "); listar_vector(v, 9); printf("]");
          a = sumaSubMax1(v, 9);
          b = sumaSubMax2(v, 9);
          printf("%15d%15d\n", a, b);
    }
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
     struct timeval t;
     if (gettimeofday(&t, NULL) < 0 ){
          return 0.0;
     }
     return (t.tv_usec + t.tv_sec * 1000000.0);
}



void test3_1(){
     double tiempos[6];
     int x=0, i;
     double n1, n2, n3, t1, t2, t3, a, b;
     int alinear;

     printf("\ntest3: \n\n");
     printf("%s\n\n","sumaSubMax1");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^1.8");
     printf("%15s%16s\n\n","t(n)/n^2", "t(n)/n^2.2");
     for(i=500; i<=32000; i=i*2){
       int vector[i];
       aleatorio(vector, i); //genera vectores aleatorios con i numeros
       a = microsegundos(); //tiempo pre-algoritmo
       sumaSubMax1(vector, i);
       b = microsegundos(); //tiempo post-algoritmo
       tiempos[x] = b - a; //tiempo que tardo el algoritmo
       n1 = pow(i, 1.8); n2 = pow(i, 2); n3 = pow(i,2.2);
       t1 = tiempos[x]/n1; t2 = tiempos[x]/n2; t3 = tiempos[x]/n3;
       alinear=0; //variable para que cuando imprima el (*), no se desalinee
       if(tiempos[x]<500){
          alinear=1; //ponemos la variable a 1
          printf("(*)");
          a = microsegundos();
          for(int j=0; j<1000; j++){// Lo ejecutamos 100 veces
            sumaSubMax1(vector, i);
          }
          b = microsegundos();// dividimos el tiempo resultante entre 1000
          tiempos[x] = (b-a)/1000;
          }
       if(alinear==1){  //Comprobamos si entro por el if en i=500
          printf("%10d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos[x], t1, t2, t3); //mueve la linea hacia la izquierda
       } else{
        printf("%13d%18.3f%17.6f%17.6f%17.6f\n", i, tiempos[x], t1, t2, t3);
       }
        x++;
     }
}

void test3_2(){
     double tiempos[6];
     int x=0, i;
     double n1, n2, n3, t1, t2, t3, a, b;

     printf("\n%s\n\n","sumaSubMax2");
     printf("%12s%18s%20s", "n", "t(n)", "t(n)/n^0.75");
     printf("%15s%16s\n\n","t(n)/n^0.99", "t(n)/n^1.15");
     for(i=500; i<=32000; i=i*2){ //igual que el anterior pero con el algoritmo sumaSubMax2
       int vector[i];
       aleatorio(vector, i);
       a = microsegundos();
       sumaSubMax2(vector, i);
       b = microsegundos();
       tiempos[x] = b - a;
       n1 = pow(i, 0.75); n2 = pow(i, 0.99); n3 = pow(i,1.15);
       t1 = tiempos[x]/n1; t2 = tiempos[x]/n2; t3 = tiempos[x]/n3;

          if(tiempos[x]<500){
            printf("(*)");
            a = microsegundos();
            for(int j=0; j<1000; j++){
              sumaSubMax2(vector, i);
            }
            b = microsegundos();
            tiempos[x] = (b-a)/1000;
          }
          // En este caso no hace falta modificar las lineas ya que siempre entrand todos por el if
        printf("%10d%18.4f%19.9f%17.10f%17.11f\n", i, tiempos[x], t1, t2, t3);

        x++;
     }
}


int main(void){
  inicializar_semilla();
  test1();
  test2();
  for(int i=0;i<4;i++){
    test3_1();
    test3_2();
    printf("\n--------------------------------------------");
    printf("--------------------------------------------\n");
  }
  return 0;

}

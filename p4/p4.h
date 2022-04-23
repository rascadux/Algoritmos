#ifndef __P4_H__
#define __P4_H__

#define TAM_MAX 3000

typedef int ** matriz;
typedef struct {
     int peso;
     int x, y;
} arista;

typedef arista tipo_elemento;

typedef struct {
     int cabeza, final, tamano;
     tipo_elemento vector[TAM_MAX];
} cola;


void crear_cola(cola *);
int cola_vacia(cola);
void insertar(tipo_elemento, cola *);
tipo_elemento quitar_primero(cola *);
tipo_elemento primero(cola);
void mostrar_cola(cola);

#endif

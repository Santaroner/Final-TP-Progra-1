#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
typedef struct
 {
     int idPractica;/// Campo único y autoincremental
     char nombre[30];
     int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
     int baja; /// 0 si está activo, 1 si está eliminado.
 } stPracticas;

stPracticas cargarUnaPractica();
int cargarPracticas(char ArchivoPracticas[30]);
void modificarPracticas(stPracticas practicas[20], int validos);
void mostrarPracticas(stPracticas practicas);
void mostrarUnaPractica(stPracticas practicasAux);

#endif // PRACTICAS_H_INCLUDED

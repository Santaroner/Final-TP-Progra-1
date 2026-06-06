#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED
#include "Utilities.h"
#include "Pacientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define ARCHIVO_PACIENTES "TestPacientes.bin"
#define ARCHIVO_PRACTICAS "Practicas.bin"
#define ARCHIVO_LABORATORIOS "Laboratorios.bin"

typedef struct
 {
     int idPractica;/// Campo único y autoincremental
     char nombre[30];
     int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
     int baja; /// 0 si está activo, 1 si está eliminado.
 } stPracticas;

stPracticas cargarUnaPractica();
void cargarPracticas(char ArchivoPracticas[30]);
void modificarPracticas(char ArchivoPractica[30]);
stPracticas menuModificarPractica(stPracticas unaPractica);
void mostrarPracticas(char ArchivoPracticas[30]);
void mostrarUnaPractica(stPracticas practicasAux);

#endif // PRACTICAS_H_INCLUDED

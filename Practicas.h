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

/// ----------------- E S T R U C T U R A  D E  P R A C T I C A S ----------------- ///
typedef struct
 {
     int idPractica;/// Campo único y autoincremental
     char nombre[30];
     int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
     int baja; /// 0 si está activo, 1 si está eliminado.
 } stPracticas;

/// ---------------------- C A R G A  D E  P R A C T I C A S ---------------------- ///
int generaId();
void ingreseNombre(char nombre[30]);
int ingreseCosto(int costo);
int ingreseBaja(int baja);
stPracticas cargarUnaPractica();
void cargarPracticas(char ArchivoPracticas[30]);

/// ------ C R E A C I O N  Y  C A R G A  D E  A R R E G L O  D I N A M I C O ------- ///
stPracticas *crearArregloDinamicoPracticas(char ArchivoPracticas[30]);
void traspasoDatos(stPracticas *arregloDinamicoPracticas, int cantPracticas);

/// --------------------------- V A L I D A C I O N E S -------------------------- ///
int buscarNombreIgualPractica(char nombrePractica[30], char ArchivoPracticas[30]);

/// --------------------- C O N T E O  D E  P R A C T I C A S -------------------- ///
int contarPracticas(char ArchivoPracticas[30]);

/// --------------------- M U E S T R A  D E  P R A C T I C A S -------------------- ///
void mostrarPracticas(char ArchivoPracticas[30]);
void mostrarUnaPractica(stPracticas practicasAux);
void mostrarPracticasAlta(char archivoPracticas[30]);
void mostrarPracticasBaja(char archivoPracticas[30]);
void mostrarUnaPracticaAlta(stPracticas practicasAux);
void mostrarUnaPracticaBaja(stPracticas practicasAux);

/// --------------------- M O D I F I C A R  P R A C T I C A S -------------------- ///
void modificarPracticas(char ArchivoPractica[30]);
stPracticas menuModificarPractica(stPracticas unaPractica);

/// ----------- A L T A  Y  B A J A  L O G I C A  D E  P R A C T I C A S ---------- ///
void darDeBajaPracticas(char ArchivoPracticas[30]);
void darDeAltaPracticas(char ArchivoPracticas[30]);
stPracticas darDeAltaUnaPractica(stPracticas unaPractica);
stPracticas darDeBajaUnaPractica(stPracticas unaPractica);

#endif // PRACTICAS_H_INCLUDED

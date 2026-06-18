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
void cargarPracticas(char ArchivoPracticas[]);
void cargarPracticaEnArchivo(char ArchivoPracticas[], stPracticas unaPractica, int *validosArregloPracticas);

/// ------ C R E A C I O N  Y  C A R G A  D E  A R R E G L O  D I N A M I C O ------- ///
stPracticas *cargarArregloDinamicoPracticas(char ArchivoPracticas[], stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas);
void traspasoDatos(stPracticas *arregloDinamicoPracticas, char ArchivoPracticas[], int *validosArregloPracticas);
void muestraArreglo(stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas);

/// --------------------------- V A L I D A C I O N E S -------------------------- ///
int buscarNombreIgualPractica(char nombrePractica[30], char ArchivoPracticas[]);

/// --------------------- C O N T E O  D E  P R A C T I C A S -------------------- ///
int contarPracticas(char ArchivoPracticas[]);

/// --------------------- M U E S T R A  D E  P R A C T I C A S -------------------- ///
void mostrarPracticas(stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas);
void mostrarPracticasDesdeArchivo(char ArchivoPracticas[]);
void mostrarUnaPractica(stPracticas practicasAux);
void mostrarPracticasAlta(char archivoPracticas[]);
void mostrarPracticasBaja(char archivoPracticas[]);
void mostrarUnaPracticaAlta(stPracticas practicasAux);
void mostrarUnaPracticaBaja(stPracticas practicasAux);

/// --------------------- M O D I F I C A R  P R A C T I C A S -------------------- ///
void modificarPracticas(char ArchivoPracticas[]);
stPracticas menuModificarPractica(stPracticas unaPractica);
void modificarPracticaEnArchivo(char ArchivoPracticas[], stPracticas unaPractica, int posicion);

/// ----------- A L T A  Y  B A J A  L O G I C A  D E  P R A C T I C A S ---------- ///
void darDeBajaPracticas(char ArchivoPracticas[]);
void darDeAltaPracticas(char ArchivoPracticas[]);
stPracticas darDeAltaUnaPractica(stPracticas unaPractica);
stPracticas darDeBajaUnaPractica(stPracticas unaPractica);
int verificarAltas(char ArchivoPracticas[]);
int verificarBajas(char ArchivoPracticas[]);

/// ------------------- B U S Q U E D A  D E  P R A C T I C A S ------------------- ///
void buscarPracticasPorNombre();
void buscarPracticaPorNombre(char nombrePractica[30], char ArchivoPracticas[]);
void menuBusquedaPorNombre(stPracticas unaPractica, int posicion);

#endif // PRACTICAS_H_INCLUDED

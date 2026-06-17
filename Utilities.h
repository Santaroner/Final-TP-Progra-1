#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include "Pacientes.h"
#include "Practicas.h"
#include "Laboratorios.h"
#include <ctype.h>
#include <string.h>
#define ARCHIVO_PACIENTES "TestPacientes.bin"
#define ARCHIVO_PRACTICAS "Practicas.bin"
#define ARCHIVO_LABORATORIOS "Laboratorios.bin"


int GetIDPacientes (); /// Autoincremental ID pacientes
int compararIDLP (int num);
int compararIDLPrac (int num);
int getIDValids(FILE *archi);
int getIDVPacientes();
int getIDVPracticas();
int getIDVLaboratorio();
void borrarSaltoDeLinea(char cadena[]);
void limpiarBuffer();
char * primerLetraMayuscula (char cadena[]);
FILE * abrirArchivo (char nombreArchivo[],char modo[]);

/// Validaciones
int ingresarSoloLetrasSinEspacios (char palabra[]);
int ingresarSoloLetras (char palabra[]);
int ingresarSoloNumerosEnArreglo (char numeros[]);
int ingresarSoloNumeros (int numeros); ///
int ingresarEntero();
int ingresarEnteroMinMax(int min, int max); /// Si ingresa un dato que no sea numero no retorna 1, solo para numeros ingresados con scanf, no con strings en fgets
char ingresoSoloSNEnScan(char a, char b);
char ingresoSoloLetraEnScan(); /// Si ingresa un dato que no no sea letra no retorna 1

/// TESTEO DE ARCHIVOS
void resetearArchivos();/// Vacia los 3 archivos
void cargarPacientesAB(); /// Carga los pacientes
void cargarPracticaTest(); /// Carga practicas
void cargarLaboTest(); /// carga laboratorios

#endif // UTILITIES_H_INCLUDED

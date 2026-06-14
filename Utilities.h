#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include "Pacientes.h"
#include "Practicas.h"
#include "Laboratorios.h"
#include <ctype.h>
#include <string.h>
int GetIDPacientes (); /// Autoincremental ID pacientes
int compararIDLP (int num);
int compararIDLPrac (int num);
int getIDValids(FILE *archi);
int getIDVPacientes();
int getIDVPracticas();
int getIDVLaboratorio();
void borrarSaltoDeLinea(char cadena[]);
char * primerLetraMayuscula (char cadena[]);
FILE * abrirArchivo (char nombreArchivo[],char modo[]);

/// Validaciones
int ingresarSoloLetrasSinEspacios (char palabra[]);
int ingresarSoloNumerosEnArreglo (char numeros[]);
int ingresarSoloNumeros (int numeros); ///

#endif // UTILITIES_H_INCLUDED

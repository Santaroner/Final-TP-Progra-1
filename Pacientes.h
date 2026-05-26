#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Utilities.h"
//extern APacientes[];
typedef struct
 {
     int idPaciente; /// autoincremental
     char nombre [30];
     char apellido[30];
     char dni[10];
     char movil[12];
     int eliminado; /// 0 si está activo, 1 si está eliminado.
 } stPaciente;
void cargarPacientes(); /// Bucle para cargar pacientes
void cargaPaciente();  /// Llama a las diferentes funciones con validaciones y integra los datos en el archivo

/// -------------------------- C A R G A   P A C I E N T E S -------------------------------------------------------- ///
 int cargarIDPaciente ();
 void cargarNombrePaciente(char nombre[30]);
 void cargarApellidoPaciente(char apellido[]);
 void cargarDNIPaciente(char DNI[]);
 void cargarMovilPaciente(char movil[]);
 void cargarEstadoPaciente();
/// -------------------------- M U E S T R A  //// V A L I D O S  -------------------------------------------------------- ///
 void mostrarPacientes(stPaciente *pacientes,int validos);
 int mostrarArchivo();
 extern stPaciente *pacientes;
 extern validos;

#endif // PACIENTES_H_INCLUDED

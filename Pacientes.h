#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Utilities.h"
#include "Laboratorios.h"

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

/// --------------------------------------------------------- C A R G A   P A C I E N T E S -------------------------------------------------------- ///
 int cargarIDPaciente ();
 void cargarNombrePaciente(char nombre[30]);
 void cargarApellidoPaciente(char apellido[]);
 void cargarDNIPaciente(char DNI[]);
 void cargarMovilPaciente(char movil[]);
 int cargarEstadoPaciente();
/// ------------------------------------------------------- M U E S T R A  //// V A L I D O S  -------------------------------------------------------- ///
 void mostrarPacientes(stPaciente *pacientes,int validos);
 int validarDNI (char DNI[]);
 int busquedaPorDNIDOS (char DNI[]); /// BORRAR
 int mostrarArchivo();
 void mostrarEliminados ();
 extern stPaciente *pacientes;
 extern int validos;
 /// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///

void buscarPaciente(stPaciente *pacientes, int validos);
void menuModificarPaciente (int pos);
void cambiarNombrePaciente(int pos);
void cambiarApellidoPaciente(int pos);
void cambiarMovilPaciente(int pos);
void cambiarDNIPaciente(int pos);
void bajaPaciente();
void guardarPaciente (stPaciente paciente ,int pos );

/// ----------------------------------------------------- B U S Q U E D A      P A C I E N T E S  ----------------------------------------------------- ///
void busquedaPaciente ();
int busquedaPorDNI (char DNI[]);
int busquedaPorApellido (char apellido[]);
void altaViejoPaciente ();
int confirmarBajaPaciente (char nombre[], char apellido[]);

/// ----------------------------------------------------- O R D E N A M I E N T O /// A R R E G L O --- D I N A M I C O -------------------------------------------------- ///
stPaciente * activosADinamicos (int *validosADP);
stPaciente * creandoAD (stPaciente paciente, int *validosADP,stPaciente *ADP);
void mostrarADP (stPaciente *aux, int *validosADP);
int findMinorChar(stPaciente * ADR, int validosADP, int posicion);
void ordenamientoSeleccionChar(stPaciente *ADR,int validosADR);

/// ----------------------------------------  -------------------------------------------------- ///

void menuMostrarLaboratoriosPorPaciente ();
void laboratoriosPorPacienteID ();
//void mostrarLaboratoriosPorPacientes (int ID);
void mostrarLaboratoriosUnPaciente (char DNI[]);
void mostrarUnLaboratorio (char nombre[], char practica[], int precio, int anio , int mes, int dia,int id); /// Devuelve el nombre de la practica a mostrarLaboratoriosPorPaciente
void mostrarTodosLaboratoriosPorPaciente ();


/// ----- Carga de archivos para test
void cargarPacientesAB(); /// Heroes
void cargarPracticaTest(); /// Carga 15 practicas
void cargarLaboTest(); /// Carga 40 laboratorios


/// ORDENAMIENTO LABS POR FECHA
stLaboratorios * arregloDinamicoLaboratoriosPorFecha (int *validosOrdenamiento);
stLaboratorios * asignarMemoriaLaboratoriosPorFecha (stLaboratorios * arregloOrdenamiento, stLaboratorios lab, int pos);
int fechaAEntero (stLaboratorios lab);
void ordenamientoSeleccionFecha(stLaboratorios arreglo[], int validos);
int findMinorFecha(stLaboratorios arreglo[], int validos, int posicion);
void ordenamientoSeleccionFecha(stLaboratorios arreglo[], int validos);


#endif // PACIENTES_H_INCLUDED

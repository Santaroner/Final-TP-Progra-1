#ifndef LABORATORIOS_H_INCLUDED
#define LABORATORIOS_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
#include "Practicas.h"

typedef struct
 {
     int idLab; /// campo único y autoincremental
     int idPaciente;
     int anio;
     int mes;
     int dia; /// 1 a ... dependiendo el mes.
     int practicaRealizada; /// Validar que la practica existe
     int baja; /// 0 si está activo, 1 si está eliminado.
 } stLaboratorios;


 /// --------------------------------------------------------- C A R G A   P A C I E N T E S -------------------------------------------------------- ///
 void cargarLaboratorio(stLaboratorios *lab);
 stLaboratorios * cargarLaboratorios();

 /// ------------------------------------------------------- M U E S T R A  //// V A L I D A R -------------------------------------------------------- ///

 void mostrarLaboratorios(stLaboratorios *laboratorios,int validosL); /// muestra
 void mostrarLaboratoriosArchivo(); /// muestra
  int validarAnio();
 int validarMes();
 int validarDia(int mes);

 /// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///

 void bajaLaboratorio(); /// baja logica
 void modificarLaboratorio();
 void procesoMenuModificar(stLaboratorios *lab);
 void consultarLaboratorio();
 void encontrarDatosPaciente (int id, char nombre[], char apellido[]);


 /// ----------------------------------------------------- O R D E N A M I E N T O /// M U E S T R A -------------------------------------------------- ///
stLaboratorios * arregloDinamicoLaboratoriosPorFecha (int *validosOrdenamiento);
stLaboratorios * asignarMemoriaLaboratoriosPorFecha (stLaboratorios * arregloOrdenamiento, stLaboratorios lab, int pos);
int fechaAEntero (stLaboratorios lab);
void ordenamientoSeleccionFecha(stLaboratorios arreglo[], int validos);
int findMinorFecha(stLaboratorios arreglo[], int validos, int posicion);
void ordenamientoSeleccionFecha(stLaboratorios arreglo[], int validos);

void buscarPracticasRealizadas(int practicaID, char practicaRealizada[],int *precio);
void mostrarLaboratoriosOrdenadosPorfecha (stLaboratorios arreglo[],int validos);
int buscandoIDPractica();


 int buscandoIDPacientes(); /// rafa probando busca id
void mostrarPracticasSanti ();

#endif // LABORATORIOS_H_INCLUDED

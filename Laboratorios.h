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


 void cargarLaboratorio(stLaboratorios *lab);
 stLaboratorios * cargarLaboratorios();
 //int validarFecha(int anio, int mes, int dia);
 void mostrarLaboratorios(stLaboratorios *laboratorios,int validosL); /// muestra
 void mostrarLaboratoriosArchivo(); /// muestra
 void bajaLaboratorio(); /// baja logica

 void modificarLaboratorio();
 void consultarLaboratorio();
 void encontrarDatosPaciente (int id, char nombre[], char apellido[]);

 /// Validar fecha
 int validarAnio();
 int validarMes();
 int validarDia(int mes);

 /// ORDENAMIENTO LABS POR FECHA
stLaboratorios * arregloDinamicoLaboratoriosPorFecha (int *validosOrdenamiento);
stLaboratorios * asignarMemoriaLaboratoriosPorFecha (stLaboratorios * arregloOrdenamiento, stLaboratorios lab, int pos);
int fechaAEntero (stLaboratorios lab);
void ordenamientoSeleccionFecha(stLaboratorios arreglo[], int validos);
int findMinorFecha(stLaboratorios arreglo[], int validos, int posicion);
void ordenamientoSeleccionFecha(stLaboratorios arreglo[], int validos);

void buscarPracticasRealizadas(int practicaID, char practicaRealizada[],int *precio);
void mostrarLaboratoriosOrdenadosPorfecha (stLaboratorios arreglo[],int validos);
int buscandoIDPractica() ;


 int buscandoIDPacientes(); /// rafa probando busca id
 void muestraTSP();
void mostrarPracticasSanti ();

#endif // LABORATORIOS_H_INCLUDED

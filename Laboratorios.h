#ifndef LABORATORIOS_H_INCLUDED
#define LABORATORIOS_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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


 void buscandoIDPacientes(); /// rafa probando busca id
 void muestraTSP();
void mostrarPracticasSanti ();

#endif // LABORATORIOS_H_INCLUDED

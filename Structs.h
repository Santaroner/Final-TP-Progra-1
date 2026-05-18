#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED /// DEJAR ESTO COMO ESTA
 typedef struct
 {
     int idPaciente; /// autoincremental
     char nombre [30];
     char apellido[30];
     char dni[10];
     char movil[12];
     int eliminado; /// 0 si está activo, 1 si está eliminado.
 } stPaciente;

 typedef struct
 {
     int idLab; /// campo único y autoincremental
     int idPaciente;
     int anio;
     int mes;
     int dia; /// 1 a ... dependiendo el mes.
     int practicaRealizada;
     int baja; /// 0 si está activo, 1 si está eliminado.
 } stLaboratorios;

 typedef struct
 {
     int idPractica;/// Campo único y autoincremental
     char nombre[30];
     int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
     int baja; /// 0 si está activo, 1 si está eliminado.
 } stPracticas;


#endif // STRUCTS_H_INCLUDED NO TOCAR NADA

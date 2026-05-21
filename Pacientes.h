#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED

typedef struct
 {
     int idPaciente; /// autoincremental
     char nombre [30];
     char apellido[30];
     char dni[10];
     char movil[12];
     int eliminado; /// 0 si está activo, 1 si está eliminado.
 } stPaciente;


#endif // PACIENTES_H_INCLUDED

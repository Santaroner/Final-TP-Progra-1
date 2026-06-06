#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include "Pacientes.h"
#include "Practicas.h"
#include "Laboratorios.h"
int GetIDPacientes (); /// Autoincremental ID pacientes
int compararIDLP (int num);
int getIDValids(FILE *archi);
int GetIdLaboratorios();
int getIDVPacientes();
int getIDVPracticas();

#endif // UTILITIES_H_INCLUDED

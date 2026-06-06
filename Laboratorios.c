#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
#include "Practicas.h"
stLaboratorios *laboratorios = NULL;
int validos = 0;

// idLab - idPac - año - mes - dia - idPrac - baja o alta

// - - - - - - Carga Lab

void cargarLaboratorio(stLaboratorios *lab) /// Duda si agregar pac y prac.
{
   do {
    printf("Ingrese año: ");
    scanf("%d", &lab->anio);
    printf("Ingrese mes (1-12): ");
    scanf("%d", &lab->mes);
    printf("Ingrese dia: ");
    scanf("%d", &lab->dia);
    } while (!validarFecha(lab->anio, lab->mes, lab->dia)); /// ! pide mientras no sea valida.

    printf("Ingrese ID del paciente: ");
//    scanf("%d", &lab->); /// func

    printf("Ingrese ID de la practica: ");
//    scanf("%d", &lab->); /// func

    lab->idLab = GetIdLaboratorios();
    printf("ID asignado: %d\n", lab->idLab);

    lab->baja = 0;
}

void cargarLaboratorios()
{
    char seguir = 's';
    while (tolower(seguir) == 's')
    {
        stLaboratorios *aux = realloc(laboratorios, (validos + 1) * sizeof(stLaboratorios));
        if (aux != NULL)
        {
            laboratorios = aux;
            cargarLaboratorio(&laboratorios[validos]);
            validos++;
            printf("Laboratorio cargado correctamente. Total: %i\n", validos);
        }
        else
        {
            printf("Error al asignar memoria.\n");
        }
        printf("Desea cargar otro laboratorio? (s/n): ");
        scanf(" %c", &seguir);
    }
    printf("Carga finalizada.\n");
}

int validarFecha(int anio, int mes, int dia)
{
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // el 0 para que el primer mes sea 1ero

    if (anio < 2000 || anio > 2026) return 0; /// sale si invalido
    if (mes < 1 || mes > 12) return 0;  /// sale si invalido
    if (dia < 1 || dia > diasPorMes[mes]) return 0;  /// sale si invalido

    return 1;
}


int GetIdLaboratorios()
{
    static int aux = 0;
    aux++;
    return aux;
}





void buscandoIDPacientes() /// rafa probando busca id - - - - - - - funcion en utilities
{
    int newID = 0;
    int aux;
    printf("Ingrese el ID a buscar:\”");
    scanf("%i",&newID);
    compararIDLP(newID);
    if ( aux == 0)
    {
        printf("El id ha sido encontrado.\n”");
    }
    else if (aux == 1)
    {
        printf("El ID no existe. Si desea crear uno vaya al apartado pacientes.\n");
    }
}

void muestraTSP () /// TEST SANTI PACIENTES
{
    printf("entra");
    stPaciente aux;
    FILE *archi = fopen ("PacientesSanti.bin","rb");
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0 )
    {
        printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
               aux.idPaciente,
               aux.nombre,
               aux.apellido,
               aux.dni,
               aux.movil);
    }
    fclose(archi);
}

void mostrarPracticasSanti ()
{
    FILE * archi = fopen ("PracticasSanti.bin","rb");
    if (archi == NULL) printf("El archivo no se pudo abrir\n");
    stPracticas aux;
    while (fread(&aux,sizeof(stPracticas),1,archi) > 0)
    {
        printf("idPractica: %i\n", aux.idPractica);
        printf("Nombre: %s\n", aux.nombre);
        printf("Costo: %i\n", aux.costo);
        printf("Baja (0 activo, 1 baja): %i\n", aux.baja);
    }
    fclose(archi);
}

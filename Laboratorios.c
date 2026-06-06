#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
#include "Practicas.h"
stLaboratorios *laboratorios = NULL;
int validosL = 0;

// idLab - idPac - año - mes - dia - idPrac - baja o alta

// - - - - - - Carga Lab

void cargarLaboratorio(stLaboratorios *lab) /// Duda si agregar pac y prac.
{

//    printf("Ingrese ID del paciente: ");
//    scanf("%d", &lab->); /// func

//    printf("Ingrese ID de la practica: ");
//    scanf("%d", &lab->); /// func
    char seguir = 's';
    lab->idLab = getIDVLaboratorio();
    printf("ID asignado: %d\n", lab->idLab);

//    int aux=buscandoIDPacientes();
//    printf("%d", &aux);
    int aux = 0;
    while (seguir == 's')
    {
        aux = validarAnio();
        lab->anio = aux;
        aux = validarMes();
        lab ->mes = aux;
        aux = validarDia(aux);
        lab ->dia = aux;

        printf("Presione 's' para continuar:\n");
        scanf(" %c",&seguir);
    }



//    printf("Ingrese ID del paciente: ");
//    scanf("%d", &lab->); /// func

//    printf("Ingrese ID de la practica: ");
//    scanf("%d", &lab->); /// func

    lab->baja = 0;
    printf("Mostrar listado?\n");
    int muestra = 0;
    if (muestra == 0)
    {
        mostrarLaboratorios(laboratorios,validosL);
    }
}

stLaboratorios * cargarLaboratorios()
{
    char seguir = 's';
    stLaboratorios *aux;
    while (tolower(seguir) == 's')
    {
        aux = realloc(laboratorios, (validosL + 1) * sizeof(stLaboratorios));
        if (aux != NULL)
        {
            laboratorios = aux;
            cargarLaboratorio(&laboratorios[validosL]);
            validosL++;
            printf("Laboratorio cargado correctamente. Total: %i\n", validosL);
        }
        else
        {
            printf("Error al asignar memoria.\n");
        }
        printf("Desea cargar otro laboratorio? (s/n): ");
        scanf(" %c", &seguir);
    }
    printf("Carga finalizada.\n");

    return aux;
}

int validarFecha(int anio, int mes, int dia)
{
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // el 0 para que el primer mes sea 1ero

    if (anio < 2000 || anio > 2026) return 0; /// sale si invalido
    if (mes < 1 || mes > 12) return 0;  /// sale si invalido
    if (dia < 1 || dia > diasPorMes[mes]) return 0;  /// sale si invalido

    return 1;
}

int validarAnio()
{
    int flag =1 ;
    int aux = 0;
    do
    {
    printf("Ingrese el anio: ");
    scanf("%d", &aux);
    if (aux < 1990 || aux > 2026)
        printf("Año equivocado, recuerde (entre 1990 y 2026) ");
    else
        {
            printf("Anio %d", aux);
            flag = 0; /// si se ingreso el año correctmante, flag  0
            return aux;
        }
    }while (flag != 0);


}

int validarMes()
{
    int flag = 1;
    int aux = 0;
    do
    {
    printf("Ingrese el mes: ");
    scanf("%d", &aux);
    if (aux < 1 || aux > 12)
        printf("Error, recuerde entre 1 y 12 ");
    else
        printf("Mes %d", aux);
    } while (aux < 1 || aux > 12);
     return aux;
}

int validarDia(int mes)
{
    int dia;
    int flag = 1;

    do
    {
        printf("Ingrese el dia: ");
        scanf("%d", &dia);
    /// ---------------------------------------------------------------------------------------------------------------------------------------
       if (mes == 1)
    {
        if (dia <= 31 && dia >= 1 )
        {
            flag = 0;
            return dia;
        }
        else printf("Enero tiene 31 dias.\n");
    }

    if (mes == 2)
    {
        if (dia <= 28 && dia >= 1 )
        {
            flag = 0;
            return dia;
        }
        else printf("Febrero tiene 28 dias\n");
    }
    if (mes == 3)
    {
        if (dia <= 31 && dia >=1)
        {
            flag = 0;
            return dia;
        }
        else printf("Marzo tiene 31 dias\n");
    }
    if (mes == 4)
    {
        if (dia <= 30 && dia >= 1 )
        {
            flag = 0;
            return dia;
        }
        else printf("Abril tiene 30 dias\n");
    }
     if (mes == 5)
     {
         if (dia <= 31 && dia >= 1 )
         {
             flag = 0;
             return dia;
         }
        else printf("Mayo tiene 31 dias\n");
     }
     if (mes == 6)
     {
         if (dia <= 30 && dia >= 1 )
         {
             flag = 0;
             return dia;
         }
         else printf("Junio tiene 30 dias\n");
     }
     if (mes == 7)
     {
         if (dia <= 31 && dia >= 1)
         {
             flag = 0;
             return dia;
         }
         else printf("Julio tiene 31 dias\n");
     }
     if (mes == 8)
     {
         if (dia <= 31 && dia >= 1)
         {
             flag = 0;
             return dia;
         }
         else printf("Agosto tiene 31 dias\n");
     }
     if (mes == 9)
     {
         if (dia <= 30 && dia >= 1)
         {
             flag = 0;
             return dia;
         }
         else printf("Septiembre tiene 30 dias\n");
     }
     if (mes == 10)
     {
         if (dia <= 31 && dia >= 1)
         {
             flag = 0;
             return dia;
         }
         else printf("Octubre tiene 31 dias\n");
     }
     if (mes == 11)
     {
         if (dia <= 30 && dia >= 1)
         {
             flag = 0;
             return dia;
         }
         else printf("Noviembre tiene 30 dias\n");
     }
     if (mes == 12)
     {
         if (dia <= 31 && dia >= 1)
         {
             flag = 0;
             return dia;
         }
         else printf("Diciembre tiene 31 dias\n");
     }
    } while (flag != 0);


}


void mostrarLaboratorios(stLaboratorios *laboratorios,int validosL)
{
    for(int i = 0; i < validosL+1; i++)
    {
        printf("Laboratorio: %d, %d, %d, %d\n",
               laboratorios[i].idLab,
               laboratorios[i].anio,
               laboratorios[i].mes,
               laboratorios[i].dia);
    }
}



//int GetIdLaboratorios()
//{
//    static int aux = 0;
//    aux++;
//    return aux;
//}
//




int buscandoIDPacientes() /// rafa probando busca id - - - - - - - funcion en utilities
{
    int newID = 0;
    int aux;
    printf("Ingrese el ID a buscar:\”");
    scanf("%i",&newID);
    aux = compararIDLP(newID);
    if ( aux == 0)
    {
        printf("El id ha sido encontrado.\n”");
        return newID;
    }
    else if (aux == 1)
    {
        printf("El ID no existe. Si desea crear uno vaya al apartado pacientes.\n");
    }
    return 1;
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

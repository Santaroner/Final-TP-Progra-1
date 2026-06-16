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

    FILE *Laboratorios;
    Laboratorios = fopen(ARCHIVO_LABORATORIOS, "ab");

    char seguir = 'n';
    lab->idLab = getIDVLaboratorio();
    printf("ID asignado: %d\n", lab->idLab);

    do
    {
        lab->anio = validarAnio();
        lab ->mes = validarMes();
        lab ->dia = validarDia(lab ->mes);

        printf("Ingrese ID del paciente: ");
        scanf("%d",&lab->idPaciente);

        printf("Ingrese ID de practica: ");
        scanf("%d", &lab->practicaRealizada);

        lab->baja = 0;

        printf("Confirmar datos? (s/n) ");
        scanf(" %c", &seguir);
    }
    while (tolower(seguir) != 's');


    fwrite(lab, sizeof(stLaboratorios), 1, Laboratorios);
    printf("Laboratorio: ID: %d | Anio: %d | Mes: %d | Dia: %d\n",
           lab->idLab,
           lab->anio,
           lab->mes,
           lab->dia);

    fclose(Laboratorios);
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

int validarAnio()
{
    int aux = 0;
    do
    {
        printf("Ingrese el anio(1990-2026): ");
        scanf("%d", &aux);
        if (aux < 1990 || aux > 2026)
            printf("Año equivocado, recuerde (entre 1990 y 2026) \n");
        else
            printf("Anio %d\n", aux);
    }
    while (aux < 1990 || aux > 2026);
    return aux;
}

int validarMes()
{
    int aux = 0;
    do
    {
        printf("Ingrese el mes(1-12): ");
        scanf("%d", &aux);
        if (aux < 1 || aux > 12)
            printf("Error, recuerde entre 1 y 12 \n");
        else
            printf("Mes %d\n", aux);
    }
    while (aux < 1 || aux > 12);
    return aux;
}

int validarDia(int mes)
{
    int dia;
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    do
    {
        printf("Ingrese el dia: ");
        scanf("%d", &dia);
        if (dia < 1 || dia > diasPorMes[mes])
            printf("Dia invalido para ese mes.\n");
        else
            printf("Dia: %d\n", dia);
    }
    while (dia < 1 || dia > diasPorMes[mes]);
    return dia;
}

void bajaLaboratorio()
{
    int idBuscar;
    int pos = 0;
    int posEncontrado = -1;
    stLaboratorios lab;

    printf("Ingrese ID a dar de baja: ");
    scanf("%d", &idBuscar);

    FILE *archi = fopen(ARCHIVO_LABORATORIOS, "r+b");
    if (archi == NULL)
    {
        printf("Error al abrir");
        return;
    }

    while (fread(&lab, sizeof(stLaboratorios), 1, archi)> 0)
    {
        if (lab.idLab == idBuscar && lab.baja == 0)
        {
            posEncontrado = pos;
            lab.baja = 1;
            break;
        }
        pos++;
    }

    if (posEncontrado != -1)
    {
        fseek(archi, posEncontrado * sizeof(stLaboratorios), SEEK_SET);
        fwrite(&lab, sizeof(stLaboratorios), 1,archi);
        printf("Laboratorio dado de baja");
    }
    else
        printf("Laboratorio no encontrado o ya de baja");

    fclose(archi);
}

void mostrarLaboratorios(stLaboratorios *laboratorios,int validosL)
{
    for(int i = 0; i < validosL; i++)
    {
        printf("Laboratorio: ID: %d | Anio: %d | Mes: %d | Dia: %d\n",
               laboratorios[i].idLab,
               laboratorios[i].anio,
               laboratorios[i].mes,
               laboratorios[i].dia);
    }
}

void mostrarLaboratoriosArchivo()
{
    FILE *archi = fopen(ARCHIVO_LABORATORIOS, "rb");
    stLaboratorios aux;

    if (archi == NULL)
    {
        printf("Error al abrir.");
        return;
    }

    while (fread(&aux, sizeof(stLaboratorios), 1, archi)> 0)
    {
        if (aux.baja == 0)
        {
            printf("ID: %d | Paciente: %d | Practica: %d | Anio: %d | Mes: %d | Dia: %d\n",
                   aux.idLab,
                   aux.idPaciente,
                   aux.practicaRealizada,
                   aux.anio,
                   aux.mes,
                   aux.dia);
        }
    }
}

void modificarLaboratorio()
{
    int idBuscar;
    int pos = 0;
    int posEncontrado = -1;
    stLaboratorios lab;

    printf("Ingrese ID de Lab a modificar:\n ");
    scanf("%d", &idBuscar);

    FILE *archi = fopen(ARCHIVO_LABORATORIOS, "r+b");
    if (archi == NULL)
    {
        printf("Error al abrir archivo. \n");
        return;
    }

    while(fread(&lab, sizeof(stLaboratorios), 1, archi)> 0)
    {
        if (lab.idLab == idBuscar && lab.baja == 0)
        {
            posEncontrado = pos;
            break;
        }
        pos++;
    }

    if (posEncontrado == -1)
    {
        printf("Laboratorio no encontrado o de baja. \n");
        fclose(archi);
        return;
    }

    int opcion;
    printf("Que desea modificar?\n");
    printf("1- Fecha\n");
    printf("2- Practica\n");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        lab.anio = validarAnio();
        lab.mes  = validarMes();
        lab.dia  = validarDia(lab.mes);
        break;
    case 2:
        do
        {
            printf("Ingrese nuevo ID de practica: ");
            scanf("%d", &lab.practicaRealizada);
        }
        while (compararIDLPrac(lab.practicaRealizada));
        break;
    default:
        printf("Opcion invalida.\n");
        fclose(archi);
        return;
    }

    fseek(archi, posEncontrado * sizeof(stLaboratorios), SEEK_SET);
    fwrite(&lab, sizeof(stLaboratorios), 1, archi);
    printf("Laboratorio modificado correctamente.\n");

    fclose(archi);
}

void consultarLaboratorio()
{
    int idBuscar;
    int encontrado = 0;
    stLaboratorios lab;

    printf("Ingresar ID del laboratorio a consultar: ");
    scanf("%d", &idBuscar);

    FILE *archi = fopen(ARCHIVO_LABORATORIOS, "rb");
    if (archi == NULL)
    {
        printf("Error al abrir");
        return;
    }

    while (fread(&lab, sizeof(stLaboratorios), 1, archi)> 0)
    {
        if (lab.idLab == idBuscar && lab.baja == 0)
        {
            printf("ID: %d | Paciente: %d | Practica: %d | Anio: %d | Mes: %d | Dia: %d\n",
                   lab.idLab,
                   lab.idPaciente,
                   lab.practicaRealizada,
                   lab.anio,
                   lab.mes,
                   lab.dia);
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0)
        printf("Laboratorio no encontrado o de baja");

    fclose(archi);
}


int buscandoIDPacientes() /// rafa probando busca id - - - - - - - funcion en utilities
{
    int newID = 0;
    int aux;
    printf("Ingrese el ID a buscar:\”");
    scanf("%i",&newID);
    aux = compararIDLP(newID);
    if ( aux == 0)
    {
        printf("El id ha sido encontrado.\n");
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

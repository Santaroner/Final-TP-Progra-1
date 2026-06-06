#include <stdio.h>
#include "Pacientes.h"
#include "Practicas.h"
#include "Laboratorios.h"
#define ARCHIVO_PACIENTES "TestPacientes.bin"
#define ARCHIVO_PRACTICAS "Practicas.bin"
#define ARCHIVO_LABORATORIOS "Laboratorios.bin"
//int GetIDPacientes ()
//{
//    int aux;
//    static int IDEstatico = 1;
//    aux = IDEstatico;
//    IDEstatico ++;
//    return aux;
//}

int GetIDPacientes ()
{
    int oldID = getIDVPacientes();
    oldID ++;
    return oldID;
}

int getIDVPacientes() /// Recorre archivo Pacientes para saber cuantos ID tiene
{
    stPaciente aux;
    int IDAux = 0;
    FILE * archi = fopen("TestPacientes.bin", "rb");
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0 )
    {
        IDAux ++;
    }
    IDAux++;
    printf("IDAux vale:%i",IDAux);
    fclose(archi);
    return IDAux;
}

int compararIDLP (int num)
{
    printf("entra");
    stPaciente aux;
    FILE *archi = fopen ("PacientesSanti.bin","rb"); /// CAMBIAR MAS ADELANTE POR EL ORIGINALm Pacientes santi para practicar ahora
    while (fread(&aux,sizeof(stPaciente),1,archi))
    {
        if (num == aux.idPaciente)
        {
            printf("ID Encontrado. ID:%i\n",aux.idPaciente);
            printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
            fclose(archi);
            return 0;
        }
        else printf("Buscando id en el bucle.\”");
    }
    fclose(archi);
    return 1;
}

int pacientesEliminados()
{
    int aux = 0;
    stPaciente paciente;
    FILE *archi = fopen("TestPacientes.bin","rb");
    while (fread(&paciente,sizeof(stPaciente),1,archi) > 0 )
    {
        aux++;
    }
    return aux;
}

int getIDVPracticas() /// Recorre el archivo de practicas para hacer saber cuantos ID tiene
{
    stPracticas aux;
    int IDAux = 0;
//   FILE * archi = fopen("PracticasSanti.bin", "rb");
    FILE * archi = fopen("Practicas.bin", "rb");
    while (fread(&aux,sizeof(stPracticas),1,archi) > 0 )
    {
        IDAux ++;
    }
    printf("IDPracticasAux vale:%i",IDAux);
    fclose(archi);
    return IDAux;
}


int GetIdLaboratorios()
{
    static int aux = 0;
    aux++;
    return aux;
}


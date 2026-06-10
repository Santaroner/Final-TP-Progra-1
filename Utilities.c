#include <stdio.h>
#include "Pacientes.h"
#include "Practicas.h"
#include "Laboratorios.h"
#include "Menus.h"

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
        else printf("Buscando id en el bucle.\n");
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
    FILE * archi = fopen(ARCHIVO_PRACTICAS, "rb");
    while (fread(&aux,sizeof(stPracticas),1,archi) > 0 )
    {
        IDAux ++;
    }
    ///printf("IDPracticasAux vale:%i",IDAux);
    fclose(archi);
    return IDAux;
}

int getIDVLaboratorio()
{
    stLaboratorios aux;
    int IDAux = 0;
    FILE * archi = fopen(ARCHIVO_LABORATORIOS, "rb");
    while (fread(&aux, sizeof(stLaboratorios),1,archi) > 0)
    {
        IDAux++;
    }
    IDAux++;
    fclose(archi);
    return IDAux;
}

/// ----------------------------- PRE CARGA PARA TEST DE ARCHIVOS


/// -------------- FUNCIONES ANTI ADRIAN ---- solo numeros ///

int ingresarSoloLetrasSinEspacios (char palabra[]) /// Ingreso solo letras SIN espacios
{
    int i = 0;

    while (palabra [i] != '\0' && palabra[i] != ' \n')  /// '\0' Cuando llega al final del arreglo
    {
        if(!isalpha(palabra[i]) ) /// Isalpha es verdadero cuando el caracter no es una letra - por eso ! --- palabra[i] != ' ' para que no se ingresen espacios. Valido para DNI, nombre, celular
        {
            return 0; /// Si retorna 0 es falso
        }
        i++;
    }
    return 1; /// Si no hizo return en el 0, es verdadero.
}

int ingresarSoloNumerosEnArreglo (char numeros[])
{
    int i = 0;

    while (numeros[i] != '\0' && numeros[i] != '\n') /// Mientras no haya \n o \0
    {
        if (!isdigit(numeros[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int ingresarSoloNumeros (int numeros)
{
    while (numeros != '\0' && numeros != '\n') /// Mientras no haya \n o \0
    {
        if (!isdigit(numeros))
        {
            return 0;
        }
    }
    return 1;
}

/// VALIDACIONES


/// --------------------------------------- T E S T    A R C H I V O S ------------------------------------------------------------------------------ ///



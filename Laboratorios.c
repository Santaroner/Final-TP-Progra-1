#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
#include "Practicas.h"

// idLab - idPac - año - mes - dia - idPrac - baja o alta

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

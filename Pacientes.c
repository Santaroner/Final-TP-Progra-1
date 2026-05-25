#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
/// preguntar arreglo dinamico en cargarPacientes (cuando hacer el free) (si despues de llenar el archivo)
 stPaciente *pacientes = NULL;
 int validos = 0; /// validos para el arreglo dinamico

 /// ID - nombre - apellido - dni - movil - eliminado
void cargarPacientes()
{
    char seguir = 's';
    while (tolower(seguir) == 's') /// tolower por si se ingresa S mayuscula
    {
        stPaciente *aux = realloc (pacientes,validos+1 * sizeof(stPaciente));
        if (aux != NULL)
        {
            printf("Se asigno memoria correctamente\n"); /// TEST -------------------------------
            pacientes = aux;
        } else printf("No se pudo asignar memoria.\n");/// TEST -------------------------------
        cargaPaciente();
        printf("Desea cargar otro paciente?\n");
        scanf(" %c",&seguir);
        if (tolower(seguir) != 's') {printf("Operacion terminada\n");}
        else {validos++;
        printf("Validos vale:%i\n",validos);}
    }
    }
 void cargaPaciente()
 {
     int ID = 0;
     char nombre[30];
     char apellido[30];
     char DNI [10];
     char movil[12];
     ID = cargarIDPaciente();
     cargarNombrePaciente(pacientes[validos].nombre);
     cargarApellidoPaciente(pacientes[validos].apellido);
     cargarDNIPaciente(pacientes[validos].dni);
     cargarMovilPaciente(pacientes[validos].movil);
     printf("Paciente: %s, %s, %s, %s\n",
            pacientes[validos].nombre,
            pacientes[validos].apellido,
            pacientes[validos].dni,
            pacientes[validos].movil);
 }

 int cargarIDPaciente() /// Diferentes funciones para hacer las validaciones correspondientes
 {
    int ID = GetIDPacientes();
    if (ID != 0)
    {
        return ID;
    } else printf("El ID no se autoincremento correctamente, buscar solucion.\n");return 0;
 }
 void cargarNombrePaciente(char nombre[30])
 {
     char aux[30];
     int flag = 0;
     do
     {
        printf("Ingrese el nombre del paciente:\n");
        getchar();
        fgets(aux,30,stdin);
     if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 30 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
     {
         aux [strcspn(aux,"\n" )] = '\0';
         printf("Nombre guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
         strcpy(nombre,aux);
         flag = 1; /// Si se cambia la flag es porque es ingreso el nombre correctamente > fin de bucle
     }else
     {
         while (getchar () != '\n'); /// Si se añaden mas de 30 caracteres los limpia
         printf("No puede exceder los 30 caracteres, intente de nuevo.\n");
     }
     } while (flag == 0);
 }
void cargarApellidoPaciente(char apellido[])
{
   char aux[30];
     int flag = 0;
     do
     {
        printf("Ingrese el apellido del paciente:\n");
        fgets(aux,30,stdin);
     if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 30 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
     {
         aux [strcspn(aux,"\n" )] = '\0';
         printf("Apellido guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
         strcpy(apellido,aux);
         flag = 1; /// Si se cambia la flag es porque es ingreso el nombre correctamente > fin de bucle
     }else
     {
         while (getchar () != '\n'); /// Si se añaden mas de 30 caracteres los limpia
         printf("No puede exceder los 30 caracteres, intente de nuevo.\n");
     }
     } while (flag == 0);
}
void cargarDNIPaciente(char DNI[])
{
    char aux[10];
     int flag = 0;
     do
     {
        printf("Ingrese el DNI del paciente:\n");
        fgets(aux,10,stdin);
     if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 10 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
     {
         aux [strcspn(aux,"\n" )] = '\0';
         printf("DNI guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
         strcpy(DNI,aux);
         flag = 1; /// Si se cambia la flag es porque es ingreso el nombre correctamente > fin de bucle
     }else
     {
         while (getchar () != '\n'); /// Si se añaden mas de 10 caracteres los limpia
         printf("No puede exceder los 10 caracteres, intente de nuevo.\n");
     }
     } while (flag == 0);
}
void cargarMovilPaciente(char movil[])
{
    char aux[12];
     int flag = 0;
     do
     {
        printf("Ingrese el celular del paciente:\n");
        fgets(aux,12,stdin);
     if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 12 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
     {
         aux [strcspn(aux,"\n" )] = '\0';
         printf("Celular guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
         strcpy(movil,aux);
         flag = 1; /// Si se cambia la flag es porque es ingreso el nombre correctamente > fin de bucle
     }else
     {
         while (getchar () != '\n'); /// Si se añaden mas de 12 caracteres los limpia
         printf("No puede exceder los 12 caracteres, intente de nuevo.\n");
     }
     } while (flag == 0);
}
// void cargarEstadoPaciente();

void mostrarPacientes(stPaciente *pacientes,int validos)
{
    for(int i = 0; i < validos+1; i++)
    {
        printf("Paciente: %s, %s, %s, %s\n",
            pacientes[i].nombre,
            pacientes[i].apellido,
            pacientes[i].dni,
            pacientes[i].movil);
    }
}

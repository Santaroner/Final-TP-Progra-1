#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
/// preguntar arreglo dinamico en cargarPacientes (cuando hacer el free) (si despues de llenar el archivo)
stPaciente *pacientes = NULL;
int validos = 0; /// validos para el arreglo dinamico

/// ID - nombre - apellido - dni - movil - eliminado




/// ---------------------------------------------- C A R G A   P A C I E N T E S ------------------------------------------------------------------
void cargarPacientes()
{
    char seguir = 's';
    while (tolower(seguir) == 's') /// tolower por si se ingresa S mayuscula
    {
        stPaciente *aux = realloc (pacientes,(validos+1) * sizeof(stPaciente));
        if (aux != NULL)
        {
            printf("Se asigno memoria correctamente\n"); /// TEST -------------------------------
            pacientes = aux;
        }
        else printf("No se pudo asignar memoria.\n");  /// TEST -------------------------------
        cargaPaciente();
        printf("Desea cargar otro paciente?\n");
        scanf(" %c",&seguir);
        if (tolower(seguir) != 's')
        {
            printf("Operacion terminada\n");
        }
        else
        {
            validos++;
            printf("Validos vale:%i\n",validos);
        }
    }
}
void cargaPaciente()
{
    int ID ;
    FILE *Pacientes;
    Pacientes = fopen("Heroes.bin", "ab");
    ID = cargarIDPaciente();
    pacientes[validos].idPaciente = ID;
    cargarNombrePaciente(pacientes[validos].nombre);
    cargarApellidoPaciente(pacientes[validos].apellido);
    cargarDNIPaciente(pacientes[validos].dni);
    cargarMovilPaciente(pacientes[validos].movil);
    fwrite(&pacientes[validos],sizeof(stPaciente),1,Pacientes);
    printf("Paciente: %s, %s, %s, %s\n",
           pacientes[validos].nombre,
           pacientes[validos].apellido,
           pacientes[validos].dni,
           pacientes[validos].movil);
    fclose(Pacientes);
}

int cargarIDPaciente() /// Diferentes funciones para hacer las validaciones correspondientes
{
    int ID = GetIDPacientes();
    if (ID != 0)
    {
        return ID;
    }
    else printf("El ID no se autoincremento correctamente, buscar solucion.\n");
    return 0;
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
        }
        else
        {
            while (getchar () != '\n'); /// Si se añaden mas de 30 caracteres los limpia
            printf("No puede exceder los 30 caracteres, intente de nuevo.\n");
        }
    }
    while (flag == 0);
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
        }
        else
        {
            while (getchar () != '\n'); /// Si se añaden mas de 30 caracteres los limpia
            printf("No puede exceder los 30 caracteres, intente de nuevo.\n");
        }
    }
    while (flag == 0);
}
void cargarDNIPaciente(char DNI[])
{
    char aux[10];
    int flag = 0;
    do
    {
        printf("Ingrese el DNI del paciente:\n");
        fgets(aux,10,stdin);
        if (strchr(aux,'\n') != NULL && strlen(aux) > 8) /// Si se ingresan mas de 10 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        {
            aux [strcspn(aux,"\n" )] = '\0';
            printf("DNI guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
            strcpy(DNI,aux);
            flag = 1; /// Si se cambia la flag es porque es ingreso el nombre correctamente > fin de bucle
        }
        else
        {
            while (getchar () != '\n'); /// Si se añaden mas de 10 caracteres los limpia
            printf("No puede exceder los 10 caracteres, intente de nuevo.\n");
        }
    }
    while (flag == 0);
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
        }
        else
        {
            while (getchar () != '\n'); /// Si se añaden mas de 12 caracteres los limpia
            printf("No puede exceder los 12 caracteres, intente de nuevo.\n");
        }
    }
    while (flag == 0);
}
// void cargarEstadoPaciente();

/// ------------------------------------------------------ C A R G A  P A C I E N T E S ---------------------------------------------------------------- ///

/// ------------------------------------------------------- M U E S T R A ///  V A L I D O S ----------------------------------------------------------///

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

int mostrarArchivo ()
{
    int validos = 0;

    int optionswitch;
    printf("1-\n2-\n3-\4-\n");
    scanf("%i",&optionswitch);
FILE *PrePacientes;
        stPaciente aux;
    switch(optionswitch)
    {
    case 1:

        PrePacientes = fopen("TestPacientes.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,PrePacientes) > 0 )
        {
            printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
            validos++;
        }
        fclose(PrePacientes);
        return validos;
        break;
    case 2:
        PrePacientes = fopen("Heroes.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,PrePacientes) > 0 )
        {
            printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
            validos++;
        }
        fclose(PrePacientes);
        return validos;
        break;
    case 3:
        PrePacientes = fopen("PrePacientes.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,PrePacientes) > 0 )
        {
            printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
            validos++;
        }
        fclose(PrePacientes);
        return validos;
        break;
    }

//    FILE *PrePacientes;
//    stPaciente aux;
//    PrePacientes = fopen("TestPacientes.bin","rb");
//    while (fread(&aux,sizeof(stPaciente),1,PrePacientes) > 0 )
//    {
//        printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
//               aux.idPaciente,
//               aux.nombre,
//               aux.apellido,
//               aux.dni,
//               aux.movil);
//        validos++;
//    }
//    fclose(PrePacientes);
//    return validos;
}

//void cantidadValidosPacientes(stPacientes *pacientes)
//{
//    FILE *arch;
//    arch = fopen("Pacientes.bin", "rb");
//}

/// ------------------------------------------------------- M U E S T R A ///  V A L I D O S ----------------------------------------------------------///


/// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///

//void modificarPaciente(stPaciente *pacientes, int validos)
//{
//    char aux[30];
//    int optionswitch;
//    printf("Ingrese el DNI del paciente a modificar");
//    fgets(aux,30,stdin);
//    aux [strcspn(aux,"\n")] == '\0';
//    if (strcmpi(aux, pacientes[i].dni) == 0)
//    {
//        printf("El paciente ha sido encontrado.\Ingrese el dato a modificar:\n1-Nombre2-Apellido\n4-Movil"\n);
//    }
//
//}

/// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///

/// --------------------------------------- T E S T    A R C H I V O S ------------------------------------------------------------------------------ ///

// void TestPCarga()
// {
//     int ID ;
//     FILE *PrePacientes;
//     PrePacientes = fopen("PrePacientes.bin", "ab");
//     ID = cargarIDPaciente();
//     cargarNombrePaciente(pacientes[validos].nombre);
//     cargarApellidoPaciente(pacientes[validos].apellido);
//     cargarDNIPaciente(pacientes[validos].dni);
//     cargarMovilPaciente(pacientes[validos].movil);
//     fwrite(&pacientes[validos],sizeof(stPaciente),1,PrePacientes);
//     printf("Paciente: %s, %s, %s, %s\n",
//            pacientes[validos].nombre,
//            pacientes[validos].apellido,
//            pacientes[validos].dni,
//            pacientes[validos].movil);
//    fclose(PrePacientes);
// }

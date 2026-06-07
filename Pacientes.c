#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
/// FALTAN VALIDACIONES ARCHIVOS SI NO SE ABREN MENSAJE DE ERROR AL ABRIR
/// Funcion volver a dar de alta de lista de eliminados
/// Implementar ToUpper en primera letra de strings en nombres, apellidos.
/// ordenar y comentar codigo
stPaciente *pacientes = NULL;
int validos = 0; /// validos para el arreglo dinamico


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
    int activo;
    FILE *Pacientes;
    Pacientes = fopen("TestPacientes.bin", "ab");
    ID = cargarIDPaciente();
    pacientes[validos].idPaciente = ID;
    cargarNombrePaciente(pacientes[validos].nombre);
    cargarApellidoPaciente(pacientes[validos].apellido);
    cargarDNIPaciente(pacientes[validos].dni);
    cargarMovilPaciente(pacientes[validos].movil);
    activo = cargarEstadoPaciente();
    pacientes[validos].eliminado = activo ; /// asigna estado 0 o 1
    printf("Carga paciente eliminado valor : %i ", pacientes[validos].eliminado);
    fwrite(&pacientes[validos],sizeof(stPaciente),1,Pacientes);

    printf("Paciente: %s, %s, %s, %s, Estado:%i\n",
           pacientes[validos].nombre,
           pacientes[validos].apellido,
           pacientes[validos].dni,
           pacientes[validos].movil,
           pacientes[validos].eliminado);
    fclose(Pacientes);
}

int cargarIDPaciente() /// Diferentes funciones para hacer las validaciones correspondientes
{
    int ID = getIDVPacientes(); /// IDV Recorre el archivo para incrementar los ID
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
    int validar;
    do
    {
        printf("Ingrese el DNI del paciente:\n");
        fgets(aux,10,stdin);
        aux [strcspn(aux,"\n" )] = '\0';
        validar = validarDNI(aux); /// Si devuelve 1 el DNI no está duplicado
//        if (strchr(aux,'\n') != NULL && strlen(aux) > 1 ) /// Si se ingresan mas de 10 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        if (strlen(aux) > 0 && strlen(aux) < 10) /// Si se ingresan mas de 10 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        {
            if (validar == 1)
            {
                aux [strcspn(aux,"\n" )] = '\0';
                printf("DNI guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
                strcpy(DNI,aux);
                flag = 1; /// Si se cambia la flag es porque es ingreso el DNI correctamente > fin de bucle
            }
//            } else {validar = validarDNI(aux);}
        }
        else
        {
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

int cargarEstadoPaciente()
{
    int aux ;
    int flag = 0;
    do
    {
        printf("El paciente esta activo?\n0:Activo ||| 1:Baja\n");
        scanf("%i",&aux);
        if (aux == 0 || aux == 1)
        {
            printf("Estado del paciente cargado correctamente.\n");
            printf("activo vale : %i",aux);
            flag = 1;
            return aux;
        }
        else
        {
            printf("Ingrese la opcion correcta por favor.\nEstado activo:0\nPaciente de baja:1.\n");
        }
    } while ( flag != 1);
}

int validarDNI (char DNI[])
{
    FILE *archi = fopen("TestPacientes.bin","rb");
    stPaciente aux;
    int flag = 0;

    if (archi == NULL)
    {
        printf("Error al abrir archivo.\”");
        return -1;
    }

    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (strcmpi (DNI, aux.dni) == 0)
        {
            printf("El DNI ya está en el sistema, elija otro por favor.\n");
            fclose(archi);
            return 0;
        }
    }
    if (flag == 0)
    {
        fclose(archi);
        return 1;
    }
}
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
    printf("1-TestPacientes\n2-Heroes ------- PROBANDO ACA\n3-PrePacientes\4-\n");
    scanf("%i",&optionswitch);
    FILE *PrePacientes;
    stPaciente aux;
    switch(optionswitch)
    {
    case 1:
        PrePacientes = fopen("TestPacientes.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,PrePacientes) > 0 )
        {
            if (aux.eliminado == 0)
            {
                 printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
            validos++;
            }
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
    case 4 :
        PrePacientes = fopen("PacientesSanti.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,PrePacientes) > 0 )
               {
                   if (aux.eliminado == 0)
                   {
                    printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil,
                   aux.eliminado);
                validos++;
                   }
        }
        fclose(PrePacientes);
        return validos;
        break;
    }
    }

void mostrarEliminados ()
{
    printf("Entra la funcion,");
    stPaciente aux;
    FILE *archi = fopen ("TestPacientes.bin","rb");
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (aux.eliminado == 1)
        {
            printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
        }
    }
    fclose(archi);
    char alta;
    printf("Desea dar de alta alguno de estos pacientes?(S/N)\n");
    scanf(" %c",&alta);
    if (alta == 's' || alta == 'S')
    {
        altaViejoPaciente();
    }
    else if (alta == 'n' || alta == 'N')
    {
        return;
    }
    else printf("Tecla incorrecta.\n");
}

/// ------------------------------------------------------- M U E S T R A ///  V A L I D O S ----------------------------------------------------------///


/// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///

void buscarPaciente(stPaciente *pacientes, int validos)
{
    FILE *archi = fopen("TestPacientes.bin","rb");
    int pos = 0; /// posicion a enviar
    char aux[30];
    stPaciente busqueda;
    printf("Ingrese el DNI del paciente a modificar\n");
    getchar();
    fgets(aux,10,stdin);
    aux [strcspn(aux,"\n")] = '\0';
    printf("Aux vale:%s",aux);
    for (int i = 0 ; i < validos ; i ++)
    {
        printf("Entra al bucle\n");
        printf("pos:%i",pos); /// testeando posicion
        fread(&busqueda,sizeof(stPaciente),1,archi);
        if (strcmpi(aux, busqueda.dni) == 0)
        {
            menuModificarPaciente(pos+1);
        }
        pos++;
    }
    fclose(archi);
}

void menuModificarPaciente (int pos)
{
    int optionswitch;
    printf("El paciente ha sido encontrado.\Ingrese el dato a modificar:\n1-Nombre\n2-Apellido\n3-Movil\n");
    scanf("%i",&optionswitch);
    switch(optionswitch)
    {
    case 1:
        cambiarNombrePaciente(pos);
        break;
    case 2:
        cambiarApellidoPaciente(pos);
        break;
    case 3:
        cambiarMovilPaciente(pos);
        break;
    case 4:
        cambiarDNIPaciente(pos);
        break;
    default :
        printf("Opcion incorrecta.\n");
        break;
    }
}

void cambiarNombrePaciente(int pos)
{
    char aux [30];
    stPaciente auxiliar;
    int flag = 0;
    do
    {
        printf("pos : %i",pos);
        printf("Ingrese el nombre actualizado del paciente:\n");
        getchar();
        fgets(aux, 30,stdin);
        if (strchr(aux,'\n') != NULL) ///
        {
            aux [strcspn(aux, "\n")] = '\0';
            printf("Nombre dentro de los parametros acordados\n");
            flag = 1;
        }
        else
        {
            while (getchar () != '\n'); ///
            printf("No se pueden ingresar mas de 30 numeros\n");
        }
    }while (flag == 0);

    FILE *archi = fopen("TestPacientes.bin","r+b");
    fseek(archi, (pos-1) * sizeof(stPaciente), SEEK_SET); /// Busca posicion menos 1
    fread(&auxiliar,sizeof(stPaciente),1,archi); /// Lee en auxiliar y avanza una posicion
    strcpy(auxiliar.nombre,aux); /// Copia el nombre cargado por usuario (aux) en la estructura
    fseek(archi, -sizeof(stPaciente), SEEK_CUR); /// Vuelve la posicion que sumo el fread arriba
    fwrite(&auxiliar,sizeof(stPaciente),1,archi); /// la estructura entera en la posicion
    printf("nombre strcpy: %s",auxiliar.nombre);
    fclose(archi); /// cerrar
}

void cambiarApellidoPaciente(int pos)
{
    char nuevoApellido [30];
    stPaciente aux;
    int flag = 0;
    do
    {
        printf("Ingrese el Apellido actualizado del paciente:\n");
        getchar();
        fgets(nuevoApellido, 12,stdin);
        if (strchr(nuevoApellido,'\n') != NULL)
        {
            nuevoApellido [strcspn(nuevoApellido, "\n")] = '\0';
            printf("Apellido dentro de los parametros acordados\n");
            flag = 1;
        }
        else
        {
            while (getchar () != '\n');
            printf("No se pueden ingresar mas de 30 letras\n");
        }
    }
    while (flag == 0);

    FILE *archi = fopen("TestPacientes.bin","r+b");
    fseek(archi,(pos-1) * sizeof(stPaciente),SEEK_SET);
    fread(&aux,sizeof(stPaciente),1,archi);
    strcpy(aux.apellido,nuevoApellido);
    printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
    fseek(archi, -sizeof(stPaciente),SEEK_CUR);
    fwrite(&aux,sizeof(stPaciente),1,archi);
    fclose(archi);
}

void cambiarMovilPaciente(int pos)
{
    char nuevoMovil [30];
    stPaciente aux;
    int flag = 0;
    do
    {
        printf("Ingrese el celular actualizado del paciente:\n");
        getchar();
        fgets(nuevoMovil, 12,stdin);
        if (strchr(nuevoMovil,'\n') != NULL)
        {
            nuevoMovil [strcspn(nuevoMovil, "\n")] = '\0';
            printf("Nombre dentro de los parametros acordados\n");
            flag = 1;
        }
        else
        {
            while (getchar () != '\n');
            printf("No se pueden ingresar mas de 12 numeros\n");
        }
    }
    while (flag == 0);

    FILE *archi = fopen("TestPacientes.bin","r+b");
    fseek(archi,(pos-1)* sizeof(stPaciente), SEEK_SET);
    fread(&aux,sizeof(stPaciente),1,archi);
    fseek(archi,-sizeof(stPaciente),SEEK_CUR);
    fwrite(&aux,sizeof(stPaciente),1,archi);
    fclose(archi);
}

void cambiarDNIPaciente(int pos)
{
    char nuevoDNI[12];
    stPaciente aux;
    int flag = 0;
    do
    {
        printf("Ingrese el nuevo DNI del paciente:\n");
        getchar();
        fgets(nuevoDNI,12,stdin);
        if (strchr(nuevoDNI,'\n') != NULL )
        {
            nuevoDNI[strcspn(nuevoDNI, "\n")] = '\0';
            flag = 1;
        }
        else
        {
            while (getchar() != '\n');
        }
    } while (flag == 0);

    printf("El nuevo dni del paciente va a ser : %s",nuevoDNI);

    FILE *archi = fopen("TestPacientes.bin","r+b");
    fseek(archi,(pos-1)*sizeof(stPaciente),SEEK_SET);
    fread (&aux,sizeof(stPaciente),1,archi);
    printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
    strcpy(aux.dni,nuevoDNI);
    fseek(archi,-sizeof(stPaciente),SEEK_CUR);
    fwrite(&aux,sizeof(stPaciente),1,archi);
    fclose(archi);
}

void bajaPaciente()
{
    int i = 0; /// contador de iteracion
    int contadorPos = 0; /// contador para SEEK_CUR
    char aux [10];
    stPaciente paciente;  /// estructura para recorrer
    stPaciente eliminado; /// estructura usada de auxiliar
    printf("Ingrese el DNI del paciente a dar de baja:\n");
    getchar();
    fgets(aux,10,stdin);
    aux[strcspn(aux, "\n")] = '\0';
    FILE *archi = fopen("TestPacientes.bin","r+b");
    while (fread(&paciente,sizeof(stPaciente),1,archi) > 0 )
    {
        printf("AUX: %s||DNI P: %s\n",aux,paciente.dni); /// borrar desp, viendo posiciones
        if (strcmpi(aux,paciente.dni) == 0)
        {
            contadorPos = i ;
            printf("Paciente encontrado.\n");
            paciente.eliminado = 1;
            eliminado = paciente; /// Copia el paciente para que no cambie en la nueva iteracion del bucle
            printf("Paciente dado de baja\n");
        }
        i++;
    }
        printf("Posicion:%i",contadorPos); /// borrar desp, probando posiciones
        fseek(archi, (contadorPos ) * sizeof(stPaciente),SEEK_SET); /// se mueve desde el principio las posiciones ya contadas en el while
        paciente = eliminado; /// cambio
        fwrite (&paciente,sizeof(stPaciente),1,archi);
    fclose(archi);
}


/// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///
/// ----------------------------------------------------- B U S C A R ---- P A C I E N T E  ------------------------------------------------------ ///

void busquedaPaciente ()
{
    int optionswitch = 0;
    char DNI [10];
    char apellido[30];

   printf("Desea buscar al paciente por DNI o por apellido?\n");
    printf("1-DNI.\n");
    printf("2-Apellido.\n");
    printf("0-Salir.\n");
    scanf("%i",&optionswitch);
    switch(optionswitch)
    {
    case 1:
        printf("Ingrese el DNI.\n");
        getchar();
        fgets(DNI,10,stdin);
        DNI[strcspn(DNI,"\n")] = '\0';
        busquedaPorDNI(DNI);
        break;
    case 2:
        printf("Ingrese el apellido.\n");
        getchar();
        fgets(apellido,30,stdin);
        apellido [strcspn(apellido,"\n")] = '\0';
        busquedaPorApellido(apellido);
        break;
    case 0:
        printf("Regrese pronto.\n");
        break;
    default :
        printf("Opcion incorrecta.\n");
        break;
}
}

void busquedaPorDNI (char DNI[])
{
    stPaciente aux;
    FILE * archi = fopen("TestPacientes.bin","rb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (strcmpi (DNI,aux.dni) == 0)
        {
            printf("Paciente encontrado.\n");
            printf("Nombre:%s\n",aux.nombre);
            printf("Apellido:%s\n",aux.apellido);
            printf("Celular:%s\n",aux.movil);
            printf("ID:%i\n",aux.idPaciente);
            printf("---------------------------------------------------------\n");
        }
    }
    fclose(archi);
}

void busquedaPorApellido (char apellido[])
{
    stPaciente aux;
    FILE * archi = fopen("TestPacientes.bin","rb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (strcmpi (apellido,aux.apellido) == 0)
        {
            printf("Paciente encontrado.\n");
            printf("Nombre:%s\n",aux.nombre);
            printf("Apellido:%s\n",aux.apellido);
            printf("Celular:%s\n",aux.movil);
            printf("ID:%i\n",aux.idPaciente);
            printf("---------------------------------------------------------\n");
        }
    }
    fclose(archi);
}
/// ----------------------------------------------------- B U S C A R ---- P A C I E N T E  ------------------------------------------------------ ///

/// ----------------------------------------------------- A L T A --- P A C I E N T E   ------------------------------------------------------ ///

void altaViejoPaciente ()
{
    int aux = 0;
    int flag = 0;
    int pos = 0;
    int auxPos = 0;
    stPaciente paciente;
    stPaciente copiar;
    FILE *archi = fopen ("TestPacientes.bin","r + b");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }
//    mostrarEliminados();
    printf("Ingrese el ID del paciente a dar el alta por favor:\n");
    scanf("%i",&aux);

    while (fread(&paciente,sizeof(stPaciente),1,archi) > 0)
    {
        if (aux == paciente.idPaciente)
        {
            auxPos = pos;
            paciente.eliminado = 0;
            printf("Paciente dado de alta correctamente.\n");
            copiar = paciente;
        }
        else if (flag == 0)
        {
            printf("El paciente no fue encontrado en los registros.\n");
        }
         pos++;
    }
    fseek(archi,auxPos * sizeof(stPaciente),SEEK_SET);
    fwrite(&copiar,sizeof(stPaciente),1,archi);
    fclose(archi);
}


/// --------------------------------------- T E S T    A R C H I V O S ------------------------------------------------------------------------------ ///
//printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
//                   aux.idPaciente,
//                   aux.nombre,
//                   aux.apellido,
//                   aux.dni,
//                   aux.movil);


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

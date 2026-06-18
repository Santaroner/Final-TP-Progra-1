#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pacientes.h"
#include "Utilities.h"
/// FALTAN VALIDACIONES ARCHIVOS SI NO SE ABREN MENSAJE DE ERROR AL ABRIR
/// Funcion volver a dar de alta de lista de eliminados
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
        system("cls");
        printf("Desea cargar otro paciente?S/N\n ");
        seguir = ingresoSoloLetraEnScan();
        if (tolower(seguir) != 's')
        {
            printf("Volviendo al menu anterior\n");
            system("pause");
            system("cls");
        }
        else
        {
            validos++;
        }
    }
}
void cargaPaciente()
{
    int ID ;
    int activo;
    FILE *archi;
    archi = abrirArchivo(ARCHIVO_PACIENTES,"ab");
    ID = cargarIDPaciente();
    pacientes[validos].idPaciente = ID;
    cargarNombrePaciente(pacientes[validos].nombre);
    cargarApellidoPaciente(pacientes[validos].apellido);
    cargarDNIPaciente(pacientes[validos].dni);
    cargarMovilPaciente(pacientes[validos].movil);
    activo = cargarEstadoPaciente();
    pacientes[validos].eliminado = activo ; /// asigna estado 0 o 1
    printf("Carga paciente eliminado valor : %i ", pacientes[validos].eliminado);
    fwrite(&pacientes[validos],sizeof(stPaciente),1,archi);

    printf("Paciente: %s, %s, %s, %s, Estado:%i\n",
           pacientes[validos].nombre,
           pacientes[validos].apellido,
           pacientes[validos].dni,
           pacientes[validos].movil,
           pacientes[validos].eliminado);
    fclose(archi);
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
    system("cls");
    char aux[30];
    int flag = 0;
//    getchar();
    do
    {
        printf("Ingrese el nombre del paciente:\n");

        fgets(aux,30,stdin);
        if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 30 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        {
            borrarSaltoDeLinea(aux);
            if (ingresarSoloLetrasSinEspacios(aux) == 1)
            {
                printf("Nombre ingresado correctamente.\n");
                strcpy(nombre,aux);
                primerLetraMayuscula(nombre);
                system("pause");
                flag = 1;
            } else printf("Error.\n");
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
    system("cls");
    char aux[30];
    int flag = 0;
    do
    {
        printf("Ingrese el apellido del paciente:\n");
        fgets(aux,30,stdin);
        if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 30 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        {
            borrarSaltoDeLinea(aux);
            if (ingresarSoloLetrasSinEspacios(aux) == 1)
            {
                    printf("Apellido guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
                    strcpy(apellido,aux);
                    primerLetraMayuscula(apellido);
                    system("pause");
                    flag = 1; /// Si se cambia la flag es porque es ingreso el nombre correctamente > fin de bucle
            }
            else printf("Ingrese solo letras por favor... :)  \n");
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
    system("cls");
    do
    {
        printf("Ingrese el DNI del paciente:\n");
        fgets(aux,10,stdin);
       if (strchr(aux,'\n') != NULL)  /// Si se ingresan mas de 10 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        {
            borrarSaltoDeLinea(aux);
            validar = validarDNI(aux); /// Si devuelve 1 el DNI no está duplicado
            if (validar == 1)
            {
                    if (ingresarSoloNumerosEnArreglo(aux) == 1)
                    {
                        printf("DNI guardado correctamente.\n"); /// test ------------------------------------------------------------------- borrar deps
                        system("pause");
                        strcpy(DNI,aux);
                        flag = 1; /// Si se cambia la flag es porque es ingreso el DNI correctamente > fin de bucle
                    }
                    else printf("Intente de nuevo, solamente se pueden ingresar numeros en el dni.\n");
            }
//            else
        }
        else
        {
            printf("No puede exceder los 10 caracteres, intente de nuevo.\n");
            while (getchar() != '\n');
        }
    }
    while (flag == 0);
}
void cargarMovilPaciente(char movil[])
{
    char aux[12];
    int flag = 0;
    system("cls");
    do
    {
        printf("Ingrese el celular del paciente:\n");
        fgets(aux,12,stdin);
        if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 12 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        {
            borrarSaltoDeLinea(aux);
            if (ingresarSoloNumerosEnArreglo(aux) == 1)
            {
                printf("Celular guardado.\n"); /// test ------------------------------------------------------------------- borrar deps
                strcpy(movil,aux);
                system("pause");
                flag = 1; /// Si se cambia la flag es porque es ingreso el nombre correctamente > fin de bucle
            }
            else printf("Intente de nuevo, ingresando solamente numeros en el celular :) \n");
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
        aux = ingresarEnteroMinMax(0,1);
        printf("aux vale:%i",aux); /// BORRAR DESPUES
        flag = 1;
        fflush(stdin);
    } while ( flag != 1);
    return aux;
}

int validarDNI (char DNI[])
{
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    stPaciente aux;
    int flag = 0;

    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return -1;
    }

    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (strcmpi (DNI, aux.dni) == 0)
        {
            printf("El DNI ya está en el sistema, elija otro por favor.\n");
            fclose(archi);
            flag = 1;
            return 0;
        }
    }
    if (flag == 0)
    {
        fclose(archi);
        return 1;
    }
    return 0;
}
/// ------------------------------------------------------ C A R G A  P A C I E N T E S ---------------------------------------------------------------- ///

/// ------------------------------------------------------- M U E S T R A ///  V A L I D O S ----------------------------------------------------------///
void mostrarUnPaciente (stPaciente paciente)
{
        printf("Paciente:%s, %s\n",paciente.nombre,paciente.apellido);
        printf("Celular: %s\n",paciente.movil);
        printf("DNI:     %s\n",paciente.dni);
        printf("ID:      %i\n",paciente.idPaciente);
        printf("---------------------------------------------------------\n");
}

int mostrarArchivo ()
{
    system("cls");
    int validos = 0;
    FILE *archi;
    stPaciente aux;
        archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
        while (fread(&aux,sizeof(stPaciente),1,archi) > 0 )
        {
            if (aux.eliminado == 0)
            {
                 mostrarUnPaciente(aux);
            validos++;
            }
        }
        fclose(archi);
        system("pause");
        system("cls");
    return validos;
    }

void mostrarEliminados ()
{
    stPaciente aux;
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (aux.eliminado == 1)
        {
            mostrarUnPaciente(aux);
        }
    }
    fclose(archi);
    char alta;
    printf("Desea dar de alta alguno de estos pacientes?(S/N)\n");
    alta = ingresoSoloLetraEnScan();
    if (alta == 's' || alta == 'S')
    {
        altaViejoPaciente();
    }
    else if (alta == 'n' || alta == 'N')
    {
        system("cls");
        return;
    }
    else printf("Tecla incorrecta.\n");
}

/// ------------------------------------------------------- M U E S T R A ///  V A L I D O S ----------------------------------------------------------///


/// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///

void buscarPaciente(stPaciente *pacientes, int validos)
{
    system("cls");
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    int pos = 0; /// posicion a enviar
    char aux[30];
    int flag = 0;
    int temp = 0;
    stPaciente busqueda;
    getchar();
    do
    {
        printf("Ingrese el DNI del paciente a modificar\n");
        fgets(aux,10,stdin);
        if (strchr(aux,'\n') != NULL)
        {
            fseek(archi,0,SEEK_SET);
            borrarSaltoDeLinea(aux);
           while (fread(&busqueda,sizeof(stPaciente),1,archi) > 0)
        {
            if (strcmpi(aux, busqueda.dni) == 0)
            {
                if (ingresarSoloNumerosEnArreglo(aux) == 1)
                {
                    flag = 1;
                    temp = 1;
                    menuModificarPaciente(pos+1);
                    break;
                }
            }
            pos++;
        }if (flag == 0) printf("El paciente no ha sido encontrado.\n");
        }
        else
        {
            while (getchar () != '\n'); ///
            printf("No se pueden ingresar mas de 12 digitos\n");
        }

    } while (temp == 0);

    fclose(archi);
}

void menuModificarPaciente (int pos)
{
    int optionswitch;
    printf("El paciente ha sido encontrado.\nIngrese el dato a modificar:\n1-Nombre\n2-Apellido\n3-Movil\n0-Salir\n");
    optionswitch = ingresarEntero();
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
    case 0:
        printf("Volviendo al menu anterior..\n");
        return;
    default :
        printf("Opcion incorrecta.\n");
        break;
    }
}

void guardarPaciente (stPaciente paciente,int pos )
{
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"r+b");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }
    fseek(archi, (pos-1) * sizeof(stPaciente), SEEK_SET); /// Busca posicion menos 1
    fwrite(&paciente,sizeof(stPaciente),1,archi); /// la estructura entera en la posicion
    fclose(archi); /// cerrar
}

void cambiarNombrePaciente(int pos)
{
    char aux [30];
    stPaciente auxiliar;
    int flag = 0;
    getchar();
    do
    {
        printf("Ingrese el nombre actualizado del paciente:\n");
        fgets(aux, 30,stdin);
        if (strchr(aux,'\n') != NULL) ///
        {
            borrarSaltoDeLinea(aux);
            if (ingresarSoloLetrasSinEspacios(aux) == 1)
            {
                printf("Nombre dentro de los parametros acordados\n");
                flag = 1;
            } else printf("Ingrese solamente letras por favor.\n");
        }
        else
        {
            while (getchar () != '\n'); ///
            printf("No se pueden ingresar mas de 30 caracteres\n");
        }
    }while (flag == 0);
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"r+b");
    fseek(archi,(pos-1) * sizeof(stPaciente),SEEK_SET);
    fread(&auxiliar,sizeof(stPaciente),1,archi);
    primerLetraMayuscula(aux);
    strcpy(auxiliar.nombre,aux);
    fseek(archi, -(long)sizeof(stPaciente), SEEK_CUR);
    fwrite(&auxiliar,sizeof(stPaciente),1,archi);
    fclose(archi); /// Copia el nombre cargado por usuario (aux) en la estructura
    system("pause");
    system("cls");
}

void cambiarApellidoPaciente(int pos)
{
    char nuevoApellido [30];
    stPaciente aux;
    int flag = 0;
    getchar();
    do
    {
        printf("Ingrese el Apellido actualizado del paciente:\n");
        fgets(nuevoApellido,30,stdin);
        if (strchr(nuevoApellido,'\n') != NULL)
        {
            borrarSaltoDeLinea(nuevoApellido);
            if (ingresarSoloLetrasSinEspacios(nuevoApellido) == 1)
            {
                printf("Nombre dentro de los parametros acordados\n");
                primerLetraMayuscula(nuevoApellido);
                flag = 1;
            } else printf("Ingrese solamente letras por favor\n");
        }
        else
        {
            while (getchar () != '\n');
            printf("No se pueden ingresar mas de 30 letras\n");
        }
    }
    while (flag == 0);

    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"r+b");
    fseek(archi,(pos-1) * sizeof(stPaciente),SEEK_SET);
    fread(&aux,sizeof(stPaciente),1,archi);
    primerLetraMayuscula(nuevoApellido);
    strcpy(aux.apellido,nuevoApellido);
    printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
    fseek(archi, -(long)sizeof(stPaciente), SEEK_CUR);
    fwrite(&aux,sizeof(stPaciente),1,archi);
    fclose(archi);
    system("pause");
    system("cls");
}

void cambiarMovilPaciente(int pos)
{
    char nuevoMovil [12];
    stPaciente aux;
    int flag = 0;
    getchar();
    do
    {
        printf("Ingrese el celular actualizado del paciente:\n");
        fgets(nuevoMovil, 12,stdin);
        if (strchr(nuevoMovil,'\n') != NULL)
        {
            borrarSaltoDeLinea(nuevoMovil);
            {
                if (ingresarSoloNumerosEnArreglo(nuevoMovil) == 1)
                {
                    flag = 1;
                } else printf("Ingrese solo numeros por favor... :) \n");
            }
        }
        else
        {
            while (getchar () != '\n');
            printf("No se pueden ingresar mas de 12 numeros\n");
        }
    }
    while (flag == 0);

    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"r+b");
    fseek(archi,(pos-1)* sizeof(stPaciente), SEEK_SET);
    fread(&aux,sizeof(stPaciente),1,archi);
    fseek(archi, -(long)sizeof(stPaciente), SEEK_CUR);
    strcpy(aux.movil,nuevoMovil);
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
            borrarSaltoDeLinea(nuevoDNI);
            if (ingresarSoloNumerosEnArreglo(nuevoDNI) == 1)
            {
                flag = 1;
            } else printf("Ingrese solo numeros por favor... :) \n");
        }
        else
        {
            while (getchar() != '\n');
        }
    } while (flag == 0);

    printf("El nuevo dni del paciente va a ser : %s",nuevoDNI);

    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"r+b");
    fseek(archi,(pos-1)*sizeof(stPaciente),SEEK_SET);
    fread (&aux,sizeof(stPaciente),1,archi);
    printf("ID :%i\nNombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\n\n",
                   aux.idPaciente,
                   aux.nombre,
                   aux.apellido,
                   aux.dni,
                   aux.movil);
    strcpy(aux.dni,nuevoDNI);
    fseek(archi, -(long)sizeof(stPaciente), SEEK_CUR);
    fwrite(&aux,sizeof(stPaciente),1,archi);
    fclose(archi);
}

void bajaPaciente()
{
    system("cls");
    int i = 0; /// contador de iteracion
    int flag = 0; /// Se usa para printear que no se encontró el DNI, si flag sigue siendo 0.
    int contadorPos = 0; /// contador para SEEK_CUR
    char aux [10];
    stPaciente paciente;  /// estructura para recorrer
    stPaciente eliminado; /// estructura usada de auxiliar
    printf("Ingrese el DNI del paciente a dar de baja:\n");
    getchar();
    fgets(aux,10,stdin);
    aux[strcspn(aux, "\n")] = '\0';
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"r+b");
    while (fread(&paciente,sizeof(stPaciente),1,archi) > 0 )
    {
        if (strcmpi(aux,paciente.dni) == 0 && paciente.eliminado == 0)
        {
            contadorPos = i ;
            printf("Paciente encontrado y dado de baja.\n");
            paciente.eliminado = 1;
            eliminado = paciente; /// Copia el paciente para que no cambie en la nueva iteracion del bucle
            flag = 1; /// Cambia flag para que no printee que no se ha encontrado ningun paciente
        }
        else if (strcmpi(aux,paciente.dni) == 0 && paciente.eliminado == 1)
        {
            printf("El paciente:%s, %s esta actualmente dado de baja.\n",paciente.apellido,paciente.nombre);
            flag = 1; /// Cambia flag para que no printee que no se ha encontrado ningun paciente
        }
        i++;
    }
        fseek(archi, (contadorPos ) * sizeof(stPaciente),SEEK_SET); /// se mueve desde el principio las posiciones ya contadas en el while
        paciente = eliminado; /// cambio
        fwrite (&paciente,sizeof(stPaciente),1,archi);
    fclose(archi);
    if (flag == 0) printf("No se ha encontrado ningun paciente con el DNI ingresado.\n");
    system("pause");
    system("cls");
}


/// ----------------------------------------------------- M O D I F I C A R    P A C I E N T E S ------------------------------------------------------ ///
/// ----------------------------------------------------- B U S C A R ---- P A C I E N T E  ------------------------------------------------------ ///

void busquedaPaciente ()
{
    system("cls");
    int optionswitch = 0;
    char DNI [10];
    char apellido[30];

   printf("Desea buscar al paciente por DNI o por apellido?\n");
    printf("1-DNI.\n");
    printf("2-Apellido.\n");
    printf("0-Salir.\n");
    optionswitch = ingresarEntero();
    switch(optionswitch)
    {
    case 1:
        printf("Ingrese el DNI.\n");
        getchar();
        fgets(DNI,10,stdin);
        borrarSaltoDeLinea(DNI);
        busquedaPorDNI(DNI);
        break;
    case 2:
        printf("Ingrese el apellido.\n");
        getchar();
        fgets(apellido,30,stdin);
        borrarSaltoDeLinea(apellido);
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

int busquedaPorDNI (char DNI[])
{
    stPaciente aux;
    FILE * archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    int flag = 1;
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return 1;
    }
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (strcmpi (DNI,aux.dni) == 0)
        {
            printf("Se encontro en funcion busqueda.\n");
            mostrarUnPaciente(aux);
            flag = 0;
            system("pause");
            system("cls");
            fclose(archi);
            return flag;
        }
    }
    if (flag == 1)
    {
        printf("El paciente no esta en los registros\n");
    }
    fclose(archi);
    system("pause");
    system("cls");
    return flag; /// si flag 0 paciente encontrado

}
int busquedaPorApellido (char apellido[])
{
    stPaciente aux;
    int flag = 1;
    FILE * archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return 1;
    }
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (strcmpi (apellido,aux.apellido) == 0)
        {
            mostrarUnPaciente(aux);
            flag = 0;
            system("pause");
            system("cls");
            fclose(archi);
            return flag;
        }
    }
    if (flag == 1)
        {
            printf("El paciente no esta en el sistema.\n");
        }
    fclose(archi);
    system("pause");
    system("cls");
    return flag; /// si flag 0 paciente encontrado
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
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"r+b");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }
    printf("Ingrese el ID del paciente a dar el alta por favor:\n");
    aux = ingresarEntero();

    while (fread(&paciente,sizeof(stPaciente),1,archi) > 0)
    {
        if (aux == paciente.idPaciente && paciente.eliminado == 1 )
        {
            auxPos = pos;
            paciente.eliminado = 0;
            copiar = paciente;
            flag = 1;
        }
        else if (aux == paciente.idPaciente && paciente.eliminado == 0)
        {
            printf("El paciente ya esta actualmente dado de alta.\n");
            flag = 2;
        }
         pos++;
    }

      if (flag == 1)
    {
        fseek(archi, auxPos * sizeof(stPaciente), SEEK_SET);
        fwrite(&copiar, sizeof(stPaciente), 1, archi);
        printf("Paciente dado de alta correctamente.\n");
    }
    else if (flag == 0)
    {
        printf("El paciente no fue encontrado en los registros.\n");
    }
    fclose(archi);
    system("pause");
    system("cls");
}

/// ----------------------------------------------------- O R D E N A R ------------ P A C I E N T E &&& A R R E G L O --- D I N A M I C O   ------------------------------------------------------ ///

stPaciente * activosADinamicos (int *validosADP)
{
    stPaciente aux;
    stPaciente * ADP = NULL;
    *validosADP = 0;
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return NULL;
    }
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (aux.eliminado == 0)
        {
            (*validosADP)++;
            ADP  = creandoAD(aux,validosADP,ADP);
        }
    }
    mostrarADP(ADP,validosADP);
    fclose(archi);

    return ADP;
}

stPaciente * creandoAD (stPaciente paciente, int *validosADP,stPaciente *ADP)
{
    ADP = realloc (ADP, (*validosADP) * sizeof(stPaciente));
    if (ADP == NULL)
    {
        printf("Error al asignar memoria.\n");
        return NULL;
    }
    ADP[(*validosADP)-1] = paciente; /// num arranca valiendo 1
    return ADP;
}

void mostrarADP (stPaciente *aux, int *validosADP)
{
    for (int i = 0; i < *validosADP ; i++)
{
//    printf("Nombre:%s\nApellido:%s\nDNI:%s\nMovil:%s\nID:%i\n"
//       ,aux[i].nombre
//       ,aux[i].apellido
//       ,aux[i].dni
//       ,aux[i].movil
//       ,aux[i].idPaciente);
//    printf("--------------------------------------------\n");
}
//    system("pause");
//    system("cls");
}


int findMinorChar(stPaciente * ADR, int validosADP, int posicion)
{
    int posicionMenor = posicion;
    int subindice = posicion + 1;
    char menor[30];/// = ADR[posicion].apellido[0];
    char menorNombre[30]; /// Guarda nombre arrancando en 0 para comparar con 1
    strcpy(menor, ADR[posicion].apellido);
    strcpy(menorNombre,ADR[posicion].nombre);
    borrarSaltoDeLinea(menor);
    borrarSaltoDeLinea(menorNombre);
    while(subindice < validosADP)
    {
        if (strcmpi(menor,ADR[subindice].apellido) > 0 ||
        (strcmpi(menor, ADR[subindice].apellido) == 0 && strcmpi(menorNombre, ADR[subindice].nombre) > 0))
        /// Compara apellidos, y si son iguales == 0 compara nombres, sin el if el ordenamiento solamente por apellidos pisa al segundo paciente con el mismo apellido
        {
            posicionMenor = subindice;
            strcpy(menor,ADR[subindice].apellido);
            strcpy(menorNombre,ADR[subindice].nombre);
        }
        subindice++;
    }
    return posicionMenor;
}


void ordenamientoSeleccionChar(stPaciente *ADR,int validosADR)
{
    stPaciente aux;
    int posicionMenor = 0;
    int i = 0;

    while ( i < validosADR - 1)
    {
        posicionMenor = findMinorChar(ADR, validosADR, i);
        aux = ADR[i];
        ADR[i] = ADR[posicionMenor];
        ADR[posicionMenor] = aux;
        i++;
    }
    for (int i = 0; i < validosADR ; i++){printf(" %s, %s \n----------\n", ADR[i].apellido,ADR[i].nombre);}
    system("pause");
    system("cls");
}

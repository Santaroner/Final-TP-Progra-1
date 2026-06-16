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
        scanf(" %c",&seguir);
        if (tolower(seguir) != 's')
        {
            printf("Volviendo al menu anterior\n");
            system("pause");
            system("cls");
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
    do
    {
        printf("Ingrese el nombre del paciente:\n");
        getchar();
        fgets(aux,30,stdin);
        if (strchr(aux,'\n') != NULL) /// Si se ingresan mas de 30 letras fgets no tiene espacio para \n por lo que la condicion no se cumple
        {
            borrarSaltoDeLinea(aux);
            if (ingresarSoloLetrasSinEspacios(aux) == 1)
            {
                printf("Nombre ingresado correctamente.\n");
                strcpy(nombre,aux);
                primerLetraMayuscula(nombre);
                printf("Nombre.%s\n",nombre);
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
                    printf("Apellido:%s",apellido);
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
        printf("aux vale:%i",aux);
        flag = 1;
//        scanf("%i",&aux);
        fflush(stdin);

//        {
//            if (aux == 0 || aux == 1)
//            {
//                printf("Estado del paciente cargado correctamente.\n");
//                printf("activo vale : %i",aux);
//                flag = 1;
//                system("pause");
//                return aux;
//            }
//                printf("Ingrese la opcion correcta por favor.\nEstado activo:0\nPaciente de baja:1.\n");
//            }
//        else printf("Ingresar solo 0 o 1\n");

    } while ( flag != 1);
}

int validarDNI (char DNI[])
{
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
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
            flag = 1;
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
    int optionswitch;
    printf("1-TestPacientes\n2-Heroes ------- PROBANDO ACA\n3-PrePacientes\4-\n");
    scanf("%i",&optionswitch);
    FILE *archi;
    stPaciente aux;
    switch(optionswitch)
    {
    case 1:
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
        break;
    case 2:
        archi = abrirArchivo("Heroes.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,archi) > 0 )
        {
            mostrarUnPaciente(aux);
            validos++;
        }
        fclose(archi);
        system("pause");
        system("cls");
        return validos;
        break;
    case 3:
        archi = abrirArchivo("PrePacientes.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,archi) > 0 )
        {
            mostrarUnPaciente(aux);
            validos++;
        }
        fclose(archi);
        return validos;
        break;
    case 4 :
        archi = abrirArchivo("PacientesSanti.bin","rb");
        while (fread(&aux,sizeof(stPaciente),1,archi) > 0 )
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
        fclose(archi);
        return validos;
        break;
    }
    return 0;
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
    scanf(" %c",&alta);
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
    stPaciente busqueda;
    printf("Ingrese el DNI del paciente a modificar\n");
    getchar();
    fgets(aux,10,stdin);
    borrarSaltoDeLinea(aux);
    while (fread(&busqueda,sizeof(stPaciente),1,archi) > 0)
    {
        printf("asd");
        if (strcmpi(aux, busqueda.dni) == 0)
        {
            printf("Encontrado\n");
            menuModificarPaciente(pos+1);
            break;
        }
        pos++;
    }
    fclose(archi);
}

void menuModificarPaciente (int pos)
{
    int optionswitch;
//    system("cls");
    printf("El paciente ha sido encontrado.\Ingrese el dato a modificar:\n1-Nombre\n2-Apellido\n3-Movil\n0-Salir\n");
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
    do
    {
        printf("pos : %i",pos);
        printf("Ingrese el nombre actualizado del paciente:\n");
        getchar();
        fgets(aux, 30,stdin);
        if (strchr(aux,'\n') != NULL) ///
        {
            borrarSaltoDeLinea(aux);
            if (ingresarSoloLetrasSinEspacios(aux) == 1)
            {
                printf("Nombre dentro de los parametros acordados\n");
                flag = 1;
            } else printf("Ingrese solamente letras por favor :) \n");

        }
        else
        {
            while (getchar () != '\n'); ///
            printf("No se pueden ingresar mas de 30 numeros\n");
        }
    }while (flag == 0);
    FILE *archi = abrirArchivo("TestPacientes.bin","r+b");
    fseek(archi,(pos-1) * sizeof(stPaciente),SEEK_SET);
    fread(&auxiliar,sizeof(stPaciente),1,archi);
    primerLetraMayuscula(aux);
    strcpy(auxiliar.nombre,aux);
    fseek(archi, -sizeof(stPaciente),SEEK_CUR);
    fwrite(&auxiliar,sizeof(stPaciente),1,archi);
    fclose(archi); /// Copia el nombre cargado por usuario (aux) en la estructura
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
            borrarSaltoDeLinea(nuevoApellido);
            if (ingresarSoloLetrasSinEspacios(nuevoApellido) == 1)
            {
                printf("Nombre dentro de los parametros acordados\n");
                primerLetraMayuscula(nuevoApellido);
                flag = 1;
            } else printf("Ingrese solamente letras por favor :) \n");
        }
        else
        {
            while (getchar () != '\n');
            printf("No se pueden ingresar mas de 30 letras\n");
        }
    }
    while (flag == 0);

    FILE *archi = abrirArchivo("TestPacientes.bin","r+b");
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
    fseek(archi, -sizeof(stPaciente),SEEK_CUR);
    fwrite(&aux,sizeof(stPaciente),1,archi);
    fclose(archi);
}

void cambiarMovilPaciente(int pos)
{
    char nuevoMovil [12];
    stPaciente aux;
    int flag = 0;
    do
    {
        printf("Ingrese el celular actualizado del paciente:\n");
        getchar();
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

    FILE *archi = abrirArchivo("TestPacientes.bin","r+b");
    fseek(archi,(pos-1)* sizeof(stPaciente), SEEK_SET);
    fread(&aux,sizeof(stPaciente),1,archi);
    fseek(archi,-sizeof(stPaciente),SEEK_CUR);
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

    FILE *archi = abrirArchivo("TestPacientes.bin","r+b");
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
    FILE *archi = abrirArchivo("TestPacientes.bin","r+b");
    while (fread(&paciente,sizeof(stPaciente),1,archi) > 0 )
    {
//        printf("AUX: %s||DNI P: %s\n",aux,paciente.dni); /// borrar desp, viendo posiciones
        if (strcmpi(aux,paciente.dni) == 0 && paciente.eliminado == 0)
        {
            contadorPos = i ;
            printf("Paciente encontrado.\n");
            paciente.eliminado = 1;
            eliminado = paciente; /// Copia el paciente para que no cambie en la nueva iteracion del bucle
            flag = 1; /// Cambia flag para que no printee que no se ha encontrado ningun paciente
        }
        else if (strcmpi(aux,paciente.dni) == 0 & paciente.eliminado == 1)
        {
            printf("El paciente:%s, %s esta actualmente dado de baja.\n",paciente.apellido,paciente.nombre);
            flag = 1; /// Cambia flag para que no printee que no se ha encontrado ningun paciente
        }
        i++;
    }
//        printf("Posicion:%i",contadorPos); /// borrar desp, probando posiciones
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
    scanf("%i",&optionswitch);
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
            return flag;
        }
    }
    fclose(archi);
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
    FILE *archi = abrirArchivo("TestPacientes.bin","r + b");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }
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
//            printf("validos ADP :%i", *validosADP);
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
//    else printf("Memoria asignada correctamente\n");
    ADP[(*validosADP)-1] = paciente; /// num arranca valiendo 1

//    printf("antes del return\n");
//    printf("num vale:%i en creando AD\n",*validosADP);

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
    system("pause");
    system("cls");
}


int findMinorChar(stPaciente * ADR, int validosADP, int posicion)
{
    char aux;
    int posicionMenor = posicion;
    int subindice = posicion + 1;
    char menor[30];/// = ADR[posicion].apellido[0];
    borrarSaltoDeLinea(menor);
    char menorNombre[30]; /// Guarda nombre arrancando en 0 para comparar con 1
    strcpy(menorNombre,ADR[posicion].nombre);
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
}

/// ----------------------------------------------------- O R D E N A R ------------ P A C I E N T E   ------------------------------------------------------ ///

///------------------------------------------------------- BORRAR DESPUES--------------------------------------------------
int busquedaPorDNIDOS (char DNI[])
{
    stPaciente aux;
    FILE * archi = abrirArchivo("Heroes.bin","rb");
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
            return flag;
        }
    }
    fclose(archi);
    return flag; /// si flag 0 paciente encontrado
}

///------------------------------------------------------- BORRAR DESPUES--------------------------------------------------

void menuMostrarLaboratoriosPorPaciente ()
{
    system("cls");
    int optionswitch = 0;
    do
    {
        printf("1-Mostrar laboratorios de paciente por ID\n");
        printf("2-Listado de todos los laboratorios por pacientes.\n");
        printf("0-Volver al menu anterior.\n");
        scanf("%i",&optionswitch);
        switch (optionswitch)
        {
        case 1:
            laboratoriosPorPacienteID();
            break;
        case 2:
            mostrarTodosLaboratoriosPorPaciente();
            break;
        case 0:
            system("pause");
            system("cls");
            break;
        default :
            printf("Opcion incorrecta.\n");
            break;
        }
    } while (optionswitch != 0);
}

void laboratoriosPorPacienteID () /// Ingresa DNI para buscar despues por ID
{
    system("cls");
    char DNI [12];
    printf("Ingrese el DNI de paciente a buscar.\n");
    getchar();
    fgets(DNI,10,stdin);
    borrarSaltoDeLinea(DNI);
    int flag = busquedaPorDNIDOS(DNI);
    if (flag == 0)
    {
        /// hasta aca bien
        mostrarLaboratoriosUnPaciente(DNI);
    }
    else printf("El DNI no está activo en nuestros registros.\n");
}

void mostrarLaboratoriosUnPaciente (char DNI[]) ///
{
    FILE *archi = abrirArchivo("TestLaboratorios.bin","rb");
    FILE *bin = abrirArchivo("Heroes.bin","rb");
    char practicaRealizada[30]; /// Practica a traer de funcion para printear
    if (archi == NULL || bin == NULL)
    {
        printf("Error al abrir los registros.\n");
        return;
    }
    int ID = 0;
    stLaboratorios lab;
    stPaciente paciente;
    char nombrePaciente[30];
    char apellidoPaciente [30];
    int precio = 0;
    int total = 0;
    while (fread(&paciente,sizeof(stPaciente),1,bin) > 0 ) /// Conseguimos el ID del paciente a traves de su DNI
    {
        if (strcmpi(DNI,paciente.dni) == 0 )
        {
            strcpy(nombrePaciente,paciente.nombre);
            strcpy(apellidoPaciente,paciente.apellido);
            mostrarUnPaciente(paciente);
            printf("ID Encontrado.%i\n",paciente.idPaciente);
            ID = paciente.idPaciente;
        }
    }
    printf("Paciente :%s, %s\n", apellidoPaciente, nombrePaciente);
    while (fread(&lab,sizeof(stLaboratorios),1,archi) > 0 ) /// Buscamos el ID del paciente en los registros de los laboratorios
    {
        if (lab.idPaciente == ID)
        {
///            buscarPracticasRealizadas(lab.idLab,practicaRealizada,&precio); /// Buscamos el nombre de la practica a traves de su ID

            mostrarUnLaboratorio(DNI,practicaRealizada,precio,lab.anio,lab.mes,lab.dia,lab.idLab); /// Printeamos el nombre de la practica que el paciente se realizo
            total += precio;
        }
    }
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("El gasto total del paciente fue de :%i\n",total);
    fclose(archi);
    fclose(bin);
    system("pause");
    system("cls");
}

void buscarPracticasRealizadas(int practicaID, char practicaRealizada[],int *precio)
{
    FILE *archi = abrirArchivo("TestPracticas.bin","rb");
    stPracticas aux;
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }
    while (fread(&aux,sizeof(stPracticas),1,archi) > 0 )
    {
        if (practicaID == aux.idPractica)
        {
            strcpy(practicaRealizada,aux.nombre);
            *precio = aux.costo;
        }
    }
    fclose(archi);
}

void mostrarTodosLaboratoriosPorPaciente ()
{
    system("cls");
    FILE *archi = abrirArchivo("Heroes.bin","rb");
    FILE *bin = abrirArchivo("TestLaboratorios.bin","rb");
    stPaciente auxPaciente;
    stLaboratorios auxLab;
    int encontrado = 0;
    int precio = 0;
    int aux = 0;
    int cant = 0;
    char practicaRealizada[30]; /// String a traer y printear
    if (archi == NULL || bin == NULL)
    {
        printf("Error al recorrer registros.\n");
        return;
    }
    while (fread(&auxPaciente,sizeof(stPaciente),1,archi) > 0 )
    {
        fseek(bin,0,SEEK_SET);
        if (auxPaciente.eliminado == 0)
        {
            encontrado = 0;
           while (fread(&auxLab,sizeof(stLaboratorios),1,bin) > 0 )
        {
            if (auxPaciente.idPaciente == auxLab.idPaciente)
            {
                if (encontrado == 0) /// Hace que se printee solamente una vez el nombre del paciente.
                {
                    printf("***********************************************************************************************************************************************\n");
                    printf("Nombre del paciente:%s, %s\n", auxPaciente.apellido,auxPaciente.nombre);
                    encontrado = 1;
                }
                buscarPracticasRealizadas(auxLab.practicaRealizada,practicaRealizada,&precio);
                mostrarUnLaboratorio(auxPaciente.nombre,practicaRealizada,precio,auxLab.anio,auxLab.mes,auxLab.dia,auxLab.idLab);
            }
        }
        }
    }
    fclose(archi);
    fclose(bin);
    system("pause");
    system("cls");
}

void mostrarUnLaboratorio (char nombre[], char practica[], int precio, int anio , int mes, int dia, int id)
{
    printf("------------------------------------------------\n");
    printf("Fecha : %i - %i - %i\n", dia,mes,anio);
    printf("Nombre de la practica:%s\n",practica);
    printf("Precio de la practica:%i\n",precio);
    printf("ID Practica:%i\n",id); /// capaz borrar desp
}

/// --------------------------------------- ORDENAR LABORATORIOS POR FECHA ------------------------------------------------------------------------------ ///

stLaboratorios * arregloDinamicoLaboratoriosPorFecha (int *validosOrdenamiento)
{
    FILE *archi = abrirArchivo("TestLaboratorios.bin","rb");
    rewind(archi);
    stLaboratorios *arregloDinamico = NULL;
    stLaboratorios lab;
    int pos = 0;
    while (fread(&lab,sizeof(stLaboratorios),1,archi) > 0)
    {
        arregloDinamico = asignarMemoriaLaboratoriosPorFecha(arregloDinamico, lab,pos);
        pos++;
        (*validosOrdenamiento)++;
    }
    fclose(archi);
    return arregloDinamico;
}

stLaboratorios * asignarMemoriaLaboratoriosPorFecha (stLaboratorios * arregloOrdenamiento, stLaboratorios lab, int pos)
{
//    printf("Entra");
    arregloOrdenamiento  = realloc (arregloOrdenamiento, (pos + 1) * sizeof(stLaboratorios));
    if (arregloOrdenamiento == NULL)
    {
        printf("Error al asignar memoria\n");
    }
    arregloOrdenamiento[pos] = lab;
    mostrarUnLaboratorio("nombre","practica",5,arregloOrdenamiento[pos].anio,arregloOrdenamiento[pos].mes,arregloOrdenamiento[pos].dia,arregloOrdenamiento[pos].idLab);
    return arregloOrdenamiento;
}

int fechaAEntero (stLaboratorios lab) /// Vuelve toda la fecha en un numero entero ej(20260710) para hacer un ordenamiento solo y no tener que hacer un ordenamiento por tipo de variable
{
    int fecha = 0;
    fecha += lab.anio * 10000;
    fecha += lab.mes * 100;
    fecha += lab.dia;

    return fecha;
}

int findMinorFecha(stLaboratorios arreglo[], int validos, int posicion)
{
    int aux;
    int posicionMenor = posicion;
    stLaboratorios menor;
    int subindice = posicion + 1;
    while (subindice < validos)
    {
        if (fechaAEntero(arreglo[subindice]) > fechaAEntero(arreglo[posicionMenor]))
        {
            posicionMenor = subindice;
            menor = arreglo[subindice];
        }
        subindice++;
    }
    return posicionMenor;
}

void ordenamientoSeleccionFecha(stLaboratorios arreglo[], int validos)
{
    stLaboratorios aux;
    int posicionMenor = 0;
    int i = 0;

    while ( i < validos - 1)
    {
        posicionMenor = findMinorFecha(arreglo, validos, i);
        aux = arreglo[i];
        arreglo[i] = arreglo[posicionMenor];
        arreglo[posicionMenor] = aux;
        i++;
    }
}

void mostrarLaboratoriosOrdenadosPorfecha (stLaboratorios arreglo[],int validos)
{
    FILE *archi = abrirArchivo("Heroes.bin","rb");
    stPaciente aux;
    int precio = 0;
    char nombrePractica[30];
    if (archi == NULL)
    {
        return;
    }
    for (int i = 0; i < validos; i++)
    {
        fseek(archi,0,SEEK_SET);
        while (fread(&aux,sizeof(stPaciente),1,archi) > 0 )
        {
            if(arreglo[i].idPaciente == aux.idPaciente && aux.eliminado == 0)
            {
                buscarPracticasRealizadas(arreglo[i].practicaRealizada,nombrePractica, &precio);
                printf("Fecha : %i-%i-%i\nPaciente:%s, %s, %s\nPractica realizada:%s\n",
                       arreglo[i].dia,arreglo[i].mes,arreglo[i].anio,
                       aux.apellido,aux.nombre,aux.dni,
                       nombrePractica);;
                printf("----------------------------------------\n");
            }
        }
    }


    fclose(archi);
    system("pause");
    system("cls");
}




/// --------------------------------------- ORDENAR LABORATORIOS POR FECHA ------------------------------------------------------------------------------ ///



/// --------------------------------------- T E S T    A R C H I V O S ------------------------------------------------------------------------------ ///


void cargarPacientesAB()
{
    FILE *archi = abrirArchivo("Heroes.bin", "wb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }

    stPaciente pacientes[30] = {
        {51, "Tanjiro",   "Kamado",       "30100051", "2215560051", 0},
        {52, "Nezuko",    "Kamado",       "30100052", "2215560052", 1},
        {53, "Zenitsu",   "Agatsuma",     "30100053", "2215560053", 0},
        {54, "Inosuke",   "Hashibira",    "30100054", "2215560054", 0},
        {55, "Giyu",      "Tomioka",      "30100055", "2215560055", 1},
        {56, "Izuku",     "Midoriya",     "30100056", "2215560056", 0},
        {57, "Katsuki",   "Bakugo",       "30100057", "2215560057", 0},
        {58, "Shoto",     "Todoroki",     "30100058", "2215560058", 1},
        {59, "Ochaco",    "Uraraka",      "30100059", "2215560059", 0},
        {60, "Tenya",     "Iida",         "30100060", "2215560060", 0},
        {61, "Yusuke",    "Urameshi",     "30100061", "2215560061", 0},
        {62, "Kurama",    "Youko",        "30100062", "2215560062", 1},
        {63, "Hiei",      "Jaganshi",     "30100063", "2215560063", 0},
        {64, "Kazuma",    "Kuwabara",     "30100064", "2215560064", 0},
        {65, "Rurouni",   "Kenshin",      "30100065", "2215560065", 1},
        {66, "Sanosuke",  "Sagara",       "30100066", "2215560066", 0},
        {67, "Aang",      "Airbender",    "30100067", "2215560067", 0},
        {68, "Katara",    "Waterbender",  "30100068", "2215560068", 0},
        {69, "Zuko",      "Firelord",     "30100069", "2215560069", 1},
        {70, "Toph",      "Beifong",      "30100070", "2215560070", 0},
        {71, "Peter",     "Parker",       "30100071", "2215560071", 0},
        {72, "Miles",     "Morales",      "30100072", "2215560072", 1},
        {73, "Bruce",     "Wayne",        "30100073", "2215560073", 0},
        {74, "Clark",     "Kent",         "30100074", "2215560074", 0},
        {75, "Diana",     "Prince",       "30100075", "2215560075", 0},
        {76, "Barry",     "Allen",        "30100076", "2215560076", 1},
        {77, "Arthur",    "Curry",        "30100077", "2215560077", 0},
        {78, "Wanda",     "Maximoff",     "30100078", "2215560078", 0},
        {79, "Stephen",   "Strange",      "30100079", "2215560079", 1},
        {80, "T'Challa",  "Wakanda",      "30100080", "2215560080", 0},
    };

    for (int i = 0; i < 30; i++)
    {
        fwrite(&pacientes[i], sizeof(stPaciente), 1, archi);
    }

    printf("30 pacientes agregados correctamente.\n");
    fclose(archi);
}

void cargarPracticaTest()
{
    FILE *archi = abrirArchivo("TestPracticas.bin", "wb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }

    stPracticas practicas[15] = {
        {1,  "Hemograma completo",   2500, 0},
        {2,  "Glucemia",             1500, 0},
        {3,  "Colesterol total",     2000, 0},
        {4,  "Orina completa",       1800, 0},
        {5,  "Radiografia torax",    4500, 0},
        {6,  "Electrocardiograma",   5000, 0},
        {7,  "Ecografia abdominal",  8000, 0},
        {8,  "Coagulograma",         3000, 0},
        {9,  "Hepatograma",          3500, 0},
        {10, "Creatinina",           2200, 0},
        {11, "Urea",                 1800, 0},
        {12, "Trigliceridos",        2000, 0},
        {13, "TSH tiroides",         4000, 0},
        {14, "Vitamina D",           5500, 1},
        {15, "Proteina C reactiva",  3200, 0},
    };

    for (int i = 0; i < 15; i++)
    {
        fwrite(&practicas[i], sizeof(stPracticas), 1, archi);
    }

    printf("15 practicas cargadas correctamente.\n");
    fclose(archi);
    archi = abrirArchivo("TestPracticas.bin","rb");
    stPracticas aux;
    while (fread(&aux,sizeof(stPracticas),1,archi) > 0 )
    {
        printf("Nombre de la practica:%s\nID:%i\nCosto:%i\nEstado:%i\n",
               aux.nombre,
               aux.idPractica,
               aux.costo,
               aux.baja);
        printf("---------------------------------------------------------------------\n");
    }
    fclose(archi);
}

void cargarLaboTest()
{
    FILE *archi = fopen("TestLaboratorios.bin", "wb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }

    stLaboratorios labs[40] = {
        /// Tanjiro Kamado - ID 51 (activo)
        {1,  51, 2024, 1, 10, 1,  0},
        {2,  51, 2024, 3, 22, 5,  0},
        {3,  51, 2024, 6, 15, 9,  0},

        /// Zenitsu Agatsuma - ID 53 (activo)
        {4,  53, 2023, 11, 5,  2,  0},
        {5,  53, 2024, 2, 18, 6,  0},

        /// Inosuke Hashibira - ID 54 (activo)
        {6,  54, 2024, 4, 30, 3,  0},
        {7,  54, 2024, 7, 12, 10, 0},

        /// Izuku Midoriya - ID 56 (activo)
        {8,  56, 2023, 9, 20, 4,  0},
        {9,  56, 2024, 1, 8,  7,  0},
        {10, 56, 2024, 5, 25, 13, 0},

        /// Katsuki Bakugo - ID 57 (activo)
        {11, 57, 2024, 3, 14, 8,  0},
        {12, 57, 2024, 8, 1,  15, 0},

        /// Ochaco Uraraka - ID 59 (activo)
        {13, 59, 2023, 12, 3,  1,  0},
        {14, 59, 2024, 4, 17, 11, 0},

        /// Tenya Iida - ID 60 (activo)
        {15, 60, 2024, 2, 28, 2,  0},
        {16, 60, 2024, 6, 9,  12, 0},

        /// Yusuke Urameshi - ID 61 (activo)
        {17, 61, 2023, 10, 15, 3,  0},
        {18, 61, 2024, 1, 22, 6,  1},  /// baja logica

        /// Hiei Jaganshi - ID 63 (activo)
        {19, 63, 2024, 5, 11, 4,  0},
        {20, 63, 2024, 9, 3,  9,  0},

        /// Kazuma Kuwabara - ID 64 (activo)
        {21, 64, 2023, 8, 27, 5,  0},
        {22, 64, 2024, 3, 19, 14, 0},

        /// Sanosuke Sagara - ID 66 (activo)
        {23, 66, 2024, 7, 4,  7,  0},
        {24, 66, 2024, 10, 21,10, 0},

        /// Aang Airbender - ID 67 (activo)
        {25, 67, 2023, 6, 30, 8,  0},
        {26, 67, 2024, 2, 14, 15, 0},

        /// Katara Waterbender - ID 68 (activo)
        {27, 68, 2024, 1, 5,  1,  0},
        {28, 68, 2024, 4, 28, 11, 0},

        /// Toph Beifong - ID 70 (activo)
        {29, 70, 2023, 11, 18, 2,  0},
        {30, 70, 2024, 6, 7,  13, 0},

        /// Peter Parker - ID 71 (activo)
        {31, 71, 2024, 3, 25, 3,  0},
        {32, 71, 2024, 8, 16, 6,  1},  /// baja logica

        /// Bruce Wayne - ID 73 (activo)
        {33, 73, 2023, 7, 12, 4,  0},
        {34, 73, 2024, 5, 30, 9,  0},

        /// Clark Kent - ID 74 (activo)
        {35, 74, 2024, 2, 22, 5,  0},
        {36, 74, 2024, 9, 10, 12, 0},

        /// Diana Prince - ID 75 (activo)
        {37, 75, 2023, 9, 8,  7,  0},
        {38, 75, 2024, 4, 3,  15, 0},

        /// Arthur Curry - ID 77 (activo)
        {39, 77, 2024, 6, 19, 8,  0},

        /// T'Challa Wakanda - ID 80 (activo)
        {40, 80, 2024, 7, 28, 10, 0},
    };

    for (int i = 0; i < 40; i++)
    {
        fwrite(&labs[i], sizeof(stLaboratorios), 1, archi);
    }

    printf("40 laboratorios cargados correctamente.\n");
    fclose(archi);
    stLaboratorios aux;
    archi = fopen("TestLaboratorios.bin","rb");
    int i =0;
    while (fread(&aux,sizeof(stLaboratorios),1,archi) > 0 )
    {

        printf("ID Paciente:%i\nPractica realizada:%i\nID Lab:%i\nFecha: %i - %i - %i\n pos %i",
               aux.idPaciente,
               aux.practicaRealizada,
               aux.idLab,
               aux.dia,
               aux.mes,
               aux.anio,
               i
               );
        printf("\n-----------------------------------------------------------------\n");
        i++;
    }
}

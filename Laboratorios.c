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

/// ---------------------------------------------- C A R G A  - L A B O R A T O R I O  ------------------------------------------------------------------

void cargarLaboratorio(stLaboratorios *lab) /// Duda si agregar pac y prac.
{

    FILE *Laboratorios;
    Laboratorios = abrirArchivo(ARCHIVO_LABORATORIOS, "ab");

    char seguir = 'n';
    lab->idLab = getIDVLaboratorio();
    printf("ID asignado: %d\n", lab->idLab);

    do
    {
        lab->anio = validarAnio();
        lab ->mes = validarMes();
        lab ->dia = validarDia(lab ->mes);

        printf("Ingrese ID del paciente: ");
        lab->idPaciente = buscandoIDPacientes();


//        scanf("%d",&lab->idPaciente);

        printf("Ingrese ID de practica: ");
        lab->practicaRealizada = buscandoIDPractica();
//        scanf("%d", &lab->practicaRealizada);

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

    FILE *archi = abrirArchivo(ARCHIVO_LABORATORIOS, "r+b");
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
    system("pause");
    system("cls");
    fclose(archi);
}
/// ---------------------------------------------- C A R G A  ----- L A B O R A T O R I O  ------------------------------------------------------------------



/// ---------------------------------------------- M U E S T R A -- L A B O R A T O R I O   ------------------------------------------------------------------



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
     system("pause");
    system("cls");
}
void mostrarLaboratoriosArchivo()
{
    FILE *archi = abrirArchivo(ARCHIVO_LABORATORIOS, "rb");
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
    system("pause");
    system("cls");
}

/// ---------------------------------------------- M O D I F I C A R --- L A B O R A T O R I O  ------------------------------------------------------------------


void modificarLaboratorio()
{
    int idBuscar;
    int pos = 0;
    int posEncontrado = -1;
    stLaboratorios lab;

    printf("Ingrese ID de Lab a modificar:\n ");
    scanf("%d", &idBuscar);

    FILE *archi = abrirArchivo(ARCHIVO_LABORATORIOS, "r+b");
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
        printf("Fecha actualizada correctamente.\n");
        system("pause");
        system("cls");
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
    int precio; /// para pasar parametro, pero no necesitamos acá pasar el precio
    char nombre[30]; /// nombre para printear del paciente
    char apellido[30];/// apellido para printear del paciente
    char nombrePractica[30];
    printf("Ingresar ID del laboratorio a consultar: ");
    scanf("%d", &idBuscar);

    FILE *archi = abrirArchivo(ARCHIVO_LABORATORIOS, "rb");
    if (archi == NULL)
    {
        printf("Error al abrir");
        return;
    }

    while (fread(&lab, sizeof(stLaboratorios), 1, archi)> 0)
    {
        if (lab.idLab == idBuscar && lab.baja == 0)
        {
            buscarPracticasRealizadas(lab.practicaRealizada,nombrePractica,&precio);
            encontrarDatosPaciente(lab.idPaciente,nombre,apellido);
                    printf("--------------------------------------------------\n");
                   printf("ID laboratorio: %d\nPaciente: %s, %s\nPractica: %s\nFecha : %i-%i-%i\n",
                   lab.idLab,
                   apellido,
                   nombre,
                   nombrePractica,
                   lab.dia,
                   lab.mes,
                   lab.anio);
                   printf("--------------------------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0)

        printf("Laboratorio no encontrado o de baja");

    fclose(archi);
    system("pause");
    system("cls");
}

void encontrarDatosPaciente (int id, char nombre[], char apellido[])
{
    stPaciente aux;
    FILE * archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    int flag = 1;
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return ;
    }
    while (fread(&aux,sizeof(stPaciente),1,archi) > 0)
    {
        if (id == aux.idPaciente)
        {
            mostrarUnPaciente(aux);
            strcpy(nombre,aux.nombre);
            strcpy(apellido,aux.apellido);
            flag = 0;
            system("pause");
            system("cls");
        }
    }
    fclose(archi);
}
int buscandoIDPacientes() /// rafa probando busca id - - - - - - - funcion en utilities /// Integrar solo int
{
    int newID = 0;
    int aux;
    char confirmar;
    do
    {
        printf("Ingrese el ID a buscar:\n");
    scanf("%i",&newID);
    aux = compararIDLP(newID);
    if ( aux == 0)
    {
        printf("El id ha sido encontrado.\n");
        return newID;
    }
    else if (aux == 1)
    {
//        printf("Desea ingresar otro ID?S/N\n");
//        scanf(" %c", &confirmar);
//        if (tolower(confirmar) == 's')
//        {
//
//        }
        printf("El ID no existe. Ingrese un ID valido por favor.\n");
    }
    } while (aux != 0);
}

int buscandoIDPractica() /// rafa probando busca id - - - - - - - funcion en utilities /// Integrar solo int
{
    int newID = 0;
    int aux;
    do
    {
        printf("Ingrese el ID a buscar:\”");
    scanf("%i",&newID);
    aux = compararIDLPrac(newID);
    if ( aux == 0)
    {
        printf("El id ha sido encontrado.\n");
        return newID;
    }
    else if (aux == 1)
    {
        printf("El ID no existe. Si desea crear uno vaya al apartado pacientes.\n");
    }
    } while (aux != 0);

    return 1;
}

void muestraTSP () /// TEST SANTI PACIENTES
{
    printf("entra");
    stPaciente aux;
    FILE *archi = abrirArchivo ("PacientesSanti.bin","rb");
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
    FILE * archi = abrirArchivo ("PracticasSanti.bin","rb");
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


/// ----------------------------------------------------- O R D E N A R ------------ P A C I E N T E   ------------------------------------------------------ ///
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
    int flag = busquedaPorDNI(DNI);
    if (flag == 0)
    {
        /// hasta aca bien
        mostrarLaboratoriosUnPaciente(DNI);
    }
    else printf("El DNI no está activo en nuestros registros.\n");
}

void mostrarLaboratoriosUnPaciente (char DNI[]) ///
{
    FILE *archi = abrirArchivo(ARCHIVO_LABORATORIOS,"rb");
    FILE *bin = abrirArchivo(ARCHIVO_PACIENTES,"rb");
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
            printf("ID del paciente:%i\n",paciente.idPaciente);
            ID = paciente.idPaciente; /// ID a enviar a laboratorio
        }
    }
    printf("Paciente :%s, %s\n", apellidoPaciente, nombrePaciente);
    while (fread(&lab,sizeof(stLaboratorios),1,archi) > 0 ) /// Buscamos el ID del paciente en los registros de los laboratorios
    {
        if (lab.idPaciente == ID) /// Trae precio total, monto de practica y nombre de practica
        {
            buscarPracticasRealizadas(lab.practicaRealizada,practicaRealizada,&precio); /// Buscamos el nombre de la practica a traves de su ID
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
    FILE *archi = abrirArchivo(ARCHIVO_PRACTICAS,"rb");
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
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
    FILE *bin = abrirArchivo(ARCHIVO_LABORATORIOS,"rb");
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
    FILE *archi = abrirArchivo(ARCHIVO_LABORATORIOS,"rb");
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
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"rb");
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


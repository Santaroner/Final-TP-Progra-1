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
    stPaciente aux;
    FILE *archi = fopen (ARCHIVO_PACIENTES,"rb"); /// CAMBIAR MAS ADELANTE POR EL ORIGINALm Pacientes santi para practicar ahora
    while (fread(&aux,sizeof(stPaciente),1,archi))
    {
        if (num == aux.idPaciente && aux.eliminado == 0)
        {
            printf("ID Encontrado. ID:%i\n",aux.idPaciente);
            fclose(archi);
            return 0;
        }
    }
    fclose(archi);
    return 1;
}
int compararIDLPrac (int num)
{
    stPracticas aux;
    FILE *archi = fopen (ARCHIVO_PRACTICAS,"rb");
    while (fread(&aux, sizeof(stPracticas), 1, archi))
    {
        if (num == aux.idPractica && aux.baja == 0)
        {
            printf("ID Encontrado. ID:%i\n",aux.idPractica);
            fclose(archi);
            return 0;
        }
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
    if (archi != NULL)
    {
        while (fread(&aux, sizeof(stLaboratorios),1,archi) > 0)
        {
            IDAux++;
        }
        fclose(archi);
    }
    IDAux++;
    return IDAux;
}

/// ----------------------------- PRE CARGA PARA TEST DE ARCHIVOS



/// -------------- FUNCIONES ANTI ADRIAN ---- solo numeros ///

void borrarSaltoDeLinea(char cadena[])
{
    cadena[strcspn(cadena,"\n")] = '\0';
}

FILE * abrirArchivo (char nombreArchivo[],char modo[])
{
    FILE *archi = fopen(nombreArchivo,modo);
    if (archi == NULL)
    {
        printf("Error al abrir archivo\n");
    }
//    else printf("Trabajando sobre el archivo.\n"); /// borrar despues

    return archi;
}
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

int ingresarEnteroMinMax(int min, int max)
{
    int numero;
    int control;

    do
    {
        control = scanf("%i",&numero); /// Si el scanf devuelve 1
        if (control != 1)
        {
            printf("Error, ingrese un numero.\n");
            while(getchar () != '\n'); /// limpia num
        }
        else if(numero < min || numero > max)
        {
            printf("Error, el numero debe estar entre %i y %i\n",min,max);
            control = 0;
        }



    } while (control != 1); /// control devuelve 1 si el dato ingresado por el scanf es un numero

    return numero;
}

/// VALIDACIONES

char * primerLetraMayuscula (char cadena[])
{
    if (cadena != '\0')
    {
        cadena[0] = toupper(cadena[0]);
        return cadena;
    }
}

/// --------------------------------------- T E S T    A R C H I V O S ------------------------------------------------------------------------------ ///



void resetearArchivos()
{
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES,"wb");
    FILE *temp = abrirArchivo(ARCHIVO_PRACTICAS, "wb");
    FILE *bin = abrirArchivo (ARCHIVO_LABORATORIOS, "wb");

    if (temp == NULL || bin == NULL || archi == NULL)
    {
        printf("Error al abrir y resetear archivos.\n");
        return;
    }
    else printf("Archivos vaciados correctamente.\n");
    fclose(archi);
    fclose(bin);
    fclose(temp);
}

void cargarPacientesAB()
{
    FILE *archi = abrirArchivo(ARCHIVO_PACIENTES, "wb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }

    stPaciente pacientes[60] = {
        /* ID  Nombre          Apellido        DNI          Telefono        Baja */
        { 1,  "Lionel",       "Messi",        "30200001",  "2215560001",   0},
        { 2,  "Cristiano",    "Ronaldo",      "30200002",  "2215560002",   0},
        { 3,  "Pele",         "Nascimento",   "30200003",  "2215560003",   1},
        { 4,  "Diego",        "Maradona",     "30200004",  "2215560004",   1},
        { 5,  "Ronaldo",      "Nazario",      "30200005",  "2215560005",   0},
        { 6,  "Zinedine",     "Zidane",       "30200006",  "2215560006",   0},
        { 7,  "Ronaldinho",   "Gaucho",       "30200007",  "2215560007",   0},
        { 8,  "Luka",         "Modric",       "30200008",  "2215560008",   0},
        { 9,  "Andres",       "Iniesta",      "30200009",  "2215560009",   1},
        {10,  "Xavi",         "Hernandez",    "30200010",  "2215560010",   0},
        {11,  "Neymar",       "Junior",       "30200011",  "2215560011",   0},
        {12,  "Kylian",       "Mbappe",       "30200012",  "2215560012",   0},
        {13,  "Erling",       "Haaland",      "30200013",  "2215560013",   0},
        {14,  "Vinicius",     "Junior",       "30200014",  "2215560014",   0},
        {15,  "Kevin",        "De Bruyne",    "30200015",  "2215560015",   1},
        {16,  "Robert",       "Lewandowski",  "30200016",  "2215560016",   0},
        {17,  "Mohamed",      "Salah",        "30200017",  "2215560017",   0},
        {18,  "Karim",        "Benzema",      "30200018",  "2215560018",   0},
        {19,  "Sadio",        "Mane",         "30200019",  "2215560019",   1},
        {20,  "Harry",        "Kane",         "30200020",  "2215560020",   0},
        {21,  "Antoine",      "Griezmann",    "30200021",  "2215560021",   0},
        {22,  "Paulo",        "Dybala",       "30200022",  "2215560022",   0},
        {23,  "Sergio",       "Aguero",       "30200023",  "2215560023",   1},
        {24,  "Angel",        "Di Maria",     "30200024",  "2215560024",   0},
        {25,  "Gabriel",      "Batistuta",    "30200025",  "2215560025",   0},
        {26,  "Hernan",       "Crespo",       "30200026",  "2215560026",   1},
        {27,  "Juan Roman",   "Riquelme",     "30200027",  "2215560027",   0},
        {28,  "Thierry",      "Henry",        "30200028",  "2215560028",   0},
        {29,  "Didier",       "Drogba",       "30200029",  "2215560029",   0},
        {30,  "Samuel",       "Eto",          "30200030",  "2215560030",   1},
        {31,  "Zlatan",       "Ibrahimovic",  "30200031",  "2215560031",   0},
        {32,  "Wayne",        "Rooney",       "30200032",  "2215560032",   0},
        {33,  "Steven",       "Gerrard",      "30200033",  "2215560033",   1},
        {34,  "Frank",        "Lampard",      "30200034",  "2215560034",   0},
        {35,  "Patrick",      "Vieira",       "30200035",  "2215560035",   0},
        {36,  "Paul",         "Scholes",      "30200036",  "2215560036",   1},
        {37,  "Ryan",         "Giggs",        "30200037",  "2215560037",   0},
        {38,  "David",        "Beckham",      "30200038",  "2215560038",   0},
        {39,  "Roberto",      "Carlos",       "30200039",  "2215560039",   0},
        {40,  "Cafu",         "Nascimento",   "30200040",  "2215560040",   1},
        {41,  "Paolo",        "Maldini",      "30200041",  "2215560041",   0},
        {42,  "Franco",       "Baresi",       "30200042",  "2215560042",   0},
        {43,  "Fabio",        "Cannavaro",    "30200043",  "2215560043",   1},
        {44,  "Carles",       "Puyol",        "30200044",  "2215560044",   0},
        {45,  "Gerard",       "Pique",        "30200045",  "2215560045",   0},
        {46,  "Sergio",       "Ramos",        "30200046",  "2215560046",   0},
        {47,  "Rio",          "Ferdinand",    "30200047",  "2215560047",   1},
        {48,  "Virgil",       "Van Dijk",     "30200048",  "2215560048",   0},
        {49,  "Gianluigi",    "Buffon",       "30200049",  "2215560049",   0},
        {50,  "Iker",         "Casillas",     "30200050",  "2215560050",   1},
        {51,  "Manuel",       "Neuer",        "30200051",  "2215560051",   0},
        {52,  "Oliver",       "Kahn",         "30200052",  "2215560052",   0},
        {53,  "Peter",        "Schmeichel",   "30200053",  "2215560053",   1},
        {54,  "Lev",          "Yashin",       "30200054",  "2215560054",   0},
        {55,  "Johan",        "Cruyff",       "30200055",  "2215560055",   0},
        {56,  "Michel",       "Platini",      "30200056",  "2215560056",   1},
        {57,  "Marco",        "Van Basten",   "30200057",  "2215560057",   0},
        {58,  "Ruud",         "Gullit",       "30200058",  "2215560058",   0},
        {59,  "Franz",        "Beckenbauer",  "30200059",  "2215560059",   1},
        {60,  "Gerd",         "Muller",       "30200060",  "2215560060",   0},
    };

    for (int i = 0; i < 60; i++)
    {
        fwrite(&pacientes[i], sizeof(stPaciente), 1, archi);
    }

    printf("60 pacientes agregados correctamente.\n");
    fclose(archi);
}

void cargarPracticaTest()
{
    FILE *archi = abrirArchivo(ARCHIVO_PRACTICAS, "wb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }

    stPracticas practicas[15] = {
        { 1,  "Hemograma completo",   2500, 0},
        { 2,  "Glucemia",             1500, 0},
        { 3,  "Colesterol total",     2000, 0},
        { 4,  "Orina completa",       1800, 0},
        { 5,  "Radiografia torax",    4500, 0},
        { 6,  "Electrocardiograma",   5000, 0},
        { 7,  "Ecografia abdominal",  8000, 0},
        { 8,  "Coagulograma",         3000, 0},
        { 9,  "Hepatograma",          3500, 0},
        {10,  "Creatinina",           2200, 0},
        {11,  "Urea",                 1800, 0},
        {12,  "Trigliceridos",        2000, 0},
        {13,  "TSH tiroides",         4000, 0},
        {14,  "Vitamina D",           5500, 1},
        {15,  "Proteina C reactiva",  3200, 0},
    };

    for (int i = 0; i < 15; i++)
    {
        fwrite(&practicas[i], sizeof(stPracticas), 1, archi);
    }

    printf("15 practicas cargadas correctamente.\n");
    fclose(archi);
//    archi = abrirArchivo("TestPracticas.bin","rb");
//    stPracticas aux;
//    while (fread(&aux, sizeof(stPracticas), 1, archi) > 0)
//    {
//        printf("Nombre de la practica:%s\nID:%i\nCosto:%i\nEstado:%i\n",
//               aux.nombre,
//               aux.idPractica,
//               aux.costo,
//               aux.baja);
//        printf("---------------------------------------------------------------------\n");
//    }
//    fclose(archi);
}

void cargarLaboTest()
{
    FILE *archi = fopen(ARCHIVO_LABORATORIOS, "wb");
    if (archi == NULL)
    {
        printf("Error al abrir archivo.\n");
        return;
    }

    /* 60 pacientes x 4 laboratorios = 240 registros
       Formato: {idLab, idPaciente, anio, mes, dia, practicaRealizada, baja}
       Pacientes con baja logica: 3,4,9,15,19,23,26,30,33,36,40,43,47,50,53,56,59
       Algunos laboratorios de esos pacientes tambien tienen baja logica para consistencia */

    stLaboratorios labs[240] = {
        /* --- Messi (1) --- */
        {  1,  1, 2023,  3, 10,  1, 0},
        {  2,  1, 2023,  7, 22,  5, 0},
        {  3,  1, 2024,  1, 15,  9, 0},
        {  4,  1, 2024,  5,  8, 13, 0},
        /* --- Ronaldo (2) --- */
        {  5,  2, 2023,  2, 14,  2, 0},
        {  6,  2, 2023,  8,  3,  6, 0},
        {  7,  2, 2024,  3, 20, 10, 0},
        {  8,  2, 2024,  9, 11, 14, 0},
        /* --- Pele (3) baja --- */
        {  9,  3, 2022, 11,  5,  3, 1},
        { 10,  3, 2023,  4, 18,  7, 1},
        { 11,  3, 2023,  9, 27, 11, 1},
        { 12,  3, 2024,  2,  2, 15, 1},
        /* --- Maradona (4) baja --- */
        { 13,  4, 2022, 10, 12,  4, 1},
        { 14,  4, 2023,  3, 25,  8, 1},
        { 15,  4, 2023,  8,  7, 12, 1},
        { 16,  4, 2024,  1, 19,  2, 1},
        /* --- R.Nazario (5) --- */
        { 17,  5, 2023,  5, 30,  1, 0},
        { 18,  5, 2023, 10, 14,  5, 0},
        { 19,  5, 2024,  2, 22,  9, 0},
        { 20,  5, 2024,  7,  6, 13, 0},
        /* --- Zidane (6) --- */
        { 21,  6, 2023,  1, 18,  2, 0},
        { 22,  6, 2023,  6,  9,  6, 0},
        { 23,  6, 2024,  3, 27, 10, 0},
        { 24,  6, 2024,  8, 15, 14, 0},
        /* --- Ronaldinho (7) --- */
        { 25,  7, 2023,  4, 11,  3, 0},
        { 26,  7, 2023,  9, 28,  7, 0},
        { 27,  7, 2024,  1,  5, 11, 0},
        { 28,  7, 2024,  6, 23, 15, 0},
        /* --- Modric (8) --- */
        { 29,  8, 2023,  2, 20,  4, 0},
        { 30,  8, 2023,  7,  1,  8, 0},
        { 31,  8, 2024,  4, 16, 12, 0},
        { 32,  8, 2024,  9,  4,  2, 0},
        /* --- Iniesta (9) baja --- */
        { 33,  9, 2022, 12, 13,  5, 1},
        { 34,  9, 2023,  5, 26,  9, 1},
        { 35,  9, 2023, 10,  8, 13, 1},
        { 36,  9, 2024,  3, 21,  3, 1},
        /* --- Xavi (10) --- */
        { 37, 10, 2023,  3, 15,  6, 0},
        { 38, 10, 2023,  8, 29, 10, 0},
        { 39, 10, 2024,  2,  7, 14, 0},
        { 40, 10, 2024,  7, 20,  4, 0},
        /* --- Neymar (11) --- */
        { 41, 11, 2023,  1, 24,  1, 0},
        { 42, 11, 2023,  6, 13,  5, 0},
        { 43, 11, 2024,  3, 30,  9, 0},
        { 44, 11, 2024,  8, 17, 13, 0},
        /* --- Mbappe (12) --- */
        { 45, 12, 2023,  4,  7,  2, 0},
        { 46, 12, 2023,  9, 21,  6, 0},
        { 47, 12, 2024,  1, 14, 10, 0},
        { 48, 12, 2024,  6,  3, 14, 0},
        /* --- Haaland (13) --- */
        { 49, 13, 2023,  2, 28,  3, 0},
        { 50, 13, 2023,  7, 10,  7, 0},
        { 51, 13, 2024,  4, 25, 11, 0},
        { 52, 13, 2024,  9, 12, 15, 0},
        /* --- Vinicius (14) --- */
        { 53, 14, 2023,  5, 17,  4, 0},
        { 54, 14, 2023, 10,  4,  8, 0},
        { 55, 14, 2024,  2, 20, 12, 0},
        { 56, 14, 2024,  7,  9,  2, 0},
        /* --- De Bruyne (15) baja --- */
        { 57, 15, 2022, 11, 22,  5, 1},
        { 58, 15, 2023,  4,  6,  9, 1},
        { 59, 15, 2023,  9, 19, 13, 1},
        { 60, 15, 2024,  2, 28,  3, 1},
        /* --- Lewandowski (16) --- */
        { 61, 16, 2023,  3,  1,  6, 0},
        { 62, 16, 2023,  8, 14, 10, 0},
        { 63, 16, 2024,  1, 30, 14, 0},
        { 64, 16, 2024,  6, 18,  4, 0},
        /* --- Salah (17) --- */
        { 65, 17, 2023,  1, 11,  1, 0},
        { 66, 17, 2023,  5, 29,  5, 0},
        { 67, 17, 2024,  3,  7,  9, 0},
        { 68, 17, 2024,  8, 24, 13, 0},
        /* --- Benzema (18) --- */
        { 69, 18, 2023,  4, 20,  2, 0},
        { 70, 18, 2023,  9,  8,  6, 0},
        { 71, 18, 2024,  2, 26, 10, 0},
        { 72, 18, 2024,  7, 15, 14, 0},
        /* --- Mane (19) baja --- */
        { 73, 19, 2022, 10, 30,  3, 1},
        { 74, 19, 2023,  3, 13,  7, 1},
        { 75, 19, 2023,  8, 27, 11, 1},
        { 76, 19, 2024,  1, 10, 15, 1},
        /* --- Kane (20) --- */
        { 77, 20, 2023,  2,  5,  4, 0},
        { 78, 20, 2023,  7, 22,  8, 0},
        { 79, 20, 2024,  4,  9, 12, 0},
        { 80, 20, 2024,  9, 28,  2, 0},
        /* --- Griezmann (21) --- */
        { 81, 21, 2023,  1, 16,  5, 0},
        { 82, 21, 2023,  6,  4,  9, 0},
        { 83, 21, 2024,  3, 21, 13, 0},
        { 84, 21, 2024,  8, 10,  3, 0},
        /* --- Dybala (22) --- */
        { 85, 22, 2023,  4, 27,  6, 0},
        { 86, 22, 2023,  9, 15, 10, 0},
        { 87, 22, 2024,  1, 31, 14, 0},
        { 88, 22, 2024,  6, 19,  4, 0},
        /* --- Aguero (23) baja --- */
        { 89, 23, 2022, 12,  8,  1, 1},
        { 90, 23, 2023,  5, 21,  5, 1},
        { 91, 23, 2023, 10,  3,  9, 1},
        { 92, 23, 2024,  3, 17, 13, 1},
        /* --- Di Maria (24) --- */
        { 93, 24, 2023,  2, 14,  2, 0},
        { 94, 24, 2023,  7,  1,  6, 0},
        { 95, 24, 2024,  4, 18, 10, 0},
        { 96, 24, 2024,  9,  7, 14, 0},
        /* --- Batistuta (25) --- */
        { 97, 25, 2023,  3, 25,  3, 0},
        { 98, 25, 2023,  8, 12,  7, 0},
        { 99, 25, 2024,  2, 28, 11, 0},
        {100, 25, 2024,  7, 16, 15, 0},
        /* --- Crespo (26) baja --- */
        {101, 26, 2022, 11, 18,  4, 1},
        {102, 26, 2023,  4,  6,  8, 1},
        {103, 26, 2023,  9, 24, 12, 1},
        {104, 26, 2024,  2, 11,  2, 1},
        /* --- Riquelme (27) --- */
        {105, 27, 2023,  1, 30,  5, 0},
        {106, 27, 2023,  6, 17,  9, 0},
        {107, 27, 2024,  3,  5, 13, 0},
        {108, 27, 2024,  8, 22,  3, 0},
        /* --- Henry (28) --- */
        {109, 28, 2023,  4, 14,  6, 0},
        {110, 28, 2023,  9,  2, 10, 0},
        {111, 28, 2024,  1, 19, 14, 0},
        {112, 28, 2024,  6,  8,  4, 0},
        /* --- Drogba (29) --- */
        {113, 29, 2023,  2, 23,  1, 0},
        {114, 29, 2023,  7, 11,  5, 0},
        {115, 29, 2024,  4, 28,  9, 0},
        {116, 29, 2024,  9, 17, 13, 0},
        /* --- Eto (30) baja --- */
        {117, 30, 2022, 10, 26,  2, 1},
        {118, 30, 2023,  3,  9,  6, 1},
        {119, 30, 2023,  8, 22, 10, 1},
        {120, 30, 2024,  1, 13, 14, 1},
        /* --- Ibrahimovic (31) --- */
        {121, 31, 2023,  5,  4,  3, 0},
        {122, 31, 2023, 10, 20,  7, 0},
        {123, 31, 2024,  2,  7, 11, 0},
        {124, 31, 2024,  7, 25, 15, 0},
        /* --- Rooney (32) --- */
        {125, 32, 2023,  3, 16,  4, 0},
        {126, 32, 2023,  8,  3,  8, 0},
        {127, 32, 2024,  1, 21, 12, 0},
        {128, 32, 2024,  6, 10,  2, 0},
        /* --- Gerrard (33) baja --- */
        {129, 33, 2022, 12, 27,  5, 1},
        {130, 33, 2023,  5, 15,  9, 1},
        {131, 33, 2023, 10, 29, 13, 1},
        {132, 33, 2024,  3, 18,  3, 1},
        /* --- Lampard (34) --- */
        {133, 34, 2023,  4,  9,  6, 0},
        {134, 34, 2023,  9, 26, 10, 0},
        {135, 34, 2024,  2, 14, 14, 0},
        {136, 34, 2024,  7,  3,  4, 0},
        /* --- Vieira (35) --- */
        {137, 35, 2023,  1, 22,  1, 0},
        {138, 35, 2023,  6, 10,  5, 0},
        {139, 35, 2024,  3, 27,  9, 0},
        {140, 35, 2024,  8, 14, 13, 0},
        /* --- Scholes (36) baja --- */
        {141, 36, 2022, 11,  3,  2, 1},
        {142, 36, 2023,  4, 17,  6, 1},
        {143, 36, 2023,  9,  5, 10, 1},
        {144, 36, 2024,  2, 23, 14, 1},
        /* --- Giggs (37) --- */
        {145, 37, 2023,  5, 28,  3, 0},
        {146, 37, 2023, 10, 16,  7, 0},
        {147, 37, 2024,  1,  4, 11, 0},
        {148, 37, 2024,  6, 21, 15, 0},
        /* --- Beckham (38) --- */
        {149, 38, 2023,  3,  7,  4, 0},
        {150, 38, 2023,  8, 24,  8, 0},
        {151, 38, 2024,  4, 11, 12, 0},
        {152, 38, 2024,  9,  1,  2, 0},
        /* --- R.Carlos (39) --- */
        {153, 39, 2023,  2, 18,  5, 0},
        {154, 39, 2023,  7,  7,  9, 0},
        {155, 39, 2024,  3, 24, 13, 0},
        {156, 39, 2024,  8, 13,  3, 0},
        /* --- Cafu (40) baja --- */
        {157, 40, 2022, 10, 20,  6, 1},
        {158, 40, 2023,  3,  8, 10, 1},
        {159, 40, 2023,  8, 22, 14, 1},
        {160, 40, 2024,  1, 11,  4, 1},
        /* --- Maldini (41) --- */
        {161, 41, 2023,  4, 29,  1, 0},
        {162, 41, 2023,  9, 17,  5, 0},
        {163, 41, 2024,  2,  5,  9, 0},
        {164, 41, 2024,  7, 23, 13, 0},
        /* --- Baresi (42) --- */
        {165, 42, 2023,  1, 12,  2, 0},
        {166, 42, 2023,  6, 30,  6, 0},
        {167, 42, 2024,  3, 18, 10, 0},
        {168, 42, 2024,  8,  6, 14, 0},
        /* --- Cannavaro (43) baja --- */
        {169, 43, 2022, 12,  1,  3, 1},
        {170, 43, 2023,  5, 19,  7, 1},
        {171, 43, 2023, 10,  7, 11, 1},
        {172, 43, 2024,  3, 26, 15, 1},
        /* --- Puyol (44) --- */
        {173, 44, 2023,  4, 14,  4, 0},
        {174, 44, 2023,  9,  2,  8, 0},
        {175, 44, 2024,  1, 20, 12, 0},
        {176, 44, 2024,  6,  9,  2, 0},
        /* --- Pique (45) --- */
        {177, 45, 2023,  2, 25,  5, 0},
        {178, 45, 2023,  7, 13,  9, 0},
        {179, 45, 2024,  4, 30, 13, 0},
        {180, 45, 2024,  9, 18,  3, 0},
        /* --- Ramos (46) --- */
        {181, 46, 2023,  3,  6,  6, 0},
        {182, 46, 2023,  8, 21, 10, 0},
        {183, 46, 2024,  2,  9, 14, 0},
        {184, 46, 2024,  7, 27,  4, 0},
        /* --- Ferdinand (47) baja --- */
        {185, 47, 2022, 11, 14,  1, 1},
        {186, 47, 2023,  4, 28,  5, 1},
        {187, 47, 2023,  9, 11,  9, 1},
        {188, 47, 2024,  2, 29, 13, 1},
        /* --- Van Dijk (48) --- */
        {189, 48, 2023,  5, 17,  2, 0},
        {190, 48, 2023, 10,  5,  6, 0},
        {191, 48, 2024,  1, 22, 10, 0},
        {192, 48, 2024,  6, 11, 14, 0},
        /* --- Buffon (49) --- */
        {193, 49, 2023,  3, 28,  3, 0},
        {194, 49, 2023,  8, 16,  7, 0},
        {195, 49, 2024,  4,  4, 11, 0},
        {196, 49, 2024,  9, 22, 15, 0},
        /* --- Casillas (50) baja --- */
        {197, 50, 2022, 10,  9,  4, 1},
        {198, 50, 2023,  3, 23,  8, 1},
        {199, 50, 2023,  8,  6, 12, 1},
        {200, 50, 2024,  1, 25,  2, 1},
        /* --- Neuer (51) --- */
        {201, 51, 2023,  4, 12,  5, 0},
        {202, 51, 2023,  9, 29,  9, 0},
        {203, 51, 2024,  2, 16, 13, 0},
        {204, 51, 2024,  7,  5,  3, 0},
        /* --- Kahn (52) --- */
        {205, 52, 2023,  1, 20,  6, 0},
        {206, 52, 2023,  6,  8, 10, 0},
        {207, 52, 2024,  3, 26, 14, 0},
        {208, 52, 2024,  8, 14,  4, 0},
        /* --- Schmeichel (53) baja --- */
        {209, 53, 2022, 12, 30,  1, 1},
        {210, 53, 2023,  5, 18,  5, 1},
        {211, 53, 2023, 10,  1,  9, 1},
        {212, 53, 2024,  3, 20, 13, 1},
        /* --- Yashin (54) --- */
        {213, 54, 2023,  2,  7,  2, 0},
        {214, 54, 2023,  7, 25,  6, 0},
        {215, 54, 2024,  4, 13, 10, 0},
        {216, 54, 2024,  9,  2, 14, 0},
        /* --- Cruyff (55) --- */
        {217, 55, 2023,  3, 18,  3, 0},
        {218, 55, 2023,  8,  6,  7, 0},
        {219, 55, 2024,  1, 24, 11, 0},
        {220, 55, 2024,  6, 12, 15, 0},
        /* --- Platini (56) baja --- */
        {221, 56, 2022, 11, 22,  4, 1},
        {222, 56, 2023,  4, 10,  8, 1},
        {223, 56, 2023,  9, 28, 12, 1},
        {224, 56, 2024,  2, 17,  2, 1},
        /* --- Van Basten (57) --- */
        {225, 57, 2023,  5, 29,  5, 0},
        {226, 57, 2023, 10, 17,  9, 0},
        {227, 57, 2024,  1,  4, 13, 0},
        {228, 57, 2024,  6, 22,  3, 0},
        /* --- Gullit (58) --- */
        {229, 58, 2023,  3, 10,  6, 0},
        {230, 58, 2023,  8, 27, 10, 0},
        {231, 58, 2024,  4, 15, 14, 0},
        {232, 58, 2024,  9,  4,  4, 0},
        /* --- Beckenbauer (59) baja --- */
        {233, 59, 2022, 10, 15,  1, 1},
        {234, 59, 2023,  3, 29,  5, 1},
        {235, 59, 2023,  8, 12,  9, 1},
        {236, 59, 2024,  1, 31, 13, 1},
        /* --- Gerd Muller (60) --- */
        {237, 60, 2023,  4, 20,  2, 0},
        {238, 60, 2023,  9,  8,  6, 0},
        {239, 60, 2024,  2, 26, 10, 0},
        {240, 60, 2024,  7, 14, 14, 0},
    };

    for (int i = 0; i < 240; i++)
    {
        fwrite(&labs[i], sizeof(stLaboratorios), 1, archi);
    }

    printf("240 laboratorios cargados correctamente.\n");
    fclose(archi);

//    stLaboratorios aux;
//    archi = fopen("TestLaboratorios.bin", "rb");
//    int i = 0;
//    while (fread(&aux, sizeof(stLaboratorios), 1, archi) > 0)
//    {
//        printf("ID Paciente:%i\nPractica realizada:%i\nID Lab:%i\nFecha: %i - %i - %i\n pos %i",
//               aux.idPaciente,
//               aux.practicaRealizada,
//               aux.idLab,
//               aux.dia,
//               aux.mes,
//               aux.anio,
//               i);
//        printf("\n-----------------------------------------------------------------\n");
//        i++;
//    }
//    fclose(archi);
}




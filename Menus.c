#include "Pacientes.h"
#include "Practicas.h"
#include <stdio.h>


void mainMenu();
void pacientesMenu();
void laboratoriosMenu();
void practicasMenu();

/// Variables
int validosArregloPracticas=0;
int validosPacientes = 0;
stPracticas *arregloDinamicoPracticas=NULL;
stLaboratorios *arregloDinamico = NULL;
stLaboratorios *arregloOrdenamiento = NULL;
int validosOrdenamiento = 0;
int validosADP;
stPaciente *ADP = NULL; /// arreglo dinamico pacientes para funcion mostrar
stPracticas practicas[20];
void mainMenu()
{
    int optionswitch = 0;
    do
{
    system("cls");
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n1-Pacientes");
    printf("\n2-Laboratorios");
    printf("\n3-Practicas");
    printf("\n0-Salir");
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    scanf("%i",&optionswitch);
    switch(optionswitch)
    {
    case 1: pacientesMenu();
        break;
    case 2:
        laboratoriosMenu();
        break;
    case 3:
        practicasMenu();
        break;
    case 7:
        resetearArchivos();
        system("pause");
        break;
    case 10:
        cargarPacientesAB();
        cargarPracticaTest();
        cargarLaboTest();
        system("pause");
        break;
    case 0:
        break;
    default :
        printf("Tecla incorrecta.\n");
        break;
    }

}while (optionswitch != 0);
}

void pacientesMenu() /// USAR ESTE MENU PARA PROBAR EJERCICIOS DE PACIENTE
{
    int optionswitch = 0;
    system("cls");
    do
    {
//        system("cls");
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------");
        printf("\n1-Cargar paciente");
        printf("\n2-Mostrar Pacientes.");
        printf("\n3-Modificar Pacientes.");
        printf("\n4-Dar de baja un paciente");
        printf("\n5-Buscar paciente.");
        printf("\n6-Mostrar pacientes de baja. -- Dar de alta paciente eliminado");
        printf("\n\n7-Lista de pacientes por apellido y nombre");
        printf("\n0-Volver al menu anterior.");
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        scanf("%i",&optionswitch);
        switch(optionswitch)
        {
        case 1:
            cargarPacientes();
            break;
        case 2:
            getIDVPacientes();
            getIDVPracticas();
            validosPacientes = mostrarArchivo();
            printf("Validos vale:%i\n",validosPacientes);
            break;
        case 3:
            buscarPaciente(pacientes,validosPacientes);
            break;
        case 4:
            bajaPaciente();
            break;
        case 5:
            busquedaPaciente();
            break;
        case 6:
            mostrarEliminados();
            break;
        case 7:
            ADP = activosADinamicos(&validosADP);
            ordenamientoSeleccionChar(ADP,validosADP);
            break;
        case 10:
            arregloOrdenamiento = arregloDinamicoLaboratoriosPorFecha (&validosOrdenamiento);
            printf("Validos vale:%i\n",validosOrdenamiento);
            ordenamientoSeleccionFecha(arregloOrdenamiento,validosOrdenamiento);
            mostrarLaboratoriosOrdenadosPorfecha(arregloOrdenamiento,validosOrdenamiento);
            break;
        case 99:
            cargarPacientesAB();
            cargarPracticaTest();
            cargarLaboTest();
            break;
        case 0:
            printf("Vuelva pronto.\n");
            break;
        default :
            printf("Numero incorrecto\n0 para salir.");
            break;
        }
    } while (optionswitch != 0) ;
}

void laboratoriosMenu() /// USAR ESTE MENU PARA PROBAR EJERCICIOS DE LABORATORIO
{
    int optionswitch = 0;
    do
    {
        system("cls");
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("1-Cargar laboratorio.\n");
        printf("2-Dar de baja un laboratorio.\n");
        printf("3-Modificar laboratorio.\n");
        printf("4-Consultar laboratorio.\n");
        printf("5-Listar Laboratorio.\n");
        printf("6-Menu mostrar laboratorios por paciente.\n");
        printf("7-Laboratorios ordenados por fecha.\n");
        printf("0-Volver al menu anterior.\n");
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        scanf("%i",&optionswitch);
        switch(optionswitch)
        {
        case 1:
            cargarLaboratorios();
            break;
        case 2:
            bajaLaboratorio();
            break;
        case 3:
            modificarLaboratorio();
            break;
        case 4:
            consultarLaboratorio();
            break;
        case 5:
            mostrarLaboratoriosArchivo();
            break;
        case 6:
            menuMostrarLaboratoriosPorPaciente();
            break;
        case 7:
            arregloOrdenamiento = arregloDinamicoLaboratoriosPorFecha (&validosOrdenamiento);
            printf("Validos vale:%i\n",validosOrdenamiento);
            ordenamientoSeleccionFecha(arregloOrdenamiento,validosOrdenamiento);
            mostrarLaboratoriosOrdenadosPorfecha(arregloOrdenamiento,validosOrdenamiento);
            break;
        case 99: /// ABRE ARCHIVO PACIENTES-SANTI.
            muestraTSP();
            break;
        case 0:
            printf("Vuelva pronto.\n");
            break;
        default :
            printf("Numero incorrecto\n0 para salir.\n");
            break;
        }
    } while (optionswitch != 0) ;
}

void practicasMenu() /// USAR ESTE MENU PARA PROBAR EJERCICIOS DE PRACTICA
{
    system("cls");
    int optionswitch = 0;
    do
    {
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("1-Cargar practica\n");
        printf("2-Modificar practica\n");
        printf("3-Dar de baja una practica\n");
        printf("4-Dar de alta una practica\n");
        printf("5-Mostrar listado de practicas\n");
        printf("6-Buscar practica por nombre\n");
        printf("0-Volver al menu anterior");
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        scanf("%i",&optionswitch);
        switch(optionswitch)
        {
        case 1:
                cargarPracticas(ARCHIVO_PRACTICAS);
            break;
        case 2:
            system("cls");
                modificarPracticas(ARCHIVO_PRACTICAS);
            break;
        case 3:
                darDeBajaPracticas(ARCHIVO_PRACTICAS);
            break;
        case 4:
                darDeAltaPracticas(ARCHIVO_PRACTICAS);
            break;
        case 5:
                validosArregloPracticas=0;
                arregloDinamicoPracticas=cargarArregloDinamicoPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
                mostrarPracticas(arregloDinamicoPracticas,&validosArregloPracticas);
            break;
        case 6:
                buscarPracticasPorNombre();
            break;
        case 0:
            printf("Vuelva pronto.\n");
            break;
        default :
            printf("Numero incorrecto\n0 para salir.");
            break;
        }
    } while (optionswitch != 0) ;
}


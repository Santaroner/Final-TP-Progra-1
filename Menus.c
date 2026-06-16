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
int validosADP;
stPaciente *ADP = NULL; /// arreglo dinamico pacientes para funcion mostrar
stPaciente *TSP = NULL; /// Arreglo dinamico top spenders
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
        printf("\n7-Menu mostrar laboratorios por paciente.\n");
        printf("Buscar pacientes con mayor gasto economico:\n");
        printf("\n\n9-Arreglo dinamico --- Ordenamiento de apellidos");
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
            menuMostrarLaboratoriosPorPaciente();
            break;
        case 8:
            printf("Buscar pacientes con mayor gasto economico:\n");
            break;
        case 9:
            ADP = activosADinamicos(&validosADP);
            ordenamientoSeleccionChar(ADP,validosADP);
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
void deletearchi()
{
    FILE *archi = fopen("TestPacientes.bin", "wb");
    fclose(archi);
}
void laboratoriosMenu() /// USAR ESTE MENU PARA PROBAR EJERCICIOS DE LABORATORIO
{
    int optionswitch = 0;
    do
    {
        system("cls");
        printf("1-Cargar laboratorio \n2-Baja Laboratorio\n3-Modificar Laboratorio\n4-Consultar Laboratorio\n5-Listar Laboratorios\n88-Archivo precargado Practicas\n99-Archivo precargado pacientes\n0-Salir");
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
            mostrarPracticasSanti();
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
    int optionswitch = 0;
    do
    {
        ///system("cls");
        printf("1-Cargar practica\n2-Modificar practica\n3-Dar de baja una practica\n4-Dar de alta una practica\n5-Mostrar listado de practicas \n6-Buscar practica por nombre\n0-Salir\n");
        scanf("%i",&optionswitch);
        switch(optionswitch)
        {
        case 1:
            if(arregloDinamicoPracticas==NULL)
            {
                arregloDinamicoPracticas=cargarArregloDinamicoPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
                cargarPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
            }
            else
            {
                cargarPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
            }
///            validos=cargarPracticas("PracticasSanti.bin");
            break;
        case 2:
            if(arregloDinamicoPracticas==NULL)
            {
                arregloDinamicoPracticas=cargarArregloDinamicoPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
                modificarPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
            }
            else
            {
                modificarPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
            }
            break;
        case 3:
            if(arregloDinamicoPracticas==NULL)
            {
                arregloDinamicoPracticas=cargarArregloDinamicoPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
                darDeBajaPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas);
            }
            else
            {
                darDeBajaPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas);
            }
            break;
        case 4:
            if(arregloDinamicoPracticas==NULL)
            {
                arregloDinamicoPracticas=cargarArregloDinamicoPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
                darDeAltaPracticas(ARCHIVO_PRACTICAS, arregloDinamicoPracticas);
            }
            else
            {
                darDeAltaPracticas(ARCHIVO_PRACTICAS, arregloDinamicoPracticas);
            }
            break;
        case 5:
            if(arregloDinamicoPracticas==NULL)
            {
                arregloDinamicoPracticas=cargarArregloDinamicoPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
                mostrarPracticas(arregloDinamicoPracticas,&validosArregloPracticas);
                system("pause");
            }
            else
            {
                mostrarPracticas(arregloDinamicoPracticas,&validosArregloPracticas);
            }
            break;
        case 6:
            if(arregloDinamicoPracticas==NULL)
            {
                arregloDinamicoPracticas=cargarArregloDinamicoPracticas(ARCHIVO_PRACTICAS,arregloDinamicoPracticas,&validosArregloPracticas);
                buscarPracticasPorNombre(arregloDinamicoPracticas, validosArregloPracticas);
            }
            else
            {
                buscarPracticasPorNombre(arregloDinamicoPracticas, validosArregloPracticas);
            }
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


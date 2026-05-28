#include "Pacientes.h"
#include "Practicas.h"
#include <stdio.h>

void mainMenu();
void pacientesMenu();
void laboratoriosMenu();
void practicasMenu();

/// Variables
int validosPacientes = 0;

stPracticas practicas[20];
void mainMenu()
{
    int optionswitch = 0;
    do
{
    printf("1-Ingrese menu Pacientes\n2-Ingrese menu Laboratorios\n3-Ingrese menu Practicas\n\n0-Salir\n");
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
    do
    {
        printf("1-Cargar paciente.\n2-Mostrar pacientes\n3-Modificar Paciente 3\n0-Salir\n");
        scanf("%i",&optionswitch);
        switch(optionswitch)
        {
        case 1:
            cargarPacientes();
            break;
        case 2:
            validosPacientes = mostrarArchivo();
            printf("Validos vale:%i\n",validosPacientes);
            break;
        case 3:
            buscarPaciente(pacientes,validosPacientes);
            break;
        case 9:
            mostrarArchivo();
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
        printf("1-Ejercicio 1\n2-Ejercicio 2\n3-Ejercicio 3\n0-Salir");
        scanf("%i",&optionswitch);
        switch(optionswitch)
        {
        case 1:
            printf("Ejercicio 1\n");
            break;
        case 2:
            printf("Ejercicio 2\n");
            break;
        case 3:
            printf("Ejercicio 3\n");
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
        printf("1-Cargar practica\n2-Modificar practica\n3-Mostrar listado de practicas \n0-Salir\n");
        scanf("%i",&optionswitch);
        switch(optionswitch)
        {
        case 1:
            printf("La cantidad maxima de practicas para cargar son 20\n");
            validos=cargarPracticas(practicas);
            break;
        case 2:
            modificarPacientes(practicas, validos);
            break;
        case 3:
            mostrarPracticas(practicas, validos);
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


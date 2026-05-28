#include "Practicas.h"


int cargarPracticas(stPracticas practicas[20])
{
    int validos=0;
    char seguir='s';
    while(seguir=='s' && validos<20)
    {
        int flag;
        static int idPractica=1;
        practicas[validos].idPractica=idPractica;
        do
        {
        printf("Ingrese el nombre de la practica: ");
        scanf("%s", practicas[validos].nombre);
        flag=buscarNombrePractica(practicas, validos);
        if(flag==0)
        {
            printf("La practica ya esta ingresada, ingrese una nuevamente\n");
        }
        }while(flag==0);
        printf("Ingrese el costo de la practica (1000$ a 10000$): ");
        scanf("%i", &practicas[validos].costo);
        printf("Esta de baja la practica(1) o esta activa(0)? ");
        scanf("%i", &practicas[validos].baja);
        idPractica++;
        printf("Desea seguir ingresando practicas? (s para seguir)");
        scanf(" %c", &seguir);
        validos++;
    }
    return validos;
}
int buscarNombrePractica(stPracticas practicas[20], int validos)
{
    int flag=1;
    for(int i=0;i<validos && flag!=0;i++)
    {
        int res=strcmpi(practicas[i].nombre, practicas[i+1].nombre);
        if(res==0)
        {
            flag=0;
        }
    }
    return flag;
}
void modificarPacientes(stPracticas practicas[20], int validos)
{
    int indice=0;
    printf("Cual practica desea modificar? 0 a %i", validos-1);
    scanf("%i", &indice);
    printf("La practica %i esta cargada con los siguientes datos: \n", indice);
    printf("idPractica: %i\n", practicas[indice].idPractica);
    printf("Nombre: %s\n", practicas[indice].nombre);
    printf("Costo: %i\n", practicas[indice].costo);
    printf("Baja: %i\n", practicas[indice].baja);
    int opcionSwitch=0;
    do
    {
    printf("Que desea modificar? 1-nombre, 2-costo, 3-baja, 0-salir\n");
    scanf("%i", &opcionSwitch);
    switch(opcionSwitch)
    {
    case 1:
        {
            printf("Ingrese el nuevo nombre de la practica %i: ", practicas[indice].idPractica);
            scanf("%s", practicas[indice].nombre);
        }
        break;
    case 2:
        {
            printf("Ingrese el nuevo costo de la practica %i: ", practicas[indice].idPractica);
            scanf("%i", &practicas[indice].costo);
        }
        break;
    case 3:
        {
            printf("Ingrese el nuevo estado de la practica %i (0 si esta activa, 1 si esta de baja): ", practicas[indice].idPractica);
            scanf("%i", &practicas[indice].baja);
        }
        break;
    case 0:
        printf("Vuelva pronto\n");
        break;
    default:
        printf("Numero incorrecto\n0 para salir.");
        break;
    }
    }while(opcionSwitch!=0);
}
void mostrarPracticas(stPracticas practicas[20], int validos)
{
    for(int i=0;i<validos;i++)
    {
        printf("Los datos de la practica %i son:\n", i);
        printf("idPractica: %i\n", practicas[i].idPractica);
        printf("Nombre: %s\n", practicas[i].nombre);
        printf("Costo: %i\n", practicas[i].costo);
        printf("Baja (0 activo, 1 baja): %i\n", practicas[i].baja);
    }
}

#include "Practicas.h"

int generaId()
{
    int static id = 0;
    id++;
    return id;
}

stPracticas cargarUnaPractica()
{
    stPracticas unaPractica;
        unaPractica.idPractica=generaId();
        printf("Ingrese el nombre de la practica: ");
        scanf("%s", unaPractica.nombre);
        printf("Ingrese el costo de la practica (1000$ a 10000$): ");
        scanf("%i", &unaPractica.costo);
        printf("Esta de baja la practica(1) o esta activa(0)? ");
        scanf("%i", &unaPractica.baja);

        return unaPractica;

}

int cargarPracticas(char ArchivoPracticas[30])
{
    FILE *archi_Practicas=fopen(ArchivoPracticas, "wb");

    int validos=0;
    char seguir='s';
    stPracticas nuevaPractica;

    while(seguir=='s')
    {
        nuevaPractica = cargarUnaPractica();
        fwrite(&nuevaPractica, sizeof(stPracticas), 1, archi_Practicas);
        printf("Desea seguir ingresando practicas? (s para seguir)");
        scanf(" %c", &seguir);
        validos++;
    }
    fclose(archi_Practicas);
    return validos;
}
/**int buscarNombrePractica(stPracticas practicas, int validos)
{
    int flag=1;
    for(int i=0; i<validos && flag!=0; i++)
    {
        int res=strcmpi(practicas[i].nombre, practicas[i+1].nombre);
        if(res==0)
        {
            flag=0;
        }
    }
    return flag;
}*/
void modificarPracticas(stPracticas practicas[20], int validos)
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
    }
    while(opcionSwitch!=0);
}
void mostrarPracticas(stPracticas practicas)
{
    FILE *archi_Practicas=fopen("Practicas.bin", "rb");
    stPracticas practicasAux;
    printf("Error");

/**    while(!feof(archi_Practicas))
    {
        if(!feof(archi_Practicas))
        {
        fread(&practicasAux, sizeof(stPracticas), 1, archi_Practicas);
        mostrarUnaPractica(practicasAux);
        }
    }
    */

    while((fread(&practicasAux, sizeof(stPracticas), 1, archi_Practicas)) > 0)
    {
        mostrarUnaPractica(practicasAux);
        system("pause");
        system("cls");
    }

    fclose(archi_Practicas);
}
void mostrarUnaPractica(stPracticas practicasAux)
{
    printf("idPractica: %i\n", practicasAux.idPractica);
    printf("Nombre: %s\n", practicasAux.nombre);
    printf("Costo: %i\n", practicasAux.costo);
    printf("Baja (0 activo, 1 baja): %i\n", practicasAux.baja);
}

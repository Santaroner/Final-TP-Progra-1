#include "Practicas.h"

int generaId() ///
{
    int id = getIDVPracticas(); /// Funcion de utilities, recorre la cantidad de practicas que hay
    id++;
    ///printf("ID VALE :%i",id);
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

void cargarPracticas(char ArchivoPracticas[30])
{
    int validos=0;
    char seguir='s';
    stPracticas nuevaPractica;

    while(seguir=='s')
    {
        ///FILE *archi_Practicas=fopen(ArchivoPracticas, "ab"); /// si se declara el archivo arriba y se cierra despues del while no se llega a actualizar el buffer del ID al poner nueva practica
        FILE *archi_Practicas=fopen(ArchivoPracticas, "ab");
        nuevaPractica = cargarUnaPractica();
        fwrite(&nuevaPractica, sizeof(stPracticas), 1, archi_Practicas);
        printf("Desea seguir ingresando practicas? (s para seguir)");
        scanf(" %c", &seguir);
        validos++;
        fclose(archi_Practicas);
    }
}
int contarPracticas(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ARCHIVO_PRACTICAS,"rb");
    fseek(archivoPracticas,0,2);
    int cantidadDePracticas=ftell(archivoPracticas)/sizeof(stPracticas);
    fclose(archivoPracticas);
    return cantidadDePracticas;
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
void modificarPracticas(char ArchivoPracticas[30])
{
      FILE *archivoPracticas=fopen(ARCHIVO_PRACTICAS,"r+b");
      mostrarPracticas(ARCHIVO_PRACTICAS);
      int cantidadDePracticas=contarPracticas(ARCHIVO_PRACTICAS);
      if(cantidadDePracticas==0)
      {
          printf("No hay practicas cargadas para modificar");
      }
      else
      {
          int nroPractica=0;
          printf("Ingrese una practica para modificar (1 a %i)", cantidadDePracticas);
          scanf("%i", &nroPractica);
          int posicion=nroPractica-1;
          fseek(archivoPracticas,posicion*sizeof(stPracticas),0);
          stPracticas unaPractica;
          fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
          mostrarUnaPractica(unaPractica);
          unaPractica=menuModificarPractica(unaPractica);
          fseek(archivoPracticas,-sizeof(stPracticas),SEEK_CUR);
          fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
      }
      fclose(archivoPracticas);
//    int indice=0;
//    printf("Cual practica desea modificar? 0 a %i", validos-1);
//    scanf("%i", &indice);
//    printf("La practica %i esta cargada con los siguientes datos: \n", indice);
//    printf("idPractica: %i\n", practicas[indice].idPractica);
//    printf("Nombre: %s\n", practicas[indice].nombre);
//    printf("Costo: %i\n", practicas[indice].costo);
//    printf("Baja: %i\n", practicas[indice].baja);
//    int opcionSwitch=0;
//    do
//    {
//        printf("Que desea modificar? 1-nombre, 2-costo, 3-baja, 0-salir\n");
//        scanf("%i", &opcionSwitch);
//        switch(opcionSwitch)
//        {
//        case 1:
//        {
//            printf("Ingrese el nuevo nombre de la practica %i: ", practicas[indice].idPractica);
//            scanf("%s", practicas[indice].nombre);
//        }
//        break;
//        case 2:
//        {
//            printf("Ingrese el nuevo costo de la practica %i: ", practicas[indice].idPractica);
//            scanf("%i", &practicas[indice].costo);
//        }
//        break;
//        case 3:
//        {
//            printf("Ingrese el nuevo estado de la practica %i (0 si esta activa, 1 si esta de baja): ", practicas[indice].idPractica);
//            scanf("%i", &practicas[indice].baja);
//        }
//        break;
//        case 0:
//            printf("Vuelva pronto\n");
//            break;
//        default:
//            printf("Numero incorrecto\n0 para salir.");
//            break;
//        }
//    }
//    while(opcionSwitch!=0);
}
stPracticas menuModificarPractica(stPracticas unaPractica)
{
    int opcion=0;
    do
    {
    printf("Elija un dato para modificar (1-Nombre\n2-Costo\n3-Baja\n0-Salir)");
    scanf("%i",&opcion);
    switch(opcion)
    {
        case 1:
            printf("Ingrese un nuevo nombre: ");
            scanf("%s", unaPractica.nombre);
            break;
        case 2:
            printf("Ingrese un nuevo costo: ");
            scanf("%i", &unaPractica.costo);
            break;
        case 3:
            printf("Ingrese nueva baja(0 activo, 1 baja): ");
            scanf("%i", &unaPractica.baja);
            break;
        case 0:
            printf("Vuelva pronto.\n");
            break;
        default:
            printf("Ingrese una opcion correcta(0 a 3)");
            break;
    }
    }while(opcion!=0);
    return unaPractica;
}
void mostrarPracticas(char ArchivoPracticas[30])
{
    FILE *archi_Practicas=fopen(ArchivoPracticas, "rb");
    stPracticas practicasAux;
    while((fread(&practicasAux, sizeof(stPracticas), 1, archi_Practicas)) > 0)
    {
        mostrarUnaPractica(practicasAux);
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



/// -------------------------------------- T E S T /// R A  F A /// ------------------------------------------ ///


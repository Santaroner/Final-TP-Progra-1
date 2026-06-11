#include "Practicas.h"

int generaId() ///
{
    int id = getIDVPracticas(); /// Funcion de utilities, recorre la cantidad de practicas que hay
    id++;
    ///printf("ID VALE :%i",id);
    return id;
}
void ingreseNombre(char nombre[30])
{
    int flag=0;
    do
    {
        printf("Ingrese el nombre de la practica: ");
        getchar();
        fgets(nombre,30,stdin);
        nombre [strcspn(nombre,"\n")] = '\0';
        flag=buscarNombreIgualPractica(nombre,ARCHIVO_PRACTICAS);
        if(flag==1)
        {
            printf("La practica que quiere cargar ya esta ingresada, ingrese otra.\n");
        }
    }
    while(flag==1);
}
int ingreseCosto(int costo)
{
    do
    {
        printf("Ingrese el costo de la practica (1000$ a 10000$): ");
        scanf("%i", &costo);
        if(costo<1000 || costo>10000)
        {
            printf("Error, el costo debe estar entre $1000 y $10000.\n");
        }
    }
    while(costo<1000 || costo>10000);
    return costo;
}
int ingreseBaja(int baja)
{
    printf("Esta de baja la practica(1) o esta activa(0)? ");
    scanf("%i", &baja);
    return baja;
}
stPracticas cargarUnaPractica()
{
        stPracticas unaPractica;
        unaPractica.idPractica=generaId();
        ingreseNombre(unaPractica.nombre);
        unaPractica.costo=ingreseCosto(unaPractica.costo);
        unaPractica.baja=ingreseBaja(unaPractica.baja);
        return unaPractica;
}


void cargarPracticas(char ArchivoPracticas[30], stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas)
{
    char seguir='s';
    stPracticas nuevaPractica;
    int i=*validosArregloPracticas;
    while(seguir=='s')
    {
        ///FILE *archi_Practicas=fopen(ArchivoPracticas, "ab"); /// si se declara el archivo arriba y se cierra despues del while no se llega a actualizar el buffer del ID al poner nueva practica
        ///FILE *archi_Practicas=fopen(ArchivoPracticas, "ab");
        nuevaPractica = cargarUnaPractica();
        arregloDinamicoPracticas=(stPracticas *)realloc(arregloDinamicoPracticas, (i+1)*sizeof(stPracticas));
        arregloDinamicoPracticas[i]=nuevaPractica;
        cargarPracticaEnArchivo(ARCHIVO_PRACTICAS,arregloDinamicoPracticas[i],validosArregloPracticas);
        i++;
        ///fwrite(&nuevaPractica, sizeof(stPracticas), 1, archi_Practicas);
        printf("Desea seguir ingresando practicas? (s para seguir)");
        scanf(" %c", &seguir);
        ///fclose(archi_Practicas);
    }
}
void cargarPracticaEnArchivo(char ArchivoPracticas[30], stPracticas unaPractica, int *validosArregloPracticas)
{
    FILE *archi_Practicas=fopen(ArchivoPracticas, "ab");
    fwrite(&unaPractica,sizeof(stPracticas),1,archi_Practicas);
    (*validosArregloPracticas)++;
    fclose(archi_Practicas);
}
stPracticas *cargarArregloDinamicoPracticas(char ArchivoPracticas[30], stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas)
{
    int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS);
    arregloDinamicoPracticas=(stPracticas *)realloc(arregloDinamicoPracticas, cantPracticas*sizeof(stPracticas));
    traspasoDatos(arregloDinamicoPracticas,ARCHIVO_PRACTICAS,validosArregloPracticas);
    return arregloDinamicoPracticas;
}
void traspasoDatos(stPracticas *arregloDinamicoPracticas, char ArchivoPracticas[30], int *validosArregloPracticas)
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    stPracticas unaPractica;
    if(archivoPracticas==NULL)
    {
        *validosArregloPracticas=0;
    }
    int i=0;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        arregloDinamicoPracticas[i]=unaPractica;
        i++;
        (*validosArregloPracticas)++;
    }
    fclose(archivoPracticas);
}
void muestraArreglo(stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas)
{
    int a=*validosArregloPracticas;
    for(int i=0;i<a;i++)
    {
        printf("idPractica: %i\n", arregloDinamicoPracticas[i].idPractica);
        printf("idPractica: %s\n", arregloDinamicoPracticas[i].nombre);
        printf("idPractica: %i\n", arregloDinamicoPracticas[i].costo);
        printf("idPractica: %i\n", arregloDinamicoPracticas[i].baja);
        system("pause");
    }
}
int buscarNombreIgualPractica(char nombrePractica[30], char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    int flag=0;
    if(archivoPracticas==NULL)
    {
        flag=0;
    }
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        int res=strcmpi(unaPractica.nombre,nombrePractica);
        if(res==0)
        {
            flag=1;
        }
    }
    fclose(archivoPracticas);
    return flag;
}
int contarPracticas(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ARCHIVO_PRACTICAS,"rb");
    fseek(archivoPracticas,0,2);
    int cantidadDePracticas=ftell(archivoPracticas)/sizeof(stPracticas);
    fclose(archivoPracticas);
    return cantidadDePracticas;
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
void mostrarPracticasAlta(char archivoPracticas[30])
{
    FILE *archi_Practicas=fopen(archivoPracticas, "rb");
    stPracticas practicasAux;
    while((fread(&practicasAux, sizeof(stPracticas), 1, archi_Practicas)) > 0)
    {
        mostrarUnaPracticaAlta(practicasAux);
    }
    fclose(archi_Practicas);
}
void mostrarPracticasBaja(char archivoPracticas[30])
{
    FILE *archi_Practicas=fopen(archivoPracticas, "rb");
    stPracticas practicasAux;
    while((fread(&practicasAux, sizeof(stPracticas), 1, archi_Practicas)) > 0)
    {
        mostrarUnaPracticaBaja(practicasAux);
    }
    fclose(archi_Practicas);
}
void mostrarUnaPracticaAlta(stPracticas practicasAux)
{
    if(practicasAux.baja==0)
    {
    printf("idPractica: %i\n", practicasAux.idPractica);
    printf("Nombre: %s\n", practicasAux.nombre);
    printf("Costo: %i\n", practicasAux.costo);
    printf("Baja (0 activo, 1 baja): %i\n", practicasAux.baja);
    }
}
void mostrarUnaPracticaBaja(stPracticas practicasAux)
{
    if(practicasAux.baja==1)
    {
    printf("idPractica: %i\n", practicasAux.idPractica);
    printf("Nombre: %s\n", practicasAux.nombre);
    printf("Costo: %i\n", practicasAux.costo);
    printf("Baja (0 activo, 1 baja): %i\n", practicasAux.baja);
    }
}
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
}
stPracticas menuModificarPractica(stPracticas unaPractica)
{
    int opcion=0;
    do
    {
    printf("Elija un dato para modificar:\n1-Nombre\n2-Costo\n0-Salir");
    scanf("%i",&opcion);
    switch(opcion)
    {
        case 1:
            printf("Ingrese un nuevo nombre: ");
            getchar();
            fgets(unaPractica.nombre,30,stdin);
            unaPractica.nombre [strcspn(unaPractica.nombre,"\n")] = '\0';
            break;
        case 2:
            printf("Ingrese un nuevo costo: ");
            scanf("%i", &unaPractica.costo);
            break;
        case 0:
            printf("Vuelva pronto.\n");
            break;
        default:
            printf("Ingrese una opcion correcta(0 a 2)");
            break;
    }
    }while(opcion!=0);
    return unaPractica;
}
void darDeBajaPracticas(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ARCHIVO_PRACTICAS,"r+b");
    mostrarPracticasAlta(ARCHIVO_PRACTICAS);
    int cantidadDePracticas=contarPracticas(ARCHIVO_PRACTICAS);
      if(cantidadDePracticas==0)
      {
          printf("No hay practicas cargadas para dar de baja");
      }
      else
      {
    int nroPractica=0;
          printf("Ingrese una practica para dar de baja (idPractica).");
          scanf("%i", &nroPractica);
          int posicion=nroPractica-1;
          fseek(archivoPracticas,posicion*sizeof(stPracticas),0);
          stPracticas unaPractica;
          fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
          unaPractica=darDeBajaUnaPractica(unaPractica);
          fseek(archivoPracticas,-sizeof(stPracticas),SEEK_CUR);
          fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
          mostrarUnaPractica(unaPractica);
          printf("La practica seleccionada ha sido dada de baja!\n");
      }
    fclose(archivoPracticas);
}
stPracticas darDeBajaUnaPractica(stPracticas unaPractica)
{
    unaPractica.baja=1;
    return unaPractica;
}
void darDeAltaPracticas(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ARCHIVO_PRACTICAS,"r+b");
    mostrarPracticasBaja(ARCHIVO_PRACTICAS);
    int cantidadDePracticas=contarPracticas(ARCHIVO_PRACTICAS);
      if(cantidadDePracticas==0)
      {
          printf("No hay practicas cargadas para dar de alta");
      }
      else
      {
    int nroPractica=0;
          printf("Ingrese una practica para dar de alta (idPractica).");
          scanf("%i", &nroPractica);
          int posicion=nroPractica-1;
          fseek(archivoPracticas,posicion*sizeof(stPracticas),0);
          stPracticas unaPractica;
          fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
          unaPractica=darDeAltaUnaPractica(unaPractica);
          fseek(archivoPracticas,-sizeof(stPracticas),SEEK_CUR);
          fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
          mostrarUnaPractica(unaPractica);
          printf("La practica seleccionada ha sido dada de alta!\n");
      }
    fclose(archivoPracticas);
}
stPracticas darDeAltaUnaPractica(stPracticas unaPractica)
{
    unaPractica.baja=0;
    return unaPractica;
}


/// -------------------------------------- T E S T /// R A  F A /// ------------------------------------------ ///


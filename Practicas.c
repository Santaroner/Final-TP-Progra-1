#include "Practicas.h"

/// ---------------------- C A R G A  D E  P R A C T I C A S ---------------------- ///
int generaId() ///
{
    int id = getIDVPracticas(); /// Funcion de utilities, recorre la cantidad de practicas que hay
    id++;
    ///printf("ID VALE :%i",id);
    return id;
}
void ingreseNombre(char nombre[30])
{
    int flag=0, flag2=1, flag3=0;
    do
    {
        printf("Ingrese el nombre de la practica: ");
        getchar();
        void limpiarBuffer();
        fgets(nombre,30,stdin);
        if (strchr(nombre,'\n') != NULL)
        {
        nombre=primerLetraMayuscula(nombre);
        borrarSaltoDeLinea(nombre);
        flag2=ingresarSoloLetras(nombre);
        if(flag2==0)
        {
            printf("Error, ingrese solo letras.\n");
        }
        flag=buscarNombreIgualPractica(nombre,ARCHIVO_PRACTICAS);
        if(flag==1)
        {
            printf("La practica que quiere cargar ya esta ingresada, ingrese otra.\n");
        }
        flag3=1;
        }
        else
        {
            while (getchar () != '\n'); ///
            printf("No se pueden ingresar mas de 30 caracteres.\n");
        }
    }while(flag==1 || flag2==0 || flag3==0);
}
int ingreseCosto(int costo)
{

        printf("Ingrese el costo de la practica (1000$ a 10000$): ");
        costo = ingresarEnteroMinMax(1000,10000);
        return costo;
}
int ingreseBaja(int baja)
{
    printf("Esta de baja la practica(1) o esta activa(0)? ");
    baja = ingresarEnteroMinMax(0,1);
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
void cargarPracticas(char ArchivoPracticas[30])
{
    char seguir='s';
    stPracticas nuevaPractica;
    while(tolower(seguir)=='s')
    {
        ///FILE *archi_Practicas=fopen(ArchivoPracticas, "ab"); /// si se declara el archivo arriba y se cierra despues del while no se llega a actualizar el buffer del ID al poner nueva practica
        FILE *archi_Practicas=fopen(ArchivoPracticas, "ab");
        nuevaPractica = cargarUnaPractica();
        fwrite(&nuevaPractica, sizeof(stPracticas), 1, archi_Practicas);
        printf("Desea seguir ingresando practicas? (S/N)");
        seguir=ingresoSoloSNEnScan('s','n');
        fclose(archi_Practicas);
        system("pause");
        system("cls");
    }
}
void cargarPracticaEnArchivo(char ArchivoPracticas[30], stPracticas unaPractica, int *validosArregloPracticas)
{
    FILE *archi_Practicas=fopen(ArchivoPracticas, "ab");
    fwrite(&unaPractica,sizeof(stPracticas),1,archi_Practicas);
    (*validosArregloPracticas)++;
    fclose(archi_Practicas);
}

/// ------ C R E A C I O N  Y  C A R G A  D E  A R R E G L O  D I N A M I C O ------- ///
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

/// --------------------------- V A L I D A C I O N E S -------------------------- ///
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

/// --------------------- C O N T E O  D E  P R A C T I C A S -------------------- ///
int contarPracticas(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ARCHIVO_PRACTICAS,"rb");
    fseek(archivoPracticas,0,2);
    int cantidadDePracticas=ftell(archivoPracticas)/sizeof(stPracticas);
    fclose(archivoPracticas);
    return cantidadDePracticas;
}

/// --------------------- M U E S T R A  D E  P R A C T I C A S -------------------- ///
void mostrarPracticas(stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas)
{
      int limite=*validosArregloPracticas;
      for(int i=0;i<limite;i++)
      {
          stPracticas unaPractica=arregloDinamicoPracticas[i];
          mostrarUnaPractica(unaPractica);
      }
      system("pause");
      system("cls");
}
void mostrarPracticasDesdeArchivo(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        mostrarUnaPractica(unaPractica);
    }
    system("pause");
    system("cls");
    fclose(archivoPracticas);
}
void mostrarUnaPractica(stPracticas practicasAux)
{
    char activo[] = ("Activo");
    char inactivo[] = ("Inactivo");
    printf("ID: %i\n", practicasAux.idPractica);
    printf("Nombre: %s\n", practicasAux.nombre);
    printf("Costo: %i\n", practicasAux.costo);
    if (practicasAux.baja == 0)
    {
        printf("Estado: %s\n",activo);
    }
    else printf("Estado: %s\n",inactivo);
    printf("---------------------------------------\n");

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
    printf("--------------------------------------------\n");
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
    printf("--------------------------------------------\n");
    }
}

/// --------------------- M O D I F I C A R  P R A C T I C A S -------------------- ///
void modificarPracticas(char ArchivoPracticas[30])
{
        FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
        int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS);
        if(cantPracticas==0)
        {
            printf("No hay practicas cargadas para modificar.\n");
        }
        else
        {
            mostrarPracticasDesdeArchivo(ARCHIVO_PRACTICAS);
            int posicion=0;
            do
            {
            printf("Elija una practica para modificar (idPractica): ");
            posicion=ingresarEntero();
            if(posicion<1 || posicion>cantPracticas)
            {
                printf("Error, ingrese una practica valida (1 a %i).\n",cantPracticas);
            }
            }while(posicion<1 || posicion>cantPracticas);
            stPracticas unaPractica;
            fseek(archivoPracticas,(posicion-1)*sizeof(stPracticas),0);
            fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
            unaPractica=menuModificarPractica(unaPractica);
            fseek(archivoPracticas,(posicion-1)*sizeof(stPracticas),0);
            fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
        }
        fclose(archivoPracticas);
}
stPracticas menuModificarPractica(stPracticas unaPractica)
{
    int opcion=0;
    printf("Elija un dato para modificar:\n1-Nombre\n2-Costo\n0-Salir\n");
    opcion=ingresarEntero();
    switch(opcion)
    {
        case 1:
              ingreseNombre(unaPractica.nombre);
            break;
        case 2:
              unaPractica.costo=ingreseCosto(unaPractica.costo);
            break;
        case 0:
            printf("Vuelva pronto.\n");
            break;
        default:
            printf("Ingrese una opcion correcta(0 a 2)\n");
            break;
    }
    return unaPractica;
}
void modificarPracticaEnArchivo(char ArchivoPracticas[30], stPracticas unaPractica, int posicion)
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
    fseek(archivoPracticas,(posicion-1)*sizeof(stPracticas),0);
    fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
    fclose(archivoPracticas);
}

/// ----------- A L T A  Y  B A J A  L O G I C A  D E  P R A C T I C A S ---------- ///
void darDeBajaPracticas(char ArchivoPracticas[30])
{
      FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
      int flag=0;
      flag=verificarAltas(ARCHIVO_PRACTICAS);
      int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS);
      if(flag==0)
      {
          printf("No hay practicas activas para dar de baja.\n");
      }
      else
      {
      mostrarPracticasAlta(ARCHIVO_PRACTICAS);
      int nroPractica=0;
      do
      {
      printf("Elija una practica para dar de baja (idPractica): ");
      nroPractica=ingresarEntero();
      if(nroPractica<1 || nroPractica>cantPracticas)
            {
                printf("Error, ingrese una practica valida (1 a %i).\n",cantPracticas);
            }
      }while(nroPractica<1 || nroPractica>cantPracticas);
      stPracticas unaPractica;
      fseek(archivoPracticas,(nroPractica-1)*sizeof(stPracticas),0);
      fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
      unaPractica=darDeBajaUnaPractica(unaPractica);
      fseek(archivoPracticas,(nroPractica-1)*sizeof(stPracticas),0);
      fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
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
      FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
      int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS);
      int flag=0;
      flag=verificarBajas(ARCHIVO_PRACTICAS);
      if(flag==0)
      {
          printf("No hay practicas dadas de baja para dar de alta.\n");
      }
      else
      {
      mostrarPracticasBaja(ARCHIVO_PRACTICAS);
      int nroPractica=0;
      do
      {
      printf("Elija una practica para dar de alta (idPractica): ");
      nroPractica=ingresarEntero();
      if(nroPractica<1 || nroPractica>cantPracticas)
      {
          printf("Error, ingrese una practica valida (1 a %i)",cantPracticas);
      }
      }while(nroPractica<1 || nroPractica>cantPracticas);
      stPracticas unaPractica;
      fseek(archivoPracticas,(nroPractica-1)*sizeof(stPracticas),0);
      fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
      unaPractica=darDeAltaUnaPractica(unaPractica);
      fseek(archivoPracticas,(nroPractica-1)*sizeof(stPracticas),0);
      fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
      }
      fclose(archivoPracticas);
}
stPracticas darDeAltaUnaPractica(stPracticas unaPractica)
{
    unaPractica.baja=0;
    return unaPractica;
}
int verificarAltas(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    int flag=0;
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        if(unaPractica.baja==0)
        {
            flag=1;
        }
    }
    fclose(archivoPracticas);
    return flag;
}
int verificarBajas(char ArchivoPracticas[30])
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    int flag=0;
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        if(unaPractica.baja==1)
        {
            flag=1;
        }
    }
    fclose(archivoPracticas);
    return flag;
}

/// ------------------- B U S Q U E D A  D E  P R A C T I C A S ------------------- ///
void buscarPracticasPorNombre()
{
    int flag=1;
    char nombre[30];
    limpiarBuffer();
    printf("Ingrese el nombre de la practica a buscar: ");
    getchar();
    int flag2=0;
    do
    {
    fgets(nombre,30,stdin);
    if (strchr(nombre,'\n') != NULL)
    {
    nombre [strcspn(nombre,"\n")] = '\0';
    flag=ingresarSoloLetras(nombre);

    if(flag==0)
    {
        printf("Error, ingrese solo letras.\n");
    }
    flag2=1;
    }
    else
    {
        while (getchar () != '\n'); ///
        printf("No se pueden ingresar mas de 30 caracteres.\n");
    }
    }while(flag!=1 || flag2==0);
    nombre [strcspn(nombre,"\n")] = '\0';
    buscarPracticaPorNombre(nombre,ARCHIVO_PRACTICAS);
}
void buscarPracticaPorNombre(char nombrePractica[30], char ArchivoPracticas[30])
{
    FILE *archivoPracticas=abrirArchivo(ArchivoPracticas,"rb");
    int res=1;
    int posicion=0;
    stPracticas unaPractica;

    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        if (strcmpi(unaPractica.nombre,nombrePractica) == 0)
        {
            printf("La practica fue encontrada exitosamente: \n");
            mostrarUnaPractica(unaPractica);
            menuBusquedaPorNombre(unaPractica,posicion);
            res = 0;
        }
        posicion++;
    }
    if(res!=0)
    {
        printf("La practica buscada no se encuentra cargada.\n");
    }
    else
    {
//        printf("La practica fue encontrada exitosamente: \n");
//        mostrarUnaPractica(unaPractica);
//        menuBusquedaPorNombre(unaPractica,posicion);
    }
    fclose(archivoPracticas);
}
void menuBusquedaPorNombre(stPracticas unaPractica, int posicion)
{
    system("pause");
    system("cls");
    int opcion=0;
    do
    {
    printf("Que desea hacer con la practica?\n1-Modificar nombre o costo\n2-Dar de alta\n3-Dar de baja\n0-Salir\n");
    opcion=ingresarEntero();
    switch(opcion)
    {
        case 1: unaPractica=menuModificarPractica(unaPractica);
        modificarPracticaEnArchivo(ARCHIVO_PRACTICAS,unaPractica, posicion);
        break;
        case 2: unaPractica=darDeAltaUnaPractica(unaPractica);
        modificarPracticaEnArchivo(ARCHIVO_PRACTICAS,unaPractica,posicion);
        break;
        case 3: unaPractica=darDeBajaUnaPractica(unaPractica);
        modificarPracticaEnArchivo(ARCHIVO_PRACTICAS,unaPractica,posicion);
        break;
        case 0: printf("Vuelva pronto!\n");
        break;
        default: printf("Ingrese un numero correcto (0 a 3)\n");
        break;
    }
    }while(opcion!=0);
    system("pause");
    system("cls");
}
/// -------------------------------------- T E S T /// R A  F A /// ------------------------------------------ ///


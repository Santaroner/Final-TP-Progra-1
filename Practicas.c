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
//    getchar();
    do
    {
        printf("Ingrese el nombre de la practica: ");
//        void limpiarBuffer();
        fgets(nombre,30,stdin);
        if (strchr(nombre,'\n') != NULL) /// La condicion se cumple cuando hay espacio para el \n y no se exceden los 30 caracteres
        {
        nombre=primerLetraMayuscula(nombre);
        borrarSaltoDeLinea(nombre);
        flag2=ingresarSoloLetras(nombre); /// Verifico que solo ingrese letras
        if(flag2==0)
        {
            printf("Error, ingrese solo letras.\n");
        }
        flag=buscarNombreIgualPractica(nombre,ARCHIVO_PRACTICAS); /// Verifico que no ingrese un nombre de practica ya ingresado
        if(flag==1)
        {
            printf("La practica que quiere cargar ya esta ingresada, ingrese otra.\n");
        }
        flag3=1;
        }
        else /// Si se excede de 30 caracteres, que limpie el buffer
        {
            while (getchar () != '\n'); ///
            printf("No se pueden ingresar mas de 30 caracteres.\n");
        }
    }while(flag==1 || flag2==0 || flag3==0); /// Uso 3 condiciones, si alguna de ellas se cumple, se sigue pidiendo el nombre
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
void cargarPracticas(char ArchivoPracticas[])
{
    char seguir='s';
    stPracticas nuevaPractica;
    while(tolower(seguir)=='s')
    {
        ///FILE *archi_Practicas=fopen(ArchivoPracticas, "ab"); /// si se declara el archivo arriba y se cierra despues del while no se llega a actualizar el buffer del ID al poner nueva practica
        FILE *archi_Practicas=fopen(ArchivoPracticas, "ab");
        if(archi_Practicas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
        nuevaPractica = cargarUnaPractica(); /// Llamo a la funcion que crea una practica
        fwrite(&nuevaPractica, sizeof(stPracticas), 1, archi_Practicas); /// Esa practica cargada la cargo en el archivo
        printf("Desea seguir ingresando practicas? (S/N)");
        seguir=ingresoSoloSNEnScan('s','n'); /// Llamo a la funcion que asegura que solo se pueda ingresar la letra S o N
        fclose(archi_Practicas);
        system("pause");
        system("cls");
    }
}
void cargarPracticaEnArchivo(char ArchivoPracticas[], stPracticas unaPractica, int *validosArregloPracticas)
{
    FILE *archi_Practicas=fopen(ArchivoPracticas, "ab");
    if(archi_Practicas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    fwrite(&unaPractica,sizeof(stPracticas),1,archi_Practicas);
    (*validosArregloPracticas)++;
    fclose(archi_Practicas);
}

/// ------ C R E A C I O N  Y  C A R G A  D E  A R R E G L O  D I N A M I C O ------- ///
stPracticas *cargarArregloDinamicoPracticas(char ArchivoPracticas[], stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas)
{
    int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS);
    arregloDinamicoPracticas=(stPracticas *)realloc(arregloDinamicoPracticas, cantPracticas*sizeof(stPracticas)); /// Redimensiono el arreglo segun la cantidad de practicas que esten cargadas en el archivo
    traspasoDatos(arregloDinamicoPracticas,ARCHIVO_PRACTICAS,validosArregloPracticas);
    return arregloDinamicoPracticas;
}
void traspasoDatos(stPracticas *arregloDinamicoPracticas, char ArchivoPracticas[], int *validosArregloPracticas)
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    stPracticas unaPractica;
    if(archivoPracticas==NULL)
    {
        printf("Error al abrir el archivo.\n");
        *validosArregloPracticas=0;
    }
    int i=0;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0) /// Hago que lea cada practica del archivo y las vaya cargando en los campos del arreglo
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
int buscarNombreIgualPractica(char nombrePractica[30], char ArchivoPracticas[])
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    int flag=0;
    if(archivoPracticas==NULL)
    {
        printf("Error al abrir el archivo.\n");
        flag=0;
    }
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        int res=strcmpi(unaPractica.nombre,nombrePractica);
        if(res==0) /// Si es cero, quiere decir que encontro un nombre que es igual al ingresado
        {
            flag=1;
        }
    }
    fclose(archivoPracticas);
    return flag;
}

/// --------------------- C O N T E O  D E  P R A C T I C A S -------------------- ///
int contarPracticas(char ArchivoPracticas[])
{
    FILE *archivoPracticas=fopen(ARCHIVO_PRACTICAS,"rb");
    if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    fseek(archivoPracticas,0,2);
    int cantidadDePracticas=ftell(archivoPracticas)/sizeof(stPracticas); /// Divido el tamaño en bytes del archivo por el tamaño en bytes de un registro de practicas
    fclose(archivoPracticas);
    return cantidadDePracticas;
}

/// --------------------- M U E S T R A  D E  P R A C T I C A S -------------------- ///
void mostrarPracticas(stPracticas *arregloDinamicoPracticas, int *validosArregloPracticas)
{
      int limite=*validosArregloPracticas;
      for(int i=0;i<limite;i++)
      {
          stPracticas unaPractica=arregloDinamicoPracticas[i]; /// Recorro el arreglo y voy mostrando de a una practica
          mostrarUnaPractica(unaPractica);
      }
      system("pause");
      system("cls");
}
void mostrarPracticasDesdeArchivo(char ArchivoPracticas[])
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0) /// Es lo mismo que la anterior funcion, nada mas que esta lo hace desde el archivo
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
    if (practicasAux.baja == 0) /// Si es cero, lo muestra como activo
    {
        printf("Estado: %s\n",activo);
    }
    else printf("Estado: %s\n",inactivo); /// Si no es cero, lo muestra como inactivo
    printf("---------------------------------------\n");

}
void mostrarPracticasAlta(char archivoPracticas[]) /// Funcion que muestra las practicas que esten activas
{
    FILE *archi_Practicas=fopen(archivoPracticas, "rb");
    if(archi_Practicas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    stPracticas practicasAux;
    while((fread(&practicasAux, sizeof(stPracticas), 1, archi_Practicas)) > 0)
    {
        mostrarUnaPracticaAlta(practicasAux);
    }
    fclose(archi_Practicas);
}
void mostrarPracticasBaja(char archivoPracticas[]) /// Funcion que muestra las practicas que esten inactivas
{
    FILE *archi_Practicas=fopen(archivoPracticas, "rb");
    if(archi_Practicas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    stPracticas practicasAux;
    while((fread(&practicasAux, sizeof(stPracticas), 1, archi_Practicas)) > 0)
    {
        mostrarUnaPracticaBaja(practicasAux);
    }
    fclose(archi_Practicas);
}
void mostrarUnaPracticaAlta(stPracticas practicasAux)
{
    if(practicasAux.baja==0) /// Si se cumple la condicion de que este activa, se muestra
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
    if(practicasAux.baja==1) /// Si se cumple la condicion de que este inactiva, se muestra
    {
    printf("idPractica: %i\n", practicasAux.idPractica);
    printf("Nombre: %s\n", practicasAux.nombre);
    printf("Costo: %i\n", practicasAux.costo);
    printf("Baja (0 activo, 1 baja): %i\n", practicasAux.baja);
    printf("--------------------------------------------\n");
    }
}

/// --------------------- M O D I F I C A R  P R A C T I C A S -------------------- ///
void modificarPracticas(char ArchivoPracticas[])
{
        FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
        if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
        int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS); /// Cuento la cantidad de practicas con la funcion correspondiente
        if(cantPracticas==0)
        {
            printf("No hay practicas cargadas para modificar.\n");
        }
        else
        {
            mostrarPracticasDesdeArchivo(ARCHIVO_PRACTICAS); /// Muestro la lista de practicas desde el archivo por comodidad
            int posicion=0;
            do
            {
            printf("Elija una practica para modificar (idPractica): ");
            posicion=ingresarEntero(); /// Con esta funcion me garantizo que solo se ingresen numeros
            if(posicion<1 || posicion>cantPracticas)
            {
                printf("Error, ingrese una practica valida (1 a %i).\n",cantPracticas);
            }
            }while(posicion<1 || posicion>cantPracticas); /// Con estas condiciones me garantizo que se ingrese una de las practicas que este cargada
            stPracticas unaPractica;
            fseek(archivoPracticas,(posicion-1)*sizeof(stPracticas),0); /// Me posiciono al inicio de la practica elegida
            fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas); /// Leo esa practica
            unaPractica=menuModificarPractica(unaPractica); /// Llamo a una funcion que ofrece un menu de modificacion y retorna la practica modificada
            fseek(archivoPracticas,(posicion-1)*sizeof(stPracticas),0); /// Me vuelvo a posicionar al inicio de esa practica
            fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas); /// La escribo
        }
        fclose(archivoPracticas);
}
stPracticas menuModificarPractica(stPracticas unaPractica)
{
    int opcion=0;
    printf("Elija un dato para modificar:\n1-Nombre\n2-Costo\n0-Salir\n");
    opcion=ingresarEntero(); /// Me garantizo que solo ingrese numeros
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
    system("pause");
    system("cls");
    return unaPractica;
}
void modificarPracticaEnArchivo(char ArchivoPracticas[], stPracticas unaPractica, int posicion)
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
    if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    fseek(archivoPracticas,(posicion-1)*sizeof(stPracticas),0);
    fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
    fclose(archivoPracticas);
}

/// ----------- A L T A  Y  B A J A  L O G I C A  D E  P R A C T I C A S ---------- ///
void darDeBajaPracticas(char ArchivoPracticas[])
{
      FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
      if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
      int flag=0;
      flag=verificarAltas(ARCHIVO_PRACTICAS);
      int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS);
      if(flag==0)
      {
          printf("No hay practicas activas para dar de baja.\n");
      }
      else
      {
      mostrarPracticasAlta(ARCHIVO_PRACTICAS); /// Muestro las practicas que esten activas
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
      fseek(archivoPracticas,(nroPractica-1)*sizeof(stPracticas),0); /// Aca sucede lo mismo que explique en la funcion de modificar practicas
      fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas);
      unaPractica=darDeBajaUnaPractica(unaPractica); /// Llamo a esta funcion que retorna una practica dada de baja
      fseek(archivoPracticas,(nroPractica-1)*sizeof(stPracticas),0);
      fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas); /// Escribo esa funcion dada de baja en el archivo
      }
      fclose(archivoPracticas);
      system("pause");
      system("cls");
}
stPracticas darDeBajaUnaPractica(stPracticas unaPractica)
{
    unaPractica.baja=1; /// Cambia a 1, es decir, la pasa a inactiva
    return unaPractica;
}
void darDeAltaPracticas(char ArchivoPracticas[])
{
      FILE *archivoPracticas=fopen(ArchivoPracticas,"r+b");
      if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
      int cantPracticas=contarPracticas(ARCHIVO_PRACTICAS);
      int flag=0;
      flag=verificarBajas(ARCHIVO_PRACTICAS);
      if(flag==0)
      {
          printf("No hay practicas dadas de baja para dar de alta.\n");
      }
      else
      {
      mostrarPracticasBaja(ARCHIVO_PRACTICAS); /// Muestro solo las practicas que esten inactivas
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
      unaPractica=darDeAltaUnaPractica(unaPractica); /// Llamo a esta funcion que retorna una practica dada de alta
      fseek(archivoPracticas,(nroPractica-1)*sizeof(stPracticas),0);
      fwrite(&unaPractica,sizeof(stPracticas),1,archivoPracticas); /// Escribo esa practica dada de alta en el archivo
      }
      fclose(archivoPracticas);
      system("pause");
      system("cls");
}
stPracticas darDeAltaUnaPractica(stPracticas unaPractica)
{
    unaPractica.baja=0; /// La cambia a 0, es decir, la pasa a activa
    return unaPractica;
}
int verificarAltas(char ArchivoPracticas[]) /// Esta funcion verifica si hay practicas dadas de alta
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    int flag=0;
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        if(unaPractica.baja==0)
        {
            flag=1; /// Si la practica esta activa, flag vale 1
        }
    }
    fclose(archivoPracticas);
    return flag;
}
int verificarBajas(char ArchivoPracticas[]) /// Esta funcion verifica que haya practicas dadas de baja
{
    FILE *archivoPracticas=fopen(ArchivoPracticas,"rb");
    if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    int flag=0;
    stPracticas unaPractica;
    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0)
    {
        if(unaPractica.baja==1)
        {
            flag=1; /// Si la practica esta inactiva, flag vale 1
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
    ///limpiarBuffer();
    printf("Ingrese el nombre de la practica a buscar: ");
    getchar();
    int flag2=0;
    do
    {
    fgets(nombre,30,stdin);
    if (strchr(nombre,'\n') != NULL) /// Si no se exceden los 30 caracteres del string, esta condicion se cumple
    {
    nombre [strcspn(nombre,"\n")] = '\0';
    flag=ingresarSoloLetras(nombre); /// Garantizo que solo se ingresen letras

    if(flag==0)
    {
        printf("Error, ingrese solo letras.\n");
    }
    flag2=1;
    }
    else /// Si la condicion de los 30 caracteres no se cumple, se limpia el buffer y se avisa por pantalla el error
    {
        while (getchar () != '\n'); ///
        printf("No se pueden ingresar mas de 30 caracteres.\n");
    }
    }while(flag!=1 || flag2==0); /// Estas dos condiciones son fundamentales para que solo se ingresen letras y no se excedan los 30 caracteres
    buscarPracticaPorNombre(nombre,ARCHIVO_PRACTICAS); /// Llamo a una funcion que compara el nombre ingresado con los cargados en el archivo
}
void buscarPracticaPorNombre(char nombrePractica[30], char ArchivoPracticas[])
{
    FILE *archivoPracticas=abrirArchivo(ArchivoPracticas,"rb");
    if(archivoPracticas==NULL)
        {
            printf("Error al abrir el archivo.\n");
        }
    int res=1;
    int posicion=1;
    stPracticas unaPractica;

    while(fread(&unaPractica,sizeof(stPracticas),1,archivoPracticas)>0) /// Voy leyendo el archivo y comparando el nombre ingresado por el usuario con los del archivo
    {
        if (strcmpi(unaPractica.nombre,nombrePractica) == 0) /// Si es cero, quiere decir que es igual
        {
            printf("La practica fue encontrada exitosamente: \n");
            mostrarUnaPractica(unaPractica); /// Muestro la practica encontrada
            menuBusquedaPorNombre(unaPractica,posicion); /// Llamo a una funcion que ofrece un menu para modificar la practica
            res = 0; /// Lo paso a cero para que no se cumpla la condicion de abajo
        }
        posicion++; /// Voy sumando las posicion ya que la necesito para la funcion del menu
    }
    if(res!=0) /// Si no se encontro ninguna practica que tenga el mismo nombre, se cumple la condicion
    {
        printf("La practica buscada no se encuentra cargada.\n");
    }
    fclose(archivoPracticas);
}
void menuBusquedaPorNombre(stPracticas unaPractica, int posicion)
{
    system("pause");
    system("cls");
    int opcion=0;
    printf("Que desea hacer con la practica?\n1-Modificar nombre o costo\n2-Dar de alta\n3-Dar de baja\n0-Salir\n");
    opcion=ingresarEntero();
    switch(opcion)
    {
        case 1: unaPractica=menuModificarPractica(unaPractica); /// Llamo a la funcion que otorga un menu de modificacion
        modificarPracticaEnArchivo(ARCHIVO_PRACTICAS,unaPractica, posicion); /// Cargo esa practica retornada en el archivo
        break;
        case 2: unaPractica=darDeAltaUnaPractica(unaPractica); /// Lo mismo con el resto
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
    system("pause");
    system("cls");
}
/// -------------------------------------- T E S T /// R A  F A /// ------------------------------------------ ///


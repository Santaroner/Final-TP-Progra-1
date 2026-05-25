
typedef struct
 {
     int idPractica;/// Campo único y autoincremental
     char nombre[30];
     int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
     int baja; /// 0 si está activo, 1 si está eliminado.
 } stPracticas;

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
            printf("La practica ya esta ingresada");
        }
        }while(flag==0);
        printf("Ingrese el costo de la practica: ");
        scanf("%i", &practicas[validos].costo);
        printf("Esta de baja la practica(1) o esta activa(0)? ");
        scanf("%i", &practicas[validos].baja);
        idPractica++;
        printf("Desea seguir ingresando practicas? ");
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
        int res=strcmpi(practicas[i].nombre, practicas[i-1].nombre);
        if(res==0)
        {
            flag=0;
        }
    }
    return flag;
}

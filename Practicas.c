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
        static int idPractica=1;
        practicas.idPractica=idPractica;
        printf("Ingrese el nombre de la practica: ");
        scanf("%s", practicas.nombre);
        printf("Ingrese el costo de la practica: ");
        scanf("%i", &practicas.costo);
        printf("Esta de baja la practica(1) o esta activa(0)? ");
        scanf("%i", &practicas.baja);
        idPractica++;
        printf("Desea seguir ingresando practicas? ");
        scanf(" %c", &seguir);
        validos++;
    }
    return validos;
}
int buscarNombrePractica(stPracticas practicas[20], int validos)
{
    for(int i=0;i<validos;i++)
    {
        int res=strcmpi(practicas[i].nombre, practicas[i-1].nombre);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "pila.h"
#include "Structs.h" /// libreria para crear estructuras .h

///probando git



int main()
{
    stPaciente rafael;
    stLaboratorios mitre;
    stPracticas Nose;

    printf("Ingreso:");
    fgets(rafael.nombre,30,stdin);

    printf("Ingrese idpaciente:\n");
    scanf("%i",&mitre.idPaciente);
    printf("nombre : %s, id:%i\n", rafael.nombre, mitre.idPaciente);



    return 0;
}

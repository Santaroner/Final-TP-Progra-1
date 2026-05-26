#include <stdio.h>
int GetIDPacientes ()
{
    int aux;
    static int IDEstatico = 1;
    aux = IDEstatico;
    IDEstatico ++;
    return aux;
}



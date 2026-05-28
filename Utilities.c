#include <stdio.h>
//int GetIDPacientes ()
//{
//    int aux;
//    static int IDEstatico = 1;
//    aux = IDEstatico;
//    IDEstatico ++;
//    return aux;
//}

int GetIDPacientes ()
{
    FILE *archi = fopen("TestPacientes","ab");
    int aux;
    static int IDEstatico = 1;
    aux = IDEstatico;
    IDEstatico ++;
    return aux;
}





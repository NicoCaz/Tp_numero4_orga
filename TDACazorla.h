#include <stdio.h>
#include <stdlib.h>


typedef struct {
    long int DNI;
    char nombre[15];
    unsigned short int edad;
    char categoria, sexo;
    unsigned int tiempo;
} regCorredor;



long int BuscaExist(FILE *arch,long int posini,regCorredor reg);
long int BuscaPosVal(FILE *arch,long int posini,regCorredor reg);

#include "TDACazorla.h"

long int BuscaExist(FILE *arch,long int posini,regCorredor reg)
{
    regCorredor aux;
    fseek(arch,posini,0);
    fread(&aux,sizeof(regCorredor),1,arch);
    while (!feof(arch) && aux.DNI!=reg.DNI)
        fread(&aux,sizeof(regCorredor),1,arch);
    if (feof(arch))
    {
        fseek(arch,0,0);
        while (ftell(arch)!=posini && aux.DNI!=reg.DNI)
            fread(&aux,sizeof(regCorredor),1,arch);
    }
    if (aux.DNI==reg.DNI)
        return ftell(arch)-sizeof(regCorredor);
    else
        return -1;
}

long int BuscaPosVal(FILE *arch,long int posini,regCorredor reg)
{
    regCorredor aux;
    fseek(arch,posini,0);
    fread(&aux,sizeof(regCorredor),1,arch);
    while (!feof(arch) && aux.DNI!=reg.DNI)
        fread(&aux,sizeof(regCorredor),1,arch);
    if (feof(arch))
    {
        fseek(arch,0,0);
        while (ftell(arch)!=posini)
            fread(&aux,sizeof(regCorredor),1,arch);
        return 0;
    }
    else if (reg.DNI== aux.DNI)
            return 0;
        else
            return -1;
}

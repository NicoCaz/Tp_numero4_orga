#include <stdio.h>
#include <stdlib.h>
#include "TDACazorla.h"

int funcionHash(long int DNI);
void alta() ;
void generarArchivo();

int main() {
    generarArchivo();
    alta();
    return 0;
}


void generarArchivo() {
    FILE* ARCH;
    regCorredor nuevo;
    int i;
    ARCH = fopen("corredores.dat","wb");
    for (i=0; i<12000; i++)
        fwrite(&nuevo,sizeof(regCorredor),1,ARCH);
    fclose(ARCH);
}

void alta() {
    FILE* ARCH,*archNuevo;
    archNuevo=fopen("alta.txt","r");
    regCorredor nuevo,aux;
    int hashNuevo,i;
    fscanf(archNuevo,"%ld",&nuevo.DNI);
    hashNuevo = nuevo.DNI % 11987;
    ARCH = fopen("corredores.dat","rb+");
    if (ARCH != NULL) {
        fseek(ARCH,hashNuevo*sizeof(regCorredor),0);
        fread(&aux,sizeof(regCorredor),1,ARCH);
        i = 0;
        while (aux.DNI != 0 && fread(&aux,sizeof(regCorredor),1,ARCH))
            i++;
        if (!feof(ARCH)) {
            fseek(ARCH,(hashNuevo+i)*sizeof(regCorredor),0);
            fwrite(&nuevo,sizeof(regCorredor),1,ARCH);
            if (i != 0)
                printf("Hubo una colisión. Se escribio fuera de hash.");
        } else {
            fseek(ARCH,0,0);
            fread(&aux,sizeof(regCorredor),1,ARCH);
            i = 0;
            while (i < hashNuevo && aux.DNI != 0 && fread(&aux,sizeof(regCorredor),1,ARCH))
                i++;
            if (i != hashNuevo) {
                fseek(ARCH,i*sizeof(regCorredor),0);
                fwrite(&nuevo,sizeof(regCorredor),1,ARCH);
                printf("Hubo una colisión. Se escribio fuera de hash.");
            } else
                printf("No hay espacio en el archivo.");
        }
        fclose(ARCH);
    } else
        printf("No existe el archivo.");
}

void Modif(regCorredor reg, char *file)
{
    long int pos;
    FILE *arch;
    arch=fopen(file,"rb+");
    if (!arch)
        printf("\n El archivo que sea modificar no existe");
    else
    {
        pos=BuscaExist(arch,reg.DNI % 11987,reg);
        if (pos>0)
        {
            fseek(arch,pos,1);
            fwrite(&reg,sizeof(regCorredor),1,arch);
        }
        else
            printf("\nEl participante que desea modificar no existe");
    }
    fclose(arch);
}

void Baja(regCorredor reg, char *file)
{
    long int pos;
    FILE *arch;
    arch=fopen(file,"rb+");
    if (!arch)
        printf("\nEl archivo que sea modificar no existe");
    else
    {
        pos=BuscaExist(arch,reg.DNI % 11987,reg);
        if (pos>0)
        {
            fseek(arch,pos,1);
            fread(&reg,sizeof(regCorredor),1,arch);
            fseek(arch,pos,1);
            fwrite(&reg,sizeof(regCorredor),1,arch);
        }
        else
            printf("\n El participante que desea eliminar no existe");
    }
    fclose(arch);
}

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long int DNI;
    char nombre[15];
    unsigned short int edad;
    char categoria, sexo;
    unsigned int tiempo;
} regCorredor;

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


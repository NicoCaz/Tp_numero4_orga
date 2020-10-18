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

void Modif(regCorredor reg, char *file) {
    long int pos;
    FILE *arch;
    arch=fopen(file,"rb+");
    if (!arch)
        printf("\n El archivo que sea modificar no existe");
    else {
        pos=BuscaExist(arch,reg.DNI % 11987,reg);
        if (pos>0) {
            fseek(arch,pos,1);
            fwrite(&reg,sizeof(regCorredor),1,arch);
        } else
            printf("\nEl participante que desea modificar no existe");
    }
    fclose(arch);
}

void Baja(regCorredor reg, char *file) {
    long int pos;
    FILE *arch;
    arch=fopen(file,"rb+");
    if (!arch)
        printf("\nEl archivo que sea modificar no existe");
    else {
        pos=BuscaExist(arch,reg.DNI % 11987,reg);
        if (pos>0) {
            fseek(arch,pos,1);
            fread(&reg,sizeof(regCorredor),1,arch);
            fseek(arch,pos,1);
            fwrite(&reg,sizeof(regCorredor),1,arch);
        } else
            printf("\n El participante que desea eliminar no existe");
    }
    fclose(arch);
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------------
//   PUNTO 4.2
//-------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char apellidoYNombre[30];
    char direccion[20];
    long int telefono;
    char fecha[11];
    int sigColision;
} regPersona;

int funcionHash2(char apellidoYNombre[30]);

void generarArchivo();

void nuevoRegistro(regPersona * persona);

//Se asume que el usuario no ingresa apellido y nombre repetidos.
void alta();

void baja(char apellidoYNombre[30]);

void modificacion();


int funcionHash2(char apellidoYNombre[30]) {
    int retorno = 0;
    for (int i=0; i<strlen(apellidoYNombre); i++)
        retorno += apellidoYNombre[i];
    return retorno % 11987;
}

void generarArchivo2() {
    FILE* ARCH;
    regPersona nulo;
    int i;
    ARCH = fopen("personas.dat","wb+");
    for (i=0; i<12000; i++)
        fwrite(&nulo,sizeof(regPersona),1,ARCH);
    fclose(ARCH);
}

void nuevoRegistro(regPersona * persona) {

}

void alta2() {
    int hashNuevo,i = 0;
    regPersona nuevo, aux, aux2, aux3;
    FILE* ARCH, *ARCH2;
    ARCH = fopen("personas.dat","rb+");
    if (ARCH != NULL) {
        nuevoRegistro(&nuevo);
        hashNuevo = funcionHash2(nuevo.apellidoYNombre);
        fseek(ARCH,hashNuevo*sizeof(regPersona),0);
        fread(&aux,sizeof(regPersona),1,ARCH);
        if (strcmp(aux.apellidoYNombre,"") == 0) {
            fseek(ARCH,hashNuevo*sizeof(regPersona),0);
            fwrite(&nuevo,sizeof(regPersona),1,ARCH);
        } else {
            ARCH2 = fopen("colisiones.dat","rb+");
            if (ARCH2 != NULL) {
                if (aux.sigColision == -1) {
                    while (fread(&aux2,sizeof(regPersona),1,ARCH2) == 1 && (aux2.apellidoYNombre,"") != 0)
                        i++;
                    fwrite(&nuevo,sizeof(regPersona),1,ARCH);
                    aux.sigColision = i;
                } else {
                    fseek(ARCH2,aux.sigColision*sizeof(regPersona),0);
                    while (fread(&aux2,sizeof(regPersona),1,ARCH2) == 1 && aux2.sigColision != -1)
                        fseek(ARCH2,aux2.sigColision*sizeof(regPersona),0);
                    fseek(ARCH2,0,0);
                    while (fread(&aux3,sizeof(regPersona),1,ARCH2) == 1 && (aux3.apellidoYNombre,"") != 0)
                        i++;
                    fwrite(&nuevo,sizeof(regPersona),1,ARCH2);
                    aux2.sigColision = i;
                }
                fclose(ARCH2);
            } else
                printf("No se encontr� el archivo.\n");
        }
    } else
        printf("No se encontr� el archivo.\n");
}

void baja(char apellidoYNombre[30]) {
    int hashNuevo,i = 0;
    regPersona nuevo, nulo, aux, aux2, aux3;
    FILE* ARCH, *ARCH2;
    ARCH = fopen("personas.dat","rb+");
    if (ARCH != NULL) {
        hashNuevo = funcionHash2(apellidoYNombre);
        fseek(ARCH,hashNuevo*sizeof(regPersona),0);
        fread(&aux,sizeof(regPersona),1,ARCH);
        if (strcmp(aux.apellidoYNombre,apellidoYNombre) == 0)
            if (aux.sigColision == -1) {
                fseek(ARCH,hashNuevo*sizeof(regPersona),0);
                fwrite(&nulo,sizeof(regPersona),1,ARCH);
            } else {
                ARCH2 = fopen("colisiones.dat","rb+");
                fseek(ARCH2,aux.sigColision*sizeof(regPersona),0);
                fread(&aux2,sizeof(regPersona),1,ARCH2);
                fseek(ARCH2,aux.sigColision*sizeof(regPersona),0);
                fwrite(&nulo,sizeof(regPersona),1,ARCH2);
                fseek(ARCH,hashNuevo*sizeof(regPersona),0);
                fwrite(&aux2,sizeof(regPersona),1,ARCH);
            } else if (aux.sigColision != -1) {
            i = aux.sigColision;
            fseek(ARCH2,aux.sigColision*sizeof(regPersona),0);
            fread(&aux2,sizeof(regPersona),1,ARCH2);
            while (strcmp(aux2.apellidoYNombre,apellidoYNombre) != 0 && aux2.sigColision != -1) {
                i = aux2.sigColision;
                fseek(ARCH2,aux2.sigColision*sizeof(regPersona),0);
                fread(&aux2,sizeof(regPersona),1,ARCH2);
            }
            if (strcmp(aux2.apellidoYNombre,apellidoYNombre) == 0)
                if (i == aux.sigColision) {
                    fseek(ARCH2,aux.sigColision*sizeof(regPersona),0);
                    aux.sigColision = aux2.sigColision;
                    fwrite(&nulo,sizeof(regPersona),1,ARCH2);
                    fseek(ARCH,hashNuevo*sizeof(regPersona),0);
                    fwrite(&aux,sizeof(regPersona),1,ARCH);
                } else {
                    fseek(ARCH2,i*sizeof(regPersona),0);
                    fread(&aux3,sizeof(regPersona),1,ARCH2);
                    fseek(ARCH2,aux3.sigColision*sizeof(regPersona),0);
                    aux3.sigColision = aux2.sigColision;
                    fwrite(&nulo,sizeof(regPersona),1,ARCH2);
                    fseek(ARCH2,i*sizeof(regPersona),0);
                    fwrite(&aux3,sizeof(regPersona),1,ARCH2);
                } else
                printf("No existe la persona a eliminar.");
        } else
            printf("No existe la persona a eliminar.");
        fclose(ARCH);
    } else
        printf("No se encontr� el archivo.\n");
}

void modificacion() {
    int hashNuevo,i;
    regPersona nuevo, aux, aux2, aux3;
    FILE* ARCH, *ARCH2;
    ARCH = fopen("personas.dat","rb+");
    if (ARCH != NULL) {
        nuevoRegistro(&nuevo);
        hashNuevo = funcionHash2(nuevo.apellidoYNombre);
        fseek(ARCH,hashNuevo*sizeof(regPersona),0);
        fread(&aux,sizeof(regPersona),1,ARCH);
        if (strcmp(aux.apellidoYNombre,nuevo.apellidoYNombre) == 0) {
            nuevo.sigColision = aux.sigColision;
            fseek(ARCH,hashNuevo*sizeof(regPersona),0);
            fwrite(&nuevo,sizeof(regPersona),1,ARCH);
        } else {
            if (aux.sigColision == -1)
                printf("No existe la persona a modificar.");
            else {
                ARCH2 = fopen("colisiones.dat","rb+");
                if (ARCH2 != NULL) {
                    i = aux.sigColision;
                    fseek(ARCH2,aux.sigColision*sizeof(regPersona),0);
                    while (fread(&aux2,sizeof(regPersona),1,ARCH2) == 1 && strcmp(aux2.apellidoYNombre,nuevo.apellidoYNombre) != 0) {
                        i = aux2.sigColision;
                        fseek(ARCH2,aux2.sigColision*sizeof(regPersona),0);
                    }
                    if (strcmp(aux2.apellidoYNombre,nuevo.apellidoYNombre) == 0) {
                        nuevo.sigColision = aux2.sigColision;
                        fseek(ARCH2,i*sizeof(regPersona),0);
                        fwrite(&nuevo,sizeof(regPersona),1,ARCH2);
                    } else
                        printf("No existe la persona a modificar.");
                    fclose(ARCH2);
                } else
                    printf("No se encontr� el archivo.\n");
            }
        }
        fclose(ARCH);
    } else
        printf("No se encontr� el archivo.\n");
}




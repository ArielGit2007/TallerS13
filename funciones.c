#include <stdio.h>
#include "funciones.h"
#include <string.h>


int leerIntegerRango(int inicio, int fin){
    int num;
    int val;
    do{
        val = scanf("%d",&num);
        if (val != 1 || num<inicio || num>fin)
        {
            printf("El dato ingresado es invalido\n");
            while(getchar()!='\n');
        }
    }while(val != 1 || num<inicio || num>fin);
    return num;
}
float leerFlotanteRango(float inicio, float fin){
    float num;
    int val;
    do{
        val = scanf("%f",&num);
        if (val != 1 || num<inicio || num>fin)
        {
            printf("El dato ingresado es invalido\n");
            while(getchar()!='\n');
        }
    }while(val != 1 || num<inicio || num>fin);
    return num;
}


void LeerDatosAuto(){
DatosAuto datos_auto;

while(getchar()!='\n');
printf("Ingrese el ID del auto:\n");
datos_auto.id=leerIntegerRango(1000,9999);
validarID(&datos_auto.id);
while(getchar()!='\n');

printf("Ingrese la marca del auto:\n");
fgets(datos_auto.Marca,sizeof(datos_auto.Marca),stdin);
BorrarSaltolinea(datos_auto.Marca);   
printf("Ingrese el anio del auto:\n");
datos_auto.Anio = leerIntegerRango(1950, 2025);
printf("Ingrese el precio del auto:\n");
datos_auto.Precio = leerFlotanteRango(0, 1000000);
while(getchar()!='\n');
printf("Ingrese el color del auto:\n");
fgets(datos_auto.Color,sizeof(datos_auto.Color),stdin);
BorrarSaltolinea(datos_auto.Color);
printf("Ingrese el estado del auto:\n");
fgets(datos_auto.Estado,sizeof(datos_auto.Estado),stdin);
BorrarSaltolinea(datos_auto.Estado);
printf("Ingrese el modelo del auto:\n");
fgets(datos_auto.modelo,sizeof(datos_auto.modelo),stdin);
BorrarSaltolinea(datos_auto.modelo);
datos_auto.Activo=1;


GuardarDatosAuto(&datos_auto);
}

void mostrarDatosAuto(){
    
    DatosAuto autos[10];
    int count=leerDatosAuto(autos);
    printf("|%-6s| %-14s| %-7s| %-12s| %-9s| %-11s| %-15s|\n","ID","Marca","Anio","Precio","Color","Estado","Modelo");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        
        if (autos[i].Activo==1)
        {
            printf("|%-6d| %-14s| %-7d| %-12.2f| %-9s| %-11s| %-15s|\n",autos[i].id,autos[i].Marca,autos[i].Anio,autos[i].Precio,autos[i].Color,autos[i].Estado,autos[i].modelo);
        }
        
    }
    
}

void validarID(int *id){
    DatosAuto autos[10];
    int count=leerDatosAuto(autos);
    int disponible=0;
    do{
       if (count==0){
        disponible=1;
       } else {
         
        for (int i = 0; i < count; i++)
        {
            if (autos[i].id==(*id) && autos[i].Activo==1)
            {
                printf("El ID ya existe. Ingrese otro ID:\n");
                *id=leerIntegerRango(1000,9999);
                disponible=0;
                break;
            }
            else{
                disponible=1;
            }
        }
       }
    }while(disponible==0);
    return;
    
}

//ARCHIVOS BINARIOS 
void GuardarDatosAuto(DatosAuto *autos){
    FILE *f;
    f=fopen("autos.dat","ab+");
    if (f==NULL)
    {
        printf("No se puede abrir el archivo\n");
        return;
    }
    fwrite(autos,sizeof(DatosAuto),1,f);
    fclose(f);
    

}
int leerDatosAuto(DatosAuto *autos){
    FILE *f;
    f=fopen("autos.dat","rb");
    if (f==NULL)
    {
        f=fopen("autos.dat","ab+");
        if (f != NULL) fclose(f);
        return 0;
    }
    int count=fread(autos,sizeof(DatosAuto),10,f);
    fclose(f);
    return count;
}

void BorrarSaltolinea(char *a)
{
    int len = strlen(a);
    if (len > 0 && a[len - 1] == '\n')
    {                      // se asegura de que la cadena no este vacia y de que el ultimo caracter si sea un salto de linea
        a[len - 1] = '\0'; // De haber un salto de linea, lo cambia por el valor nulo
    }
}


#include <stdio.h>
#include "funciones.h"
#include <string.h>

int leerIntegerRango(int inicio, int fin)
{
    int num;
    int val;
    do
    {
        val = scanf("%d", &num);
        if (val != 1 || num < inicio || num > fin)
        {
            printf("El dato ingresado es invalido\n");
            while (getchar() != '\n')
                ;
        }
    } while (val != 1 || num < inicio || num > fin);
    return num;
}
float leerFlotanteRango(float inicio, float fin)
{
    float num;
    int val;
    do
    {
        val = scanf("%f", &num);
        if (val != 1 || num < inicio || num > fin)
        {
            printf("El dato ingresado es invalido\n");
            while (getchar() != '\n')
                ;
        }
    } while (val != 1 || num < inicio || num > fin);
    return num;
}

void LeerDatosAuto()
{
    DatosAuto datos_auto;

    while (getchar() != '\n')
        ;
    printf("Ingrese el ID del auto:\n");
    datos_auto.id = leerIntegerRango(1000, 9999);
    validarID(&datos_auto.id);
    while (getchar() != '\n')
        ;

    printf("Ingrese la marca del auto:\n");
    fgets(datos_auto.Marca, sizeof(datos_auto.Marca), stdin);
    BorrarSaltolinea(datos_auto.Marca);
    printf("Ingrese el anio del auto:\n");
    datos_auto.Anio = leerIntegerRango(1950, 2025);
    printf("Ingrese el precio del auto:\n");
    datos_auto.Precio = leerFlotanteRango(0, 1000000);
    while (getchar() != '\n')
        ;
    printf("Ingrese el color del auto:\n");
    fgets(datos_auto.Color, sizeof(datos_auto.Color), stdin);
    BorrarSaltolinea(datos_auto.Color);
    printf("Ingrese el estado del auto:\n");
    fgets(datos_auto.Estado, sizeof(datos_auto.Estado), stdin);
    BorrarSaltolinea(datos_auto.Estado);
    printf("Ingrese el modelo del auto:\n");
    fgets(datos_auto.modelo, sizeof(datos_auto.modelo), stdin);
    BorrarSaltolinea(datos_auto.modelo);
    datos_auto.Activo = 1;
    datos_auto.cliente.id = 0;
    strcpy(datos_auto.cliente.Nombre, "");
    datos_auto.Disponible = 1;

    GuardarDatosAuto(&datos_auto);
}

void mostrarDatosAuto()
{

    DatosAuto autos[20];
    int count = leerDatosAuto(autos);
    printf("|%-6s| %-14s| %-7s| %-12s| %-9s| %-11s| %-15s|\n", "ID", "Marca", "Anio", "Precio", "Color", "Estado", "Modelo");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {

        {
            if (autos[i].Activo == 1)
            {
                printf("|%-6d| %-14s| %-7d| %-12.2f| %-9s| %-11s| %-15s|\n",
                       autos[i].id,
                       autos[i].Marca,
                       autos[i].Anio,
                       autos[i].Precio,
                       autos[i].Color, autos[i].Estado, autos[i].modelo);

                if ((autos[i].cliente.Nombre[0] != '\0' && autos[i].cliente.id != 0))
                {
                    printf("   -> Comprado por: %s (ID: %d)\n", autos[i].cliente.Nombre, autos[i].cliente.id);
                }
            }
        }
    }
}

void validarID(int *id)
{
    DatosAuto autos[20];
    int count = leerDatosAuto(autos);
    int disponible = 0;
    do
    {
        if (count == 0)
        {
            disponible = 1;
        }
        else
        {

            for (int i = 0; i < count; i++)
            {
                if (autos[i].id == (*id) && autos[i].Activo == 1)
                {
                    printf("El ID ya existe. Ingrese otro ID:\n");
                    *id = leerIntegerRango(1000, 9999);
                    disponible = 0;
                    break;
                }
                else
                {
                    disponible = 1;
                }
            }
        }
    } while (disponible == 0);
    return;
}

void HacerCompra()
{
    DatosAuto autos[20];
    int count = leerDatosAuto(autos);
    printf("Ingrese el ID del auto que desea comprar:\n");
    int Id = leerIntegerRango(1000, 9999);
    int Posicion = EncontarAutoID(autos, Id);
    printf("DEBUG: Posicion=%d, ID encontrado=%d\n", Posicion, autos[Posicion].id);
    if (Posicion != -1 && autos[Posicion].Disponible == 1)
    {
        printf("Ingrese los datos del cliente:\n");
        while (getchar() != '\n')
            ;
        printf("Nombre del cliente:\n");
        fgets(autos[Posicion].cliente.Nombre, sizeof(autos[Posicion].cliente.Nombre), stdin);
        BorrarSaltolinea(autos[Posicion].cliente.Nombre);
        printf("ID del cliente:\n");
        autos[Posicion].cliente.id = leerIntegerRango(1000, 9999);
        autos[Posicion].Disponible = 0;

        GuardarAutoEnPosicion(autos, Posicion);
        printf("Compra realizada con exito.\n");
    }
    else if (Posicion != -1 && autos[Posicion].Disponible == 0)
    {
        printf("El auto con ID %d no esta disponible para la venta.\n", Id);
    }
    else
    {
        printf("No se encontro un auto con el ID %d.\n", Id);
    }
}
void EliminarAuto()
{
    DatosAuto autos[20];
    int count = leerDatosAuto(autos);
    printf("Ingrese el ID del auto que desea eliminar:\n");
    int Id = leerIntegerRango(1000, 9999);
    int Posicion = EncontarAutoID(autos, Id);
    if (Posicion != -1)
    {
        printf("Esta seguro de que desea eliminar el auto con ID %d? 1.Si 2.No\n", Id);
        int opcion = leerIntegerRango(1, 2);
        if (opcion == 1)
        {
            autos[Posicion].Activo = 0;
            GuardarAutoEnPosicion(autos, Posicion);
            printf("Auto con ID %d eliminado exitosamente.\n", Id);
        }
        else
        {
            printf("Eliminación cancelada.\n");
        }
    }
    else
    {
        printf("No se encontro un auto con el ID %d.\n", Id);
    }
}
// ARCHIVOS BINARIOS
void GuardarDatosAuto(DatosAuto *autos)
{
    FILE *f;
    f = fopen("autos.dat", "ab+");
    if (f == NULL)
    {
        printf("No se puede abrir el archivo\n");
        return;
    }
    fwrite(autos, sizeof(DatosAuto), 1, f);
    fclose(f);
}
int leerDatosAuto(DatosAuto *autos)
{
    FILE *f;
    f = fopen("autos.dat", "rb");
    if (f == NULL)
    {
        f = fopen("autos.dat", "ab+");
        if (f != NULL)
            fclose(f);
        return 0;
    }
    int count = fread(autos, sizeof(DatosAuto), 10, f);
    fclose(f);
    return count;
}

void GuardarAutoEnPosicion(DatosAuto *autos, int posicion)
{
    FILE *f = fopen("autos.dat", "r+b");
    if (f == NULL)
    {
        printf("No se puede abrir el archivo.\n");
        return;
    }
    fseek(f, posicion * sizeof(DatosAuto), SEEK_SET);
    fwrite(&autos[posicion], sizeof(DatosAuto), 1, f);
    fclose(f);
}

int EncontarAutoID(DatosAuto *autos, int Id)
{
    int posicion = 0, flag = 0;
    FILE *f = fopen("autos.dat", "rb");
    if (f == NULL)
    {
        printf("Error al abrir el archivo\n");
    }
    else
    {
        while (fread(autos, sizeof(DatosAuto), 1, f))
        {
            if (autos->id == Id && autos->Activo == 1)
            {
                posicion = (ftell(f) / sizeof(DatosAuto)) - 1;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            posicion = -1;
        }
    }
    return posicion;
}

void BorrarSaltolinea(char *a)
{
    int len = strlen(a);
    if (len > 0 && a[len - 1] == '\n')
    {                      // se asegura de que la cadena no este vacia y de que el ultimo caracter si sea un salto de linea
        a[len - 1] = '\0'; // De haber un salto de linea, lo cambia por el valor nulo
    }
}

#include <stdio.h>
#include "funciones.h"

int main() 
{
int opc1,opc2;
do{
    printf("Gestion de Autos\n");
    printf("1. Ingresar nuevo auto\n");
    printf("2. Mostrar autos\n");
    printf("3. Hacer compra\n");
    printf("4. Buscar autos por criterio\n");
    printf("5. Salir\n");
    opc1=leerIntegerRango(1,5);
    switch (opc1)
    {
    case 1:
        LeerDatosAuto();
        break;
    case 2:
        mostrarDatosAuto();
        break;
    case 3:
        HacerCompra();
        break;
    case 4:
        break;
    case 5:
        printf("Saliendo del programa...\n");
        break;
    default:
        printf("Desea realizar otra operacion? 1.Si 2.No\n");
        opc2=leerIntegerRango(1,2);
        break;

    }

    if(opc1!=5){
        printf("Desea realizar otra operacion? 1.Si 2.No\n");
        opc2=leerIntegerRango(1,2);
    }

}while(opc2!=2 && opc1!=5);

return 0;
}
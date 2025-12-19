typedef struct{
char Nombre[50];
int id;
}DatosCliente;


typedef struct{
int id;
char Marca[50];
int Anio;
float Precio;
char Color[20];
char Estado[15];
char modelo[50];
int Activo;
int Disponible;
DatosCliente cliente;
}DatosAuto;

int leerIntegerRango(int inicio, int fin);
float leerFlotanteRango(float inicio, float fin);
void validarID(int *id);
void LeerDatosAuto();
void mostrarDatosAuto();
void GuardarDatosAuto(DatosAuto *autos);
int leerDatosAuto(DatosAuto *autos);
void BorrarSaltolinea(char *a);
void HacerCompra();
int EncontarAutoID(DatosAuto *autos, int Id);
void GuardarAutoEnPosicion(DatosAuto *autos, int posicion);
void EliminarAuto();

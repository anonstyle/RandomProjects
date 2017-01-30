/**
 *	@name		ExamenA2017.cpp
 *	@author		Ivan Ceballos Vega
 *	@date		30-01-2017
 *	@version	1.0
 */


#include <iostream>
#include <string>
#include <fstream>	
#include <cmath>	// Libreria para el uso de abs.
#include <iomanip>	// Libreria para el uso de setw.

using namespace std;

// Defincion de constantes
const int MAX_APUNTES = 500;

// Defincion de nuevos tipos
typedef struct {
	int dia;
	int mes;
	int anyo;
} tFecha;

typedef struct {
	tFecha fecha;
	float importe;
	string concepto;	
} tApunte;

typedef tApunte tCuenta[MAX_APUNTES];

// Inclusion de prototipos

/**
 *	Carga el documento en la fila.
 *
 *	@param	cuenta 		 	Array donde se guardan los datos.
 *	@param	numElementos 	Numero de elementos que contiene el array.
 *	@param	archivoElegido	Nombre del archivo donde estan almacenados los datos.
 *
 */
void cargar(tCuenta cuenta, int& numElementos, string archivoElegido);

/**
 *	Extrae la primera nomina.
 *
 *	@param	cuenta 		 	Array donde estan almacenados los datos.
 *	@param	numElementos	Numero de elementos que contiene el array.
 *	@return	nomina			Inreso en concepto de salarios.
 *
 */
float nomina(const tCuenta cuenta, int numElementos);

/**
 *	Calcula la media de gasto en concepto de luz de un anyo dado.
 *
 *	@param	cuenta 		 	Array donde se guardan los datos.
 *	@param	anyo			Anyo donde se quieren buscar los datos.
 *	@param	numElementos 	Numero de elementos que contiene el array.
 *	@return	sumaLuz			Media de gasto en luz del anyo dado.
 *
 */
float gastoLuz(const tCuenta cuenta, int anyo, int numElementos);

/**
 *	Muestra la cuenta por pantalla.
 *
 *	@param	cuenta 		 	Array donde se guardan los datos.
 *	@param	numElementos 	Numero de elementos que contiene el array.
 *
 */
void mostrarCuenta(const tCuenta cuenta, int numElementos);

/**
 *	Muestra el menu por pantalla.
 *
 *	@return	opcionEscogida	Opcion escogida por el usuario.
 *
 */
int menu();

// *** MAIN *** //
int main (){
	int opcionEscogida, numElementos, anyo;
	string nombreFichero;
	tCuenta cuenta;
	
	do {
		opcionEscogida = menu();
		
		switch(opcionEscogida){
			case 1:{
				cout << "Indique el nombre del fichero que desea cargar: ";
				cin >> nombreFichero;
				cargar(cuenta, numElementos, nombreFichero);
				break;
			}
			case 2:{
				cout << "El importe de la nomina es de " << nomina(cuenta, numElementos) << endl;
				break;
			}
			case 3:{
				cout << "Indique el anyo del que quiere saber el gasto medio de luz: ";
				cin >> anyo;
				cout << "El gasto medio en luz fue de " << gastoLuz(cuenta, anyo, numElementos) << endl;
				break;
			}
			case 4:{
				mostrarCuenta(cuenta, numElementos);
			}
			default: break;
		}
	} while(opcionEscogida != 0);
	
	return 0;
}

// Definicion de subprogramas

void cargar(tCuenta cuenta, int& numElementos, string archivoElegido){
	ifstream lectura;
	int dia;
	numElementos = 0;	
	
	lectura.open(archivoElegido.c_str());
	
	if (!lectura.is_open())
		cout << "El archivo no pudo ser abierto." << endl;
	else {
		lectura >> dia;
		while (dia != -1 && numElementos < MAX_APUNTES){
			cuenta[numElementos].fecha.dia = dia;
			lectura >> cuenta[numElementos].fecha.mes;
			lectura >> cuenta[numElementos].fecha.anyo;
			lectura >> cuenta[numElementos].importe;
			lectura >> cuenta[numElementos].concepto;
			numElementos++;
			lectura >> dia;
		}
		cout << "Se ha realizado la carga de los datos con exito" << endl;
	}
}

float nomina(const tCuenta cuenta, int numElementos){
	float nomina = 0; // Inicializamos nomina a 0 por si no encuentra ningun dato.
	int i = 0;	
	bool encontrado = false;
	
	while (i < numElementos && !encontrado){
		if (cuenta[i].concepto == "Salario"){
			encontrado = true;
			nomina = cuenta[i].importe;
		} else
			i++;
	}
	
	return nomina;
}

float gastoLuz(const tCuenta cuenta, int anyo, int numElementos){
	float sumaLuz = 0;
	int denominador = 0;
	
	for (int i = 0; i < numElementos; i++){
		if (cuenta[i].fecha.anyo == anyo && cuenta[i].concepto == "Luz"){
			sumaLuz = sumaLuz + cuenta[i].importe;
			denominador++;
		}
	}
	sumaLuz = abs(sumaLuz / denominador);
	return sumaLuz;
}

void mostrarCuenta(const tCuenta cuenta, int numElementos){
	
	for (int i = 0; i < numElementos; i++){
		cout << setw(2) << 	cuenta[i].fecha.dia  << " " << 
				setw(2) <<	cuenta[i].fecha.mes  << " " << 
				setw(2) << 	cuenta[i].fecha.anyo << " " << 
				setw(8) << 	cuenta[i].importe 	 << " " << 
							cuenta[i].concepto 	 << endl;
	}
}

int menu(){
	int opcionEscogida;
	
	do{
		cout << "Opciones disponibles: " << endl;
		cout << "  1 - Cargar cuenta de fichero." << endl;
		cout << "  2 - Importe de la ultima nomina." << endl;
		cout << "  3 - Gasto medio de luz de un anyo." << endl;
		cout << "  4 - Mostrar por pantalla." << endl;
		cout << "  0 - Salir." << endl;
		cout << "Indique la opcion elegida: ";
		cin >> opcionEscogida;
	} while (opcionEscogida < 0 || opcionEscogida > 4);
	
	return opcionEscogida;
}
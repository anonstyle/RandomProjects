/**
 *
 *	@name	ejercicio55.cpp
 *	@author	Ivan Ceballos Vega
 *	@date	12-1-2017
 *
 */
 
 #include <iostream>
 #include <iomanip>
 #include <fstream>
 #include <string>
 
 using namespace std;
 
 // Definicion de constantes
 const int MAXDIAS = 7;
 
 // Creacion de tipos
 typedef double tVentas[MAXDIAS];
 
 // Inclusion de prototipos
 
/*
 *	Muestra el menu
 * 
 * name: 	menu
 * @param	
 * @return	eleccionUsuario: valor que ha elegido el usuario como opcion a ejecutar.
 * 
 */
 int menu();
 
/*
 * Decuelve la mayor venta del array.
 * 
 * name: 	mayorVenta
 * @param	ventas: 	array donde se almacenan los datos.
 * @return	mayorVenta: es el mayor valor dentro del array.
 * 			dia: 		es la posicion dentro del array.
 * 
 */
 void mayorVenta(const tVentas ventas, double& mayorVenta, int& dia);
 
/*
 * Permite modificar un valor del array teniendo en cuenta su posicion.
 * 
 * name: 	actualizarVentas
 * @param	venta: 	valor que se quiere modificar.
 * 			dia:	posicion donde se quiere introducir.
 * @return	ventas: array donde se encuentran los datos.
 */
 void actualizarVentas(tVentas ventas, int venta, int dia);
 
/*
 * Muesta el array en pantalla.
 * 
 * name: 	visualizarVentas
 * @param	ventas:	array donde estan almacenados los valores.
 * 
 */
 void visualizarVentas(const tVentas ventas);
 
/*
 * Permite calcular el total del array.
 * 
 * name: 	ingresosTotales
 * @param	ventas:	lugar donde estan almacenados los valores.
 * @return	total:	total del sumatorio del array.
 * 	
 */
 double ingresosTotales(const tVentas ventas);
 
/*
 * Permite cargar datos al array a partir de un archivo.
 * 
 * name: 	cargarDeArchivo
 * @param	ventas: array que tiene almacenados los valores.
 * 
 */
 void cargarDeArchivo(tVentas ventas);
 
/*
 * Permite guardar los datos del array en un archivo.
 * 
 * name: 	guardarArchivo
 * @param	ventas:lugar donde estan almacenados los archivos.
 * 
 */
 void guardarArchivo(const tVentas ventas);
 
/*
 * Permite buscar un valor en el array situado entre un intervalo.
 * 
 * name: 	ventaEnIntervalo
 * @param	ventas: lugar donde estan los valores.
 * 			num1:	limite inferior del intervalo.
 * 			num2:	limite superior del intervalo.
 * @return	posicion:	devuelve la posicion del primer numero que cumple que num1 <= x <= num2. Si no la encuentra devuelve -1.	
 * 
 */
 int ventaEnIntervalo(const tVentas ventas, int num1, int num2);
 
/*
 * Permite tener el dia en string en vez de int.
 * 
 * name: 	diaSemana
 * @param	dia:		en formato entero.
 * @return	diaSemana:	en formato string.
 * 
 */
 string diaSemana(int dia);
 
 // *** MAIN *** //
 int main(){
	int opcionUsuario, dia, limSup, limInf;
	tVentas ventasSemana;
	double mayorValor, cantidad;
	
	cargarDeArchivo(ventasSemana);
	
	do {
		opcionUsuario = menu();
		
		switch(opcionUsuario){
			case 1: {
				mayorVenta(ventasSemana, mayorValor, dia);
				cout << "El mayor valor se localiza el dia en la posicion " << dia << " que corresponde a " << diaSemana(dia) << " con un valor de " << mayorValor << "." << endl;
				break;
			}
			case 2: {
				do{
					cout << "Indique el dia que quiere modificar: ";
					cin >> dia;
				} while (dia < 1 || dia > 7);
				
				do {
					cout << "Indique la cantidad: ";
					cin >> cantidad;
				} while (cantidad < 0);
				
				actualizarVentas(ventasSemana, cantidad, dia);
				break;
			}
			case 3: visualizarVentas(ventasSemana); break;
			case 4: cout << "El ingreso total es de " << ingresosTotales(ventasSemana) << " euros." << endl; break;
			case 5:	guardarArchivo(ventasSemana); break;
			case 6: {
				cout << "Indique el limite inferior: ";
				cin >> limInf;
				cout << "Indique el limite superior: ";
				cin >> limSup;
				
				dia = ventaEnIntervalo(ventasSemana, limInf, limSup);
				
				if (dia == -1)	cout << "No se ha encontrado valor mayor que " << limInf << " y menor que " << limSup << "." << endl;
				else cout << "Se ha encontrado un resultado en la posicion " << dia << " que corresponde al dia " << diaSemana(dia) << "." << endl;
			}
		}
		
	} while (opcionUsuario != 0);
	return 0; 
}

// Definicion de funciones.

int menu(){
	int eleccionUsuario;
	
	do {
		cout << "Seleccione la opcion deseada de las siguientes: " << endl;
		cout << "	0. 	Salir." << endl;
		cout << "  	1.	Localizar la mayor venta de la semana." << endl;
		cout << "  	2.	Actualizar la venta de un dia." << endl;
		cout << "	3. 	Visualizar todas las ventas." << endl;
		cout << "	4.	Calcular el total de ingresos." << endl;
		cout << "	5.	Guardar las ventas en un fichero." << endl;
		cout << "	6. 	Localizar la primera venta localizada en un intervalo." << endl;
		cout << "Indique la opcion deseada: ";
		cin >> eleccionUsuario;
	} while (eleccionUsuario < 0 || eleccionUsuario > 6);
	
	return eleccionUsuario;
}

void mayorVenta(const tVentas ventas, double& mayorVenta, int& dia){
	// Devuelve la mayor venta producida en el array y su posicion.
	
	dia = 0;
	mayorVenta = ventas[dia];
	
	for (int i = 0; i < MAXDIAS; i++){
		if (ventas[i] > mayorVenta) {
			mayorVenta = ventas[i];
			dia = i;
		}
	}
}

void actualizarVentas(tVentas ventas, int venta, int dia){
	// Permite modificar uno de los elementos del array.
	int posicion;
	
	posicion = dia - 1;
	ventas[posicion] = venta;
}

void visualizarVentas(const tVentas ventas){
	// Muestra las ventas por pantalla.
	
	for (int i = 0; i < MAXDIAS; i++){
		cout << diaSemana(i) << ": " << ventas[i] << "." << endl;
	}
}

double ingresosTotales(const tVentas ventas){
	// Calcula el total de ingresos del array.
	double total = 0;
	
	for (int i = 0; i < MAXDIAS; i++){
		total = total + ventas[i];
	}
	
	return total;
}

void cargarDeArchivo(tVentas ventas){
	// Introduce datos a partir de un archivo.
	ifstream leer;
	string nombreArchivo;
	
	cout << "Indique el nombre del archivo de donde quiere cargar las ventas: ";
	cin >> nombreArchivo;
	
	leer.open(nombreArchivo.c_str());
	while (!leer.is_open()){
		cout << "Nombre de archivo no valido, introduzca otro: ";
		cin >> nombreArchivo;
		leer.open(nombreArchivo.c_str());
	}
	cout << "¡Archivo abierto con exito!" << endl;
	
	for (int i = 0; i < MAXDIAS; i++){
		leer >> ventas[i];
	}
	
	leer.close();
}

void guardarArchivo(const tVentas ventas){
	// Guarda los datos del array en un archivo.
	ofstream escribir;
	string nombreArchivo;
	
	cout << "Indique el nombre del archivo donde quiere guardar las ventas: ";
	cin >> nombreArchivo;
	
	escribir.open(nombreArchivo.c_str());
	while (!escribir.is_open()){
		cout << "Nombre de archivo no valido, introduzca otro: ";
		cin >> nombreArchivo;
		escribir.open(nombreArchivo.c_str());
	}
	
	cout << "¡Archivo abierto con exito!" << endl;
	for (int i = 0; i < MAXDIAS; i++){
		escribir << diaSemana(i) << ": " << ventas[i] << endl;
	}
	
	escribir.close();
}

int ventaEnIntervalo(const tVentas ventas, int num1, int num2){
	// Devuelve la primera venta que se encuentre entre num1 y num2, es decir num1 <= x <= num2.
	int posicion = 0;
	bool encontrado = false;
	
	while (posicion < MAXDIAS && !encontrado){
		if (ventas[posicion] >= num1){
			if (ventas[posicion] <= num2)	encontrado = true;
		} else posicion++;
	}
	
	if (!encontrado)	posicion = -1;
	
	return posicion;
}

string diaSemana(int dia){
	string diaSemana;
	
	switch(dia){
		case 0:	diaSemana = "Lunes"; 		break;
		case 1:	diaSemana = "Martes"; 		break;
		case 2:	diaSemana = "Miercoles"; 	break;
		case 3:	diaSemana = "Juves"; 		break;
		case 4:	diaSemana = "Viernes"; 		break;
		case 5:	diaSemana = "Sabado"; 		break;
		case 6:	diaSemana = "Domingo"; 		break;
		default: break;
	}
	
	return diaSemana;
}

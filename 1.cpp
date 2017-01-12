/**
* @author Ivan Ceballos Vega
* @version 1.0
* @date 2017
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Declaracion de constantes.
const int ELEMENTOSVECTOR = 2;
const float GRADOSARADIANES = 0.0175;

// Declaracion de nuevos tipos.
typedef double tVector[ELEMENTOSVECTOR];

// Implementacion de prototipos.
/**
 *	Suma las componentes de los vectores.
 *	
 *	@name	sumaVectores
 *	@param	vec1, vec2 son los dos vectores que se necesitan para producir la suma.
 *	@return	vectorResultado es el resultado de la suma de las componentes de vec1 y vec2.
 *	
 */
void sumaVectores(const tVector vec1, const tVector vec2, tVector vectorResultado);

/**
*	Resta las componentes de los vectores.
*
*	@name	restaVectores
*	@param	vec1, vec2 son los dos vectores que se necesitan para producir la resta.
*	@return	vectorResultado es el resultado de la resta de las componentes de vec1 y vec2.
*
*/
void restaVectores(const tVector vec1, const tVector vec2, tVector vectorResultado);

/**
*	Calcula el modulo del vector dado.
*
*	@name	moduloVector
*	@param	vector es el dato el cual operaremos.
*	@return	resultado: el resultado del modulo de vector.
*
*/
double moduloVector(const tVector vector);

/**
*	Calcula el producto escalar de dos vectores.
*
*	@name	productoEscalar
*	@param	vec1, vec2 son los dos vectores que se necesitan para calcular el producto escalar.
*	@return	resultado:	prroducto vectorial de vec1 y vec2.
*
*/
double productoEscalar(const tVector vec1, const tVector vec2, int grados);

/**
*	Calcula el vector normal de un vector dado.
*
*	@name	vectorNormal
*	@param	vector es el vector que se introduce para calcular su vector normal.
*	@return	vectorResultado es el vector normal de vector.
*
*/
void vectorNormal(const tVector vector, tVector vectorResultado);

/**
*	Calcula la mayor componente de un vector dado.
*
*	@name	mayorComponente
*	@param	vector: es el vector que se introduce del cual detectaremos su componente de mayor valor.
*	@return	mayor:	es la mayor componente de vector.
*
*/
double mayorComponente(const tVector vector);

/**
*	Muestra el menu.
*
*	@name	menu
*	@return	eleccionUsuario:	devuelve la opcion que ha escogido el usuario.
*
*/
int menu();

/**
*	Pide los datos.
*
*	@name	pedirDatos
*	@return	vector es el vector en el cual se escribiran los valores del vector.
*
*/
void pedirDatos(tVector vector);

/**
*	Escribe en pantalla el vector indicado.
*
*	@name	escribirDatos
*	@param	vector es el vector que se introduce para mostrar.
*			resultado es el elemento de una operacion.
*			esVector verifica si el resultado a mostrar es vector o numero;
*
*/
void escribirDatos(const tVector vector, double resultado, bool esVector);

/**
*	Ejecuta la opcion escogida.
*
*	@name	ejecutarOpcion
*	@param	opcionUsuario es la opcion que el usuario ha escogido.
*
*/
void ejecutarOpcion(int opcionUsuario);

// *** MAIN *** //
int main(){
	int eleccionUsuario;

	do{
		eleccionUsuario = menu();
		ejecutarOpcion(eleccionUsuario);
	} while (eleccionUsuario != 0);
	return 0;
}

// Definicion de funciones.
void sumaVectores(const tVector vec1, const tVector vec2, tVector vectorResultado){

	for (int i = 0; i < ELEMENTOSVECTOR; i++){
		vectorResultado[i] = vec1[i] + vec2[i];
	}

}

void restaVectores(const tVector vec1, const tVector vec2, tVector vectorResultado){
	
	for (int i = 0; i < ELEMENTOSVECTOR; i++){
		vectorResultado[i] = vec1[i] - vec2[i];
	}
}

double moduloVector(const tVector vector){
	double resultado = 0;

	for (int i = 0; i < ELEMENTOSVECTOR; i++){
		resultado = resultado + pow(vector[i], 2);
	}

	resultado = sqrt(resultado);

	return resultado;
}

double productoEscalar(const tVector vec1, const tVector vec2, int grados){
	double mod1, mod2, resultado, radianes;

	mod1 = moduloVector(vec1);
	mod2 = moduloVector(vec2);

	radianes = grados * GRADOSARADIANES;

	resultado = mod1 + mod2 + cos(radianes);

	return resultado;
}

void vectorNormal(const tVector vector, tVector vectorResultado){
	double modulo;

	modulo = moduloVector(vector);

	for (int i = 0; i < ELEMENTOSVECTOR; i++){
		vectorResultado[i] = vector[i] / modulo;
	}
}

double mayorComponente(const tVector vector){
	double mayor;

	mayor = vector[0];	// Inicializa el valor de mayor al primer elemento del vector.

	for (int i = 1; i < ELEMENTOSVECTOR; i++){
		if (vector[i] > mayor)	mayor = vector[i];
	}

	return mayor;
}

int menu(){
	int eleccionUsuario;

	do {
		cout << "Indique la opcion que desea de las siguientes:" << endl;
		cout << "  0. Salir." << endl;
		cout << "  1. Suma de vectores." << endl;
		cout << "  2. Resta de vectores." << endl;
		cout << "  3. Modulo de un vector." << endl;
		cout << "  4. Producto escalar de 2 vectores." << endl;
		cout << "  5. Normalizacion de un vector." << endl;
		cout << "  6. Obtencion de la componente de mayor valor." << endl;
		cout << "Indique la opcion seleccionada: ";	cin >> eleccionUsuario;
	} while (eleccionUsuario < 0 || eleccionUsuario > 7);

	return eleccionUsuario;
}

void pedirDatos(tVector vector){

	for (int i = 0; i < ELEMENTOSVECTOR; i++){
		cout << "Introduca la componente " << i + 1 << " del vector: ";	cin >> vector[i];
	}

}

void escribirDatos(const tVector vector, double resultado, bool esVector){

	if (esVector){
		cout << "El vector es el siguiente: (";
		for (int i = 0; i < ELEMENTOSVECTOR; i++){
			cout << vector[i];
			if (i != ELEMENTOSVECTOR - 1)	cout << ", ";
		}
		cout << ")." << endl;
	}
	else {
		cout << "El resultado es el siguiente: " << resultado << "." << endl;
	}
}

void ejecutarOpcion(int opcionUsuario){
	int grados;
	tVector vector1, vector2, resultado;
	double resultadoDouble;

	switch (opcionUsuario){
	case 1:	{
		pedirDatos(vector1);
		pedirDatos(vector2);
		sumaVectores(vector1, vector2, resultado);
		escribirDatos(resultado, resultadoDouble, true);
		break;
	}
	case 2:{
		pedirDatos(vector1);
		pedirDatos(vector2);
		restaVectores(vector1, vector2, resultado);
		escribirDatos(resultado, resultadoDouble, true);
		break;
	}
	case 3:{
		pedirDatos(vector1);
		resultadoDouble = moduloVector(vector1);
		escribirDatos(resultado, resultadoDouble, false);
		break;
	}
	case 4:{
		pedirDatos(vector1);
		pedirDatos(vector2);
		cout << "Introduzca los grados entre esos dos vectores: ";	cin >> grados;
		resultadoDouble = productoEscalar(vector1, vector2, grados);
		escribirDatos(resultado, resultadoDouble, false);
		break;
	}
	case 5:{
		pedirDatos(vector1);
		vectorNormal(vector1, resultado);
		escribirDatos(resultado, resultadoDouble, true);
		break;
	}
	case 6:{
		pedirDatos(vector1);
		resultadoDouble = mayorComponente(vector1);
		escribirDatos(resultado, resultadoDouble, false);
		break;
	}
	default: break;
	}

}

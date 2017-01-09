/*
* Practica realizada por:
*
* Arturo Barbero Pérez
* Raúl Sesé Vega
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <locale>

using namespace std;
const int MAX_PROD = 25;
const int PROD_NULO = 0;
const int CENTINELA = -1;

typedef int tArray[MAX_PROD];

/*----------------/ qué hace la función, qué parámetros recibe y qué devuelve \-------------------------*/

/*Esta función muestra las distintas opciones, valida la opción elegida y devuelve dicha opción.*/
int menu();

/*Dada la opción escogida en el menú, la ejecuta.*/
void ejecutarOpc(int opc, tArray fila, int & tam);

/*Pide al usuario el nombre del fichero donde cargará la fila. Si el fichero existe la carga y la muestra. Si no, la fila se inicializa como vacía.*/
void ejecutarLeerFichero(tArray fila, int & tam);

/*Dado un fichero y un array, carga en él los números que contiene el fichero. Además pasa por referencia el número de cifras cargadas.*/
void leerFilaFich(istream &fich, tArray fila, int &tam);

/*Dado el array con los números ya cargados en él, los muestra en pantalla.*/
void mostrarFila(const tArray fila, int tam);

/*Dado el array con el tamaño de este, pide al usuario el nombre del fichero donde guardará la fila y si logra abrirlo,
guarda en el fichero la fila.*/
void ejecutarGuardarFichero(const tArray fila, int tam);

/*Dado el fichero, el array y el tamaño de este, guarda en dicho fichero el contenido de la fila.*/
void escribirFilaFich(ostream &fich, const tArray fila, int tam);

/*Dado el array y el tamaño de este; pide al usuario la posición que quiere levantar y la que posición donde quiere soltarlo.
Si es posible realiza el movimiento y si no lo es informa al usuario de ello.*/
void ejecutarGrua(tArray fila, int tam);

/*Dado un array, el tamaño de este, y las dos posiciones; comprueba si es posible realizar ese movimiento con las posiciones dadas. Devuelve un
booleano para ello.*/
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar);

/*Dado el tamaño del array y una posición cualquiera; verifica si la posición es válida en el array de tamaño tam. Para ello devuelve un booleano.*/
bool esPosValida(int tam, int pos);

/*Dado un array y una posición cualquiera; comprueba si esa posición está vacía. Para ello devuelve un booleano.*/
bool estaVacia(const tArray fila, int pos);

/*Dado un array, el tamaño, y dos posiciones; realiza el movimiento de la grúa entre esas dos posiciones. Devuelve un booleano si se ha realizado
con éxito el movimiento.*/
bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar);

/*Dado un array y su tamaño; pregunta al usuario desde qué posición empujará la excavadora y si es posible, ejecuta el movimiento.*/
void ejecutarExcavadora(tArray fila, int tam);

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);

/*-----/ VERSIÓN 2 \------*/
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);

bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar);

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar);



int main(){

	setlocale(LC_ALL, "spanish");
	system("chcp 1252");
	cout << endl << endl;

	tArray fila;
	int tamanioArray, opcionElegida;

	opcionElegida = menu();

	while (opcionElegida != 0){
		ejecutarOpc(opcionElegida, fila, tamanioArray);

		system("pause");
		system("cls");
		cout << endl << endl;
		opcionElegida = menu();
	}

	cout << "\nHasta la próxima" << endl << endl;
	system("pause");
	return 0;
}

int menu(){

	int opcion;

	cout << " 1.- Cargar fila de fichero" << endl;
	cout << " 2.- Guardar fila en fichero" << endl;
	cout << " 3.- Usar grúa" << endl;
	cout << " 4.- Usar excavadora" << endl;
	cout << " 0.- Salir" << endl << endl << "\t";
	cout << "Opción: ";
	cin >> opcion;

	while (opcion < 0 || opcion > 4 || cin.fail()){
		cin.clear(); cin.sync();
		cout << "\n¡Opción no válida!" << endl << endl << "\t";
		cout << "Opción: ";
		cin >> opcion;
	}
	cin.sync();

	return opcion;
}

void ejecutarOpc(int opc, tArray fila, int & tam){

	switch (opc){
	case 1: ejecutarLeerFichero(fila, tam); break;
	case 2: ejecutarGuardarFichero(fila, tam); break;
	case 3: cout << endl; mostrarFila(fila, tam); ejecutarGrua(fila, tam); break;
	case 4: cout << endl; mostrarFila(fila, tam); ejecutarExcavadora(fila, tam); break;
	}
}

void ejecutarLeerFichero(tArray fila, int & tam){
	string nombreFich;
	ifstream archivo;

	cout << "\nIntroduzca el nombre del fichero con extensión '.txt' de donde quiere cargar la fila: ";
	getline(cin, nombreFich);
	cout << endl;

	archivo.open(nombreFich);

	if (archivo.is_open()){
		leerFilaFich(archivo, fila, tam);
		cout << "\nSe ha cargado con éxito la fila." << endl << endl;
		mostrarFila(fila, tam);
	}
	else {
		cout << "No se ha podido abrir." << endl;
		tam = 0; // Se inicializa la fila como vacía, es decir, con tamaño 0.
	}
	archivo.close();
}

void leerFilaFich(istream &fich, tArray fila, int &tam){
	int i = 0;
	fich >> fila[i];
	while ((fila[i] != CENTINELA) && (i < MAX_PROD)){
		i++;
		fich >> fila[i];
	}
	tam = i; //	Incluye la posición del centinela
}

void mostrarFila(const tArray fila, int tam){

	int i = 0;

	if (tam > 0){

		//------------------------- Fila de arriba
		while (i < tam){
			if (fila[i] == PROD_NULO){
				cout << "|" << setw(2) << " ";
				i++;
			}
			else{
				cout << "|" << setw(2) << fila[i];
				i++;
			}
		}
		cout << "|" << endl;
		//------------------------ Fila del medio
		i = 0;
		while (i < tam){
			cout << "---";
			i++;
		}
		cout << "-" << endl;
		//------------------------ Fila de abajo
		i = 0;
		while (i < tam){
			cout << "|" << setw(2) << i;
			i++;
		}
		cout << "|" << endl << endl;
	}
	else cout << "La fila está vacía." << endl << endl;
}

void ejecutarGuardarFichero(const tArray fila, int tam){

	string nombreFich;
	ofstream archivo;

	cout << "\nIntroduzca el nombre del fichero con extensión '.txt' donde quiere guardar la fila: ";
	getline(cin, nombreFich);
	cout << endl;

	archivo.open(nombreFich);

	if (archivo.is_open()){
		escribirFilaFich(archivo, fila, tam);
		cout << "\nSe ha guardado con éxito la fila." << endl << endl;
		mostrarFila(fila, tam);
	}
	else {
		cout << "\nNo se ha podido guardar correctamente." << endl;
	}
	archivo.close();
}

void escribirFilaFich(ostream &fich, const tArray fila, int tam){

	int i = 0;
	fich << fila[i];
	while ((fila[i] != CENTINELA) && (i < tam)){
		i++;
		fich << " " << fila[i];
	}
}

void ejecutarGrua(tArray fila, int tam){
	int inicial, final, soltar;

	cout << "\nIntroduce la posición inicial del segmento a levantar: ";
	cin >> inicial;
	cout << endl;
	cout << "\nIntroduce la posición final del segmento a levantar: ";
	cin >> final;
	cout << endl;
	cout << "\nIntroduce la posición de inicio donde deseas soltar el segmento: ";
	cin >> soltar;
	cout << endl;

	if ((sonPosicionesPosiblesGrua(tam, inicial, final, soltar)) && (esPosibleGrua(fila, tam, inicial, final, soltar))){

		if (grua(fila, tam, inicial, final, soltar)) cout << "El movimiento se ha realizado con éxito." << endl << endl;
	}
	else cout << "No es posible realizar ese movimiento." << endl << endl;

	mostrarFila(fila, tam);

}
//SUPONGO que esta función cambia en la versión 2. Porque sino se mantienen las funciones de mover una posición solo y no tiene mucho sentido

bool esPosValida(int tam, int pos){
	bool valida = false;

	if ((pos >= 0) && (pos < tam)) valida = true;

	return valida;
}

bool estaVacia(const tArray fila, int pos){
	bool vacia = false;

	if (fila[pos] == 0) vacia = true;

	return vacia;
}

bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar){
	bool posible = false;

	if ((esPosValida(tam, posIni)) && (esPosValida(tam, posSoltar)) && (estaVacia(fila, posSoltar))) posible = true;

	return posible;
}
//Esta función no se si es que ya no se usa con la versión 2, o hay que utilizarla de alguna manera y no veo cómo o no sé.

bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar){
	bool movRealizado = false;

	fila[posSoltar] = fila[posIni];
	fila[posIni] = 0;
	movRealizado = true;

	return movRealizado;
}
//Y con esta función pasa lo mismo

void ejecutarExcavadora(tArray fila, int tam){
	int posicion, direccion;

	cout << "\nIntroduce la posición desde la que empujará la excavadora: ";
	cin >> posicion;

	cout << "\nIntroduce la dirección que quiere (1. Derecha, -1. Izquierda): ";
	cin >> direccion;

	if (!esPosValida(tam, posicion)) cout << "\nNo es posible realizar ese movimiento." << endl << endl;  /* Si esPosValida es false, es decir, si la
																										  posicion no existe.*/
	else{
		if (excavadora1Dir(fila, tam, posicion, direccion)) cout << "\nEl desplazamiento ha sido realizado." << endl << endl;
	}

	mostrarFila(fila, tam);
}

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion){
	/*Direccion puede ser 1 (derecha) o -1 (izquierda)*/

	int posicionHueco;
	bool encontrado = false;

	while ((posIni >= PROD_NULO) && (posIni < tam) && !encontrado){

		if (estaVacia(fila, posIni)){
			posicionHueco = posIni;
			encontrado = true;
		}
		else posIni = posIni + direccion; //Si la direccion es 1 se va hacia la derecha, si es -1 se va hacia la izquierda
	}
	if (!encontrado) posicionHueco = posIni;

	return posicionHueco;
}

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion){

	bool realizado = false;

	for (int i = posHuecoLibreDir(fila, tam, posIni, direccion); i != posIni; i = i - direccion){

		if (estaVacia(fila, i)){		  /*Se pone esto porque sino puede desplazarlo todo hacia la pared y que desaparezcan numeros.*/

			fila[i] = fila[i - direccion];
			fila[i - direccion] = 0;
		}
	}
	realizado = true;

	return realizado;
}

/*----------------/ VERSION 2 \ ---------------*/

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar){

	bool esPosible = false, posiciones = false, extremos = true;

	if (posFin < posIni) extremos = false;

	if (esPosValida(tam, posIni) && esPosValida(tam, posFin) && esPosValida(tam, posSoltar) && esPosValida(tam, tam - 1)) posiciones = true;
	// Se pone tam-1 en la ultima condición porque tam incluía el centinela

	if (extremos && posiciones) esPosible = true;

	return esPosible;
}

bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar){

	bool esPosible = true;
	int i = posIni, j = posSoltar;
	int longSegmento = (posFin + 1) - posIni;

	if (j < tam - longSegmento){
		while ((i <= posFin) && (i < tam) && (j < tam)){
			if ((fila[i] != PROD_NULO) && (fila[j] != PROD_NULO) && (j > i + longSegmento) && (j < i - longSegmento)) esPosible = false;	/*Esto falla porque si se utiliza la grua para mover todo
																						un sitio a la derecha, detecta como si no se pudiese y no lo mueve.
																						Cuando si se tendría que poder según lo que pide la practica*/
			else i++; j++;

		}
	}
	else esPosible = false;

	return esPosible;
}

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar){

	bool grua = false;

	tArray arrayAuxiliar;
	int j = 0, s = posSoltar, i = posIni;

	while ((i < tam) && (i <= posFin)){

		if (fila[i] != 0){ // Evita que guarde un 0 y que lo sustituya por un numero que haya antes colocado.
			arrayAuxiliar[j] = fila[i];
			fila[i] = PROD_NULO;
			fila[s] = arrayAuxiliar[j];
		}
		i++; j++; s++;
		grua = true;
	}

	return grua;
}
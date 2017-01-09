/*
* Practica realizada por:
*
* Arturo Barbero P�rez
* Ra�l Ses� Vega
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

/*----------------/ qu� hace la funci�n, qu� par�metros recibe y qu� devuelve \-------------------------*/

/*Esta funci�n muestra las distintas opciones, valida la opci�n elegida y devuelve dicha opci�n.*/
int menu();

/*Dada la opci�n escogida en el men�, la ejecuta.*/
void ejecutarOpc(int opc, tArray fila, int & tam);

/*Pide al usuario el nombre del fichero donde cargar� la fila. Si el fichero existe la carga y la muestra. Si no, la fila se inicializa como vac�a.*/
void ejecutarLeerFichero(tArray fila, int & tam);

/*Dado un fichero y un array, carga en �l los n�meros que contiene el fichero. Adem�s pasa por referencia el n�mero de cifras cargadas.*/
void leerFilaFich(istream &fich, tArray fila, int &tam);

/*Dado el array con los n�meros ya cargados en �l, los muestra en pantalla.*/
void mostrarFila(const tArray fila, int tam);

/*Dado el array con el tama�o de este, pide al usuario el nombre del fichero donde guardar� la fila y si logra abrirlo,
guarda en el fichero la fila.*/
void ejecutarGuardarFichero(const tArray fila, int tam);

/*Dado el fichero, el array y el tama�o de este, guarda en dicho fichero el contenido de la fila.*/
void escribirFilaFich(ostream &fich, const tArray fila, int tam);

/*Dado el array y el tama�o de este; pide al usuario la posici�n que quiere levantar y la que posici�n donde quiere soltarlo.
Si es posible realiza el movimiento y si no lo es informa al usuario de ello.*/
void ejecutarGrua(tArray fila, int tam);

/*Dado un array, el tama�o de este, y las dos posiciones; comprueba si es posible realizar ese movimiento con las posiciones dadas. Devuelve un
booleano para ello.*/
bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar);

/*Dado el tama�o del array y una posici�n cualquiera; verifica si la posici�n es v�lida en el array de tama�o tam. Para ello devuelve un booleano.*/
bool esPosValida(int tam, int pos);

/*Dado un array y una posici�n cualquiera; comprueba si esa posici�n est� vac�a. Para ello devuelve un booleano.*/
bool estaVacia(const tArray fila, int pos);

/*Dado un array, el tama�o, y dos posiciones; realiza el movimiento de la gr�a entre esas dos posiciones. Devuelve un booleano si se ha realizado
con �xito el movimiento.*/
bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar);

/*Dado un array y su tama�o; pregunta al usuario desde qu� posici�n empujar� la excavadora y si es posible, ejecuta el movimiento.*/
void ejecutarExcavadora(tArray fila, int tam);

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);

/*-----/ VERSI�N 2 \------*/
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

	cout << "\nHasta la pr�xima" << endl << endl;
	system("pause");
	return 0;
}

int menu(){

	int opcion;

	cout << " 1.- Cargar fila de fichero" << endl;
	cout << " 2.- Guardar fila en fichero" << endl;
	cout << " 3.- Usar gr�a" << endl;
	cout << " 4.- Usar excavadora" << endl;
	cout << " 0.- Salir" << endl << endl << "\t";
	cout << "Opci�n: ";
	cin >> opcion;

	while (opcion < 0 || opcion > 4 || cin.fail()){
		cin.clear(); cin.sync();
		cout << "\n�Opci�n no v�lida!" << endl << endl << "\t";
		cout << "Opci�n: ";
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

	cout << "\nIntroduzca el nombre del fichero con extensi�n '.txt' de donde quiere cargar la fila: ";
	getline(cin, nombreFich);
	cout << endl;

	archivo.open(nombreFich);

	if (archivo.is_open()){
		leerFilaFich(archivo, fila, tam);
		cout << "\nSe ha cargado con �xito la fila." << endl << endl;
		mostrarFila(fila, tam);
	}
	else {
		cout << "No se ha podido abrir." << endl;
		tam = 0; // Se inicializa la fila como vac�a, es decir, con tama�o 0.
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
	tam = i; //	Incluye la posici�n del centinela
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
	else cout << "La fila est� vac�a." << endl << endl;
}

void ejecutarGuardarFichero(const tArray fila, int tam){

	string nombreFich;
	ofstream archivo;

	cout << "\nIntroduzca el nombre del fichero con extensi�n '.txt' donde quiere guardar la fila: ";
	getline(cin, nombreFich);
	cout << endl;

	archivo.open(nombreFich);

	if (archivo.is_open()){
		escribirFilaFich(archivo, fila, tam);
		cout << "\nSe ha guardado con �xito la fila." << endl << endl;
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

	cout << "\nIntroduce la posici�n inicial del segmento a levantar: ";
	cin >> inicial;
	cout << endl;
	cout << "\nIntroduce la posici�n final del segmento a levantar: ";
	cin >> final;
	cout << endl;
	cout << "\nIntroduce la posici�n de inicio donde deseas soltar el segmento: ";
	cin >> soltar;
	cout << endl;

	if ((sonPosicionesPosiblesGrua(tam, inicial, final, soltar)) && (esPosibleGrua(fila, tam, inicial, final, soltar))){

		if (grua(fila, tam, inicial, final, soltar)) cout << "El movimiento se ha realizado con �xito." << endl << endl;
	}
	else cout << "No es posible realizar ese movimiento." << endl << endl;

	mostrarFila(fila, tam);

}
//SUPONGO que esta funci�n cambia en la versi�n 2. Porque sino se mantienen las funciones de mover una posici�n solo y no tiene mucho sentido

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
//Esta funci�n no se si es que ya no se usa con la versi�n 2, o hay que utilizarla de alguna manera y no veo c�mo o no s�.

bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar){
	bool movRealizado = false;

	fila[posSoltar] = fila[posIni];
	fila[posIni] = 0;
	movRealizado = true;

	return movRealizado;
}
//Y con esta funci�n pasa lo mismo

void ejecutarExcavadora(tArray fila, int tam){
	int posicion, direccion;

	cout << "\nIntroduce la posici�n desde la que empujar� la excavadora: ";
	cin >> posicion;

	cout << "\nIntroduce la direcci�n que quiere (1. Derecha, -1. Izquierda): ";
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
	// Se pone tam-1 en la ultima condici�n porque tam inclu�a el centinela

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
																						Cuando si se tendr�a que poder seg�n lo que pide la practica*/
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
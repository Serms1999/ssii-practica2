#include<stdio.h>
#include<iostream>
#include<fstream>
#include<regex>
#include<string>
#include<list>
using namespace std;

// Tipos de atributo
enum type { NU = 1, Nom = 2 };
enum operation { menor = 1, menorI = 2, mayor = 3, mayorI = 4, igual = 5 };

// Definicion de la estructuras
struct antecedente
{
	string izq;
	string der;
	operation op;
};

// Definimos el consecuente igual que un antecedente
typedef antecedente consecuente;

struct regla
{
	int numRegla;
	list<antecedente> antecedentes;
	consecuente consecuente;
	int prioridad;
};

struct atributo
{
	string nombre;
	type tipo;
	list<string> valores;
};

inline bool operator==(const regla& r1, const regla& r2)
{
	return r1.numRegla == r2.numRegla;
}

inline bool operator==(const antecedente& p1, const antecedente& p2)
{
	return (p1.izq == p2.izq) && (p1.der == p2.der) && (p1.op == p2.op);
}

// Funciones

// Devuelve el operador asociado a un string
operation stringToOP(string s);

// Devuelve un string dado un consecuente
string consecuenteToString(consecuente c);

// Rellena los conjuntos reglas, reglasString, atributos, 
// hechos y el objetivo con los valores dados en BC, BH y conf
void leerFicheros(string BC, string BH, string conf, 
	list<regla>& reglas, list<string>& reglasString, list<atributo>& atributos, list<antecedente>& hechos, string& objetivo);

// Da valores a los atributos de un antecedente p con los datos del string s
void leerAntecedente(antecedente& p, string s);

void leerBaseConocimiento(string fichero, list<regla>& reglas, list<string>& reglasString);

void leerBaseHechos(string fichero, list<antecedente>& hechos);

void leerFicheroConf(string fichero, list<atributo>& atributos, string& objetivo, list<regla>& reglas);

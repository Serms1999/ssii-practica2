#include<stdio.h>
#include<iostream>
#include<fstream>
#include<regex>
#include<string>
#include<list>
using namespace std;

// Tipos de Atributo
enum type { NU = 1, Nom = 2 };
enum operation { menor = 1, menorI = 2, mayor = 3, mayorI = 4, igual = 5 };

// Definicion de la estructuras
struct Antecedente
{
	string izq;
	string der;
	operation op;
};

// Definimos el Consecuente igual que un Antecedente
typedef Antecedente Consecuente;

struct Regla
{
	int numRegla;
	list<Antecedente> antecedentes;
	Consecuente consecuente;
	int prioridad;
};

struct Atributo
{
	string nombre;
	type tipo;
	list<string> valores;
};

inline bool operator==(const Regla& r1, const Regla& r2)
{
	return r1.numRegla == r2.numRegla;
}

inline bool operator==(const Antecedente& p1, const Antecedente& p2)
{
	return (p1.izq == p2.izq) && (p1.der == p2.der) && (p1.op == p2.op);
}

// Funciones

// Devuelve el operador asociado a un string
operation stringToOP(string s);

// Devuelve un string dado un Consecuente
string consecuenteToString(Consecuente c);

// Rellena los conjuntos reglas, reglasString, atributos, 
// hechos y el objetivo con los valores dados en BC, BH y conf
void leerFicheros(string BC, string BH, string conf,
                  list<Regla>& reglas, list<string>& reglasString, list<Atributo>& atributos, list<Antecedente>& hechos, string& objetivo);

// Da valores a los atributos de un Antecedente p con los datos del string s
void leerAntecedente(Antecedente& p, string s);

void leerBaseConocimiento(string fichero, list<Regla>& reglas, list<string>& reglasString);

void leerBaseHechos(string fichero, list<Antecedente>& hechos);

void leerFicheroConf(string fichero, list<Atributo>& atributos, string& objetivo, list<Regla>& reglas);

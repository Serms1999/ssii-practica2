#include "Funciones.hpp"

extern string dominio;
extern list<antecedente> hechos;
extern string objetivo;
extern string nombreBH;
list<regla> reglasAplicadas;

string BHToString(list<antecedente>& BH)
{
	string s = "";
	list<antecedente>::iterator it;
	for (it = BH.begin(); it != BH.end(); it++)
	{
		s += consecuenteToString(*it) + "\n";
	}
	return s;
}

void crearFichero1()
{
	ofstream salida1;
	string nombre = "Salida1" + nombreBH + ".txt";
	salida1.open(nombre, ios::out | ios::trunc);

	list<antecedente> BH = hechos;

	salida1 << "Dominio de la aplicacion: " << dominio << endl;
	salida1 << "Objetivo: " << objetivo << endl;

	salida1 << "Base de Hechos inicial" << endl << BHToString(BH);

	if (reglasAplicadas.size() == 0)
	{
		salida1 << "----------------------------------------------------------------" << endl;
		salida1 << "No se llega a una solucion" << endl;
		salida1.close();
		return;
	}

	list<regla>::iterator it = reglasAplicadas.begin();

	do
	{
		salida1 << "----------------------------------------------------------------" << endl;
		salida1 << "Se aplica la regla:" << endl << getRegla((*it).numRegla) << endl;

		addConsecuencia(BH, (*it).consecuente);

		salida1 << "----------------------------------------------------------------" << endl;
		salida1 << "Nueva Base de Hechos: " << endl << BHToString(BH);

		it++;
	} while (it != reglasAplicadas.end());
	salida1 << "----------------------------------------------------------------" << endl;
	if ((*--it).consecuente.izq != objetivo)
	{
		salida1 << "No se llega a una solucion" << endl;
	}
	else
	{
		salida1 << "La solucion obtenida es: " << consecuenteToString((*it).consecuente) << endl;
	}


	salida1.close();
}

void crearFichero2()
{
	ofstream salida2;
	string nombre = "Salida2" + nombreBH + ".txt";
	salida2.open(nombre, ios::out | ios::trunc);
	list<regla>::iterator it;

	salida2 << "Dominio de la aplicacion: " << dominio << endl;
	salida2 << "Razonamiento:" << endl;
	for (it = reglasAplicadas.begin(); it != reglasAplicadas.end(); it++)
	{
		salida2 << getRegla((*it).numRegla) << endl;
	}
	if ((*--it).consecuente.izq != objetivo)
	{
		salida2 << "No se llega a una solucion" << endl;
	}
	else
	{
		salida2 << "Se llega a: " << consecuenteToString((*it).consecuente) << endl;
	}

	salida2.close();
}

int main(int argc, char** argv)
{
	leer(argv[1], argv[2], argv[3]);

	reglasAplicadas = SBR();

	crearFichero1();
	crearFichero2();
    
	return 0;
}

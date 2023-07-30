#include "Funciones.hpp"

//Variables globales
list<string> reglasString;
list<Regla> reglas;
static list<Atributo> atributos;
list<Antecedente> hechos;
string objetivo;

void leer(string BC, string BH, string conf)
{
	leerFicheros(BC, BH, conf, reglas, reglasString, atributos, hechos, objetivo);
}

void diferenciaConjuntos(list<Regla>& conjuntoConflicto, list<Regla> reglasAplicadas)
{
	list<Regla>::iterator itLista;

	for (itLista = reglasAplicadas.begin(); itLista != reglasAplicadas.end(); itLista++)
	{
		conjuntoConflicto.remove(*itLista);
	}
}

void unionConjuntos(list<Regla>& conjuntoConflicto, list<Regla> equiparacion)
{
	list<Regla>::iterator it;
	for (it = equiparacion.begin(); it != equiparacion.end(); it++)
	{
		if (!(find(conjuntoConflicto.begin(), conjuntoConflicto.end(), *it) != conjuntoConflicto.end()))
		{
			conjuntoConflicto.push_back(*it);
		}
	}
}

void addConsecuencia(list<Antecedente>& BH, Consecuente p)
{
	if (!(find(BH.begin(), BH.end(), p) != BH.end()))
	{
		BH.push_back(p);
	}
}

Atributo* buscarAtributo(string nombre)
{
	list<Atributo>::iterator itAtr = atributos.begin();
	while (itAtr != atributos.end() && (*itAtr).nombre != nombre)
		itAtr++;

	if (itAtr != atributos.end())
	{
		return &*itAtr;
	}
	return NULL;
}

bool comprobarValorNominal(string valor, list<string>& valores)
{
	list<string>::iterator itVal = valores.begin();
	while (itVal != valores.end() && (*itVal) != valor)
		itVal++;

	if (itVal != valores.end())
	{
		return true;
	}
	return false;
}

bool comprobarAntecedente(Antecedente ant, list<Antecedente> hechos)
{
	list<Antecedente>::iterator itHechos;
	for (itHechos = hechos.begin(); itHechos != hechos.end(); itHechos++)
	{
		if ((*itHechos).izq == ant.izq)
		{
			// Buscamos el Atributo al que corresponda
			Atributo* a = buscarAtributo(ant.izq);
			if (a != NULL && a->tipo == NU)
			{
				int nAntecedente = stoi(ant.der);
				int nHecho = stoi((*itHechos).der);

				// Comprobamos si el Antecedente se cumple o no
				switch (ant.op)
				{
				case menor:
					return nHecho < nAntecedente;
					break;

				case mayor:
					return nHecho > nAntecedente;
					break;

				case menorI:
					return nHecho <= nAntecedente;
					break;

				case mayorI:
					return nHecho >= nAntecedente;
					break;

				case igual:
					return nHecho == nAntecedente;
					break;
				}
			}
			else if (a != NULL && a->tipo == Nom)
			{
				// Buscamos si tiene un valor valido
				if (comprobarValorNominal(ant.der, a->valores))
				{
					return ant.der == (*itHechos).der;
				}
			}
		}
	}
	return false;
}

bool contenida(string meta, list<Antecedente> hechos)
{
	list<Antecedente>::iterator it = hechos.begin();
	while (it != hechos.end() && (*it).izq != meta)
		it++;
	if (it == hechos.end()) return false;
	return true;
}

list<Regla> equiparar(list<Regla> reglas, list<Antecedente> hechos)
{
	list<Regla> posibilidades;
	list<Regla>::iterator itReg;
	list<Antecedente>::iterator itAnt;

	for (itReg = reglas.begin(); itReg != reglas.end(); itReg++)
	{
		int cont = 0;
		// Comprobamos si cada Antecedente se cumple
		for (itAnt = (*itReg).antecedentes.begin(); itAnt != (*itReg).antecedentes.end(); itAnt++)
		{
			if (comprobarAntecedente(*itAnt, hechos))
			{
				cont++;
			}
		}
		// Si todos los antecedentes se han cumplido la Regla se añade
		if (cont == (*itReg).antecedentes.size())
		{
			posibilidades.push_back((*itReg));
		}
	}
	return posibilidades;
}

Regla resolver(list<Regla>& conjuntoConflicto)
{
	list<Regla>::iterator it = conjuntoConflicto.begin();
	Regla r = *it;
    it++;

	// Buscamos la Regla con la mayor prioridad
    while (it != conjuntoConflicto.end())
	{
		if ((*it).prioridad > r.prioridad) r = *it;
		it++;
	}
	return r;
}

string getRegla(int n)
{
	list<string>::iterator it = reglasString.begin();
	advance(it, n - 1);
	return *it;
}

list<Antecedente> getBH()
{
	return hechos;
}

void reconstruirSolucion(list<Regla>& reglasAplicadas)
{
	list<Regla>::reverse_iterator it;
	for (it = reglasAplicadas.rbegin(); it != reglasAplicadas.rend();)
	{
		// Si la consecuencia de la Regla está en la base de hechos inicial, la
		// Regla no aporta nada y se elimina
		if (find(hechos.begin(), hechos.end(), (*it).consecuente) != hechos.end())
		{
			reglasAplicadas.erase(--(it.base()));
		}
		else
		{
			// Si no es el caso buscamos si otras reglas usan su consecuencia
			if (it != reglasAplicadas.rbegin())
			{
				bool encontrada = false;
				list<Regla>::reverse_iterator itReg = reglasAplicadas.rbegin();
				list<Antecedente>::iterator itPrem;

				while (itReg != reglasAplicadas.rend() && !encontrada)
				{
					itPrem = (*itReg).antecedentes.begin();
					while (itPrem != (*itReg).antecedentes.end() && !encontrada)
					{
						if ((*itPrem) == (*it).consecuente)
						{
							encontrada = true;
						}
						itPrem++;
					}
					itReg++;
				}

				// Si ninguna otra Regla usa su consecuencia esa Regla no sirve
				if (!encontrada)
				{
					reglasAplicadas.erase(--(it.base()));
				}
				else
				{
					it++;
				}
			}
			else it++;
		}
	}
}

list<Regla> SBR()
{
	list<Antecedente> BH = hechos;
	list<Regla> conjuntoConflito;
	list<Regla> reglasAplicadas;
	list<Regla> antecedentes = reglas;
	Antecedente nuevosHechos;

	do
	{
		diferenciaConjuntos(conjuntoConflito, reglasAplicadas);
		diferenciaConjuntos(antecedentes, reglasAplicadas);
		unionConjuntos(conjuntoConflito, equiparar(antecedentes, BH));

		if (conjuntoConflito.size() != 0)
		{
			Regla r = resolver(conjuntoConflito);
			nuevosHechos = r.consecuente;
			reglasAplicadas.push_back(r);
			addConsecuencia(BH, nuevosHechos);
		}
	} while (!contenida(objetivo, BH) && conjuntoConflito.size() != 0);
	if (contenida(objetivo, BH))
	{
		reconstruirSolucion(reglasAplicadas);
		return reglasAplicadas;
	}
	return reglasAplicadas;
}

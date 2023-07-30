#include <cctype>
#include "leerFicheros.hpp"

// Variables
smatch match;
regex patBH("BH(.*).txt");
regex patReg("R([0-9]+): (si|SI|Si) (.*) (entonces|ENTONCES|Entonces) (.*)");
regex patAntecedentes("(([a-zA-Z]+) (<|<=|>|>=|=) (([a-zA-Z]|[0-9])+))( y (.*))*");
regex patAtr("(,*)([a-zA-Z]+)(.*)");
string dominio;
string nombreBH;

void leerFicheros(string BC, string BH, string conf,
                  list<Regla> & reglas, list<string>& reglasString, list<Atributo> & atributos, list<Antecedente> & hechos, string& objetivo)
{
	leerBaseConocimiento(BC, reglas, reglasString);
	leerBaseHechos(BH, hechos);
	leerFicheroConf(conf, atributos, objetivo, reglas);
}

void convertirMayusculas(string& s) {

	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
}

operation stringToOP(string s)
{
	if (s == "<") return menor;
	else if (s == "<=") return menorI;
	else if (s == ">") return mayor;
	else if (s == ">=") return mayorI;
	else return igual;
}

string consecuenteToString(Consecuente c)
{
	return c.izq + " = " + c.der;
}

void leerAntecedente(Antecedente& p, string s)
{
	if (regex_search(s, match, patAntecedentes))
	{
		p.izq = match.str(2);
		p.der = match.str(4);
		convertirMayusculas(p.izq);
		convertirMayusculas(p.der);
		p.op = stringToOP(match.str(3));
	}
}

void leerBaseConocimiento(string fichero, list<Regla>& reglas, list<string>& reglasString)
{
	ifstream fichEntrada(fichero);
	string linea;

	if (fichEntrada.fail())
	{
		cout << "No se puede abrir el archivo BC" << "\n";
		exit(1);
	}

	getline(fichEntrada,dominio);	// Lee el dominio;
	getline(fichEntrada, linea);	// Lee el numero de reglas
	int numReglas = stoi(linea);
	
	for (int i = 1; i <= numReglas; i++)
	{
		Regla r;
		getline(fichEntrada,linea);	// Lee la Regla i;
		reglasString.push_back(linea);
		r.numRegla = i;

		if (regex_search(linea, match, patReg))
		{
			// Leemos las antecedentes
			string antecedentes = match.str(3);

			// Leemos la consecuencia
			string consecuncia = match.str(5);
			leerAntecedente(r.consecuente, consecuncia);

			Antecedente p;
			// Procesamos los antecedentes
			while (regex_search(antecedentes, match, patAntecedentes))
			{
				p.izq = match.str(2);
 				p.der = match.str(4);
				convertirMayusculas(p.izq);
				convertirMayusculas(p.der);
				p.op = stringToOP(match.str(3));
				r.antecedentes.push_back(p);
				antecedentes = match.str(7);
			}
		}
		reglas.push_back(r);
	}

	fichEntrada.close();
}

void leerBaseHechos(string fichero, list<Antecedente>& hechos)
{
	ifstream fichEntrada(fichero);
	string linea;

	if (regex_search(fichero, match, patBH))
	{
		nombreBH = match.str(1);
	}

	if (fichEntrada.fail())
	{
		cout << "No se puede abrir el archivo BH" << "\n";
		exit(1);
	}

	getline(fichEntrada, linea);	// Lee el numero de hechos
	int numHechos = stoi(linea);

	Antecedente h;
	for (int i = 0; i < numHechos; i++)
	{
		getline(fichEntrada, linea);
		leerAntecedente(h, linea);
		hechos.push_back(h);
	}

	fichEntrada.close();
}

void leerFicheroConf(string fichero, list<Atributo>& atributos, string& objetivo, list<Regla>& reglas)
{
    ifstream fichEntrada(fichero);
    string linea;
    
    if(fichEntrada.fail())
    {
        cout << "No se puede abrir el archivo Config" << "\n";
        exit(1);
    }

    fichEntrada >> linea;   // Lee "ATRIBUTOS"
    int nAtributos;
    fichEntrada >> nAtributos;  // Lee el numero de atributos
    for(int i = 0; i < nAtributos; i++)
    {
        Atributo atrb;
        fichEntrada >> atrb.nombre;
		convertirMayusculas(atrb.nombre);
        string tipo;
        fichEntrada >> tipo;
        if(tipo == "NU")
        {
            atrb.tipo = NU;
        }
        else if(tipo == "Nom")
        {
            atrb.tipo = Nom;
            fichEntrada >> linea;   // Lee los valores del Atributo nominal
            
            while(regex_search(linea,match,patAtr))
            {
				string aux = match.str(2);
				convertirMayusculas(aux);
                atrb.valores.push_back(aux);
                linea = match.str(3);
            }
        }
        atributos.push_back(atrb);
    }
    fichEntrada >> linea;   // Lee "OBJETIVO"
    fichEntrada >> objetivo;
	convertirMayusculas(objetivo);

	fichEntrada >> linea;	// Lee "PRIORIDADES-REGLAS"
	fichEntrada >> linea;	// Lee el numero de reglas
	
	list<Regla>::iterator itReglas;

	for (itReglas = reglas.begin(); itReglas != reglas.end(); itReglas++)
	{
		fichEntrada >> (*itReglas).prioridad;
	}

    fichEntrada.close();
}

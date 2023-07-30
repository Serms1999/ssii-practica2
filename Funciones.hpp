#include <algorithm>
#include "leerFicheros.hpp"

// Lee los ficheros con la base de conocimiento, base de hechos y el fichero de configuracion
void leer(string BC, string BH, string conf);

// Elimina los elementos de la segunda lista de la primera
void diferenciaConjuntos(list<Regla>& conjuntoConflicto, list<Regla> reglasAplicadas);

// Incluye los elementos de la segunda lista en la primera si no estan previamente
void unionConjuntos(list<Regla>& conjuntoConflicto, list<Regla> equiparacion);

// Incluye una consecuencia a la base de hechos si no esta previamente
void addConsecuencia(list<Antecedente>& BH, Consecuente p);

// Dado el nombre busca en la estructura Atributo correspondiente
Atributo* buscarAtributo(string nombre);

// Comprueba si el valor de un Atributo nominal pertenece a los valores
// declarados de ese Atributo
bool comprobarValorNominal(string valor, list<string>& valores);

// Comprueba si una Antecedente es cierta o falsa
bool comprobarAntecedente(Antecedente hecho, list<Antecedente> antecedentes);

// Comprueba si el Atributo objetivo esta en la base de hechos
bool contenida(string meta, list<Antecedente> hechos);

// Devuelve las reglas que se pueden aplicar a traves de unos hechos
list<Regla> equiparar(list<Regla> reglas, list<Antecedente> hechos);

// Devuelve la Regla a aplicar
Regla resolver(list<Regla>& conjuntoConflicto);

// Devuelve la Regla n como string
string getRegla(int n);

// Devuelve la base de hechos inicial
list<Antecedente> getBH();

// Elimina las reglas innecesarias de la solucion
void reconstruirSolucion(list<Regla>& reglasAplicadas);

list<Regla> SBR();

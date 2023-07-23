#include <algorithm>
#include "leerFicheros.h"

// Lee los ficheros con la base de conocimiento, base de hechos y el fichero de configuracion
void leer(string BC, string BH, string conf);

// Elimina los elementos de la segunda lista de la primera
void diferenciaConjuntos(list<regla>& conjuntoConflicto, list<regla> reglasAplicadas);

// Incluye los elementos de la segunda lista en la primera si no estan previamente
void unionConjuntos(list<regla>& conjuntoConflicto, list<regla> equiparacion);

// Incluye una consecuencia a la base de hechos si no esta previamente
void addConsecuencia(list<antecedente>& BH, consecuente p);

// Dado el nombre busca en la estructura atributo correspondiente
atributo* buscarAtributo(string nombre);

// Comprueba si el valor de un atributo nominal pertenece a los valores
// declarados de ese atributo
bool comprobarValorNominal(string valor, list<string>& valores);

// Comprueba si una antecedente es cierta o falsa
bool comprobarAntecedente(antecedente hecho, list<antecedente> antecedentes);

// Comprueba si el atributo objetivo esta en la base de hechos
bool contenida(string meta, list<antecedente> hechos);

// Devuelve las reglas que se pueden aplicar a traves de unos hechos
list<regla> equiparar(list<regla> reglas, list<antecedente> hechos);

// Devuelve la regla a aplicar
regla resolver(list<regla>& conjuntoConflicto);

// Devuelve la regla n como string
string getRegla(int n);

// Devuelve la base de hechos inicial
list<antecedente> getBH();

// Elimina las reglas innecesarias de la solucion
void reconstruirSolucion(list<regla>& reglasAplicadas);

list<regla> SBR();

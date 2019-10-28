#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "abb.h"

#define PRIMERO_ES_MENOR -1
#define IGUALES 0
#define PRIMERO_ES_MAYOR 1

#define ERROR -1
#define EXITO  0

/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*abb_comparador)(void*, void*) abb_comparador;

/*
 * Destructor de elementos. Cada vez que un elemento deja el arbol
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*abb_liberar_elemento)(void*) abb_liberar_elemento;


typedef struct nodo_abb{
  void* elemento;
  struct nodo_abb* izquierda;
  struct nodo_abb* derecha;
} nodo_abb_t;

typedef struct abb{
  nodo_abb_t* nodo_raiz;
  abb_comparador comparador;
  abb_liberar_elemento destructor;
} abb_t;

/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if(comparador == NULL){
		return NULL;
	}

	abb_t* arbol = malloc(sizeof(abb_t));
	if(arbol == NULL){
		return NULL;
	}

	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->destructor = destructor;

	return arbol;
}

/*
 * Determina si el árbol está vacío. 
 * Devuelve true si lo está, false en caso contrario.
 */
bool arbol_vacio(abb_t* arbol){
	return ((arbol == NULL) || (arbol->nodo_raiz == NULL));
}

// Pre C.: Recibe 3 punteros a la raiz, al nodo a insertar y a la función comparadora.
// Post C.: Inserta el nodo con su respectivo elemento en el lugar correspondiente según la siguiente convención...
//			Si el elemento a insertar es menor, va a izquierda.
//			Si el elemento a insertar es mauor o igual, va a derecha.
void arbol_insertar_recursiva(nodo_abb_t* raiz, nodo_abb_t* nuevo_nodo, abb_comparador comparador){
	if(raiz == NULL){
		return;
	}

	if((comparador(nuevo_nodo->elemento, raiz->elemento) == IGUALES) || (comparador(nuevo_nodo->elemento, raiz->elemento) == PRIMERO_ES_MAYOR)){
		if(raiz->derecha == NULL){
			raiz->derecha = nuevo_nodo;
		}
		else{
			arbol_insertar_recursiva(raiz->derecha, nuevo_nodo, comparador);
		}
	}
	else if(comparador(nuevo_nodo->elemento, raiz->elemento) == PRIMERO_ES_MENOR){
		if(raiz->izquierda == NULL){
			raiz->izquierda = nuevo_nodo;
		}
		else{
			arbol_insertar_recursiva(raiz->izquierda, nuevo_nodo, comparador);
		}
	}
}

/*
 * Inserta un elemento en el árbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El árbol admite elementos con valores repetidos.
 */
int arbol_insertar(abb_t* arbol, void* elemento){
	if(arbol == NULL){
		return ERROR;
	}

	nodo_abb_t* nodo_padre = NULL;
	nodo_abb_t* nuevo_nodo = malloc(sizeof(nodo_abb_t));
	if(nuevo_nodo == NULL){
		return ERROR;
	}
	
	nuevo_nodo->elemento = elemento;

	if(arbol_vacio(arbol)){
		arbol->nodo_raiz = nuevo_nodo;
	}
	else{
		nodo_padre = arbol->nodo_raiz;
		arbol_insertar_recursiva(arbol->nodo_raiz, nuevo_nodo, arbol->comparador);
	}

	nuevo_nodo->derecha = NULL;
	nuevo_nodo->izquierda = NULL;

	return EXITO;
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.  
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int arbol_borrar(abb_t* arbol, void* elemento){

}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 * 
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol)){
		return NULL;
	}

	bool elemento_encontrado = false, no_esta = false;
	nodo_abb_t* nodo_aux = arbol->nodo_raiz;

	while(((nodo_raiz->derecha) || (nodo_raiz->izquierda)) && (!elemento_encontrado) && (!no_esta)){
		if(arbol->comparador == IGUALES){
			elemento_encontrado = true;
		}
		else if(arbol->comparador == PRIMERO_ES_MAYOR){
			if(nodo_aux->derecha == NULL){
				no_esta = true;
			}
			else{
				nodo_aux = nodo_aux->derecha;
			}
		}
		else{
			if(nodo_aux->izquierda == NULL){
				no_esta = true;
			}
			else{
				nodo_aux = nodo_aux->izquierda;
			}
		}
	}

	if((!elemento_encontrado) || (no_esta)){
		return NULL;
	}

	return elemento;
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío.
 */
void* arbol_raiz(abb_t* arbol){
	if(arbol == NULL){
		return NULL;
	}
	return (arbol->nodo_raiz->elemento);
}


/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){

}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){

}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){

}

/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){
	if(arbol == NULL){
		return;
	}
	while(!arbol_vacio(arbol)){
		arbol_borrar(arbol, arbol->nodo_raiz->elemento);
	}
}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el 
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.
 * Los recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
*/
void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){

}
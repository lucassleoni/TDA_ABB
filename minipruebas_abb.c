#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"

typedef struct cosa{
    int clave;
    char contenido[10];
} cosa;

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c){
	   c->clave = clave;
    }
    return c;
}

void destruir_cosa(cosa* c){
    if(c){
	   free(c);
    }
}

int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2){
	   return 0;
    }
    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave){
	   return 1;
    }
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave){
	   return -1;
    }

    return 0;
}

void destructor_de_cosas(void* elemento){
    if(!elemento){
	   return;
    }
    destruir_cosa((cosa*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento){
        printf("%i ", ((cosa*)elemento)->clave);
    }
    return false;
}

bool mostrar_hasta_5(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento){
        printf("%i ", ((cosa*)elemento)->clave);
        if(((cosa*)elemento)->clave == 5){
            return true;
        }
    }

    return false;
}

bool mostrar_acumulado(void* elemento, void* extra){
    if(elemento && extra){
        *(int*)extra += ((cosa*)elemento)->clave;
        printf("%i ", *(int*)extra);
    }

  return false;
}

void testear_caso_feliz(){
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    cosa* c1= crear_cosa(1);
    cosa* c2= crear_cosa(2);
    cosa* c3= crear_cosa(3);
    cosa* c4= crear_cosa(4);
    cosa* c5= crear_cosa(5);
    cosa* c6= crear_cosa(6);
    cosa* c7= crear_cosa(7);
    cosa* auxiliar = crear_cosa(0);
    
    arbol_insertar(arbol, c4);
    arbol_insertar(arbol, c2);
    arbol_insertar(arbol, c6);
    arbol_insertar(arbol, c1);
    arbol_insertar(arbol, c3);
    arbol_insertar(arbol, c5);
    arbol_insertar(arbol, c7);

    printf("El nodo raiz deberia ser 4: %s\n", ((cosa*)arbol_raiz(arbol))->clave == 4?"SI":"NO");

    auxiliar->clave = 5;
    printf("Busco el elemento (5): %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave == 5?"SI":"NO");

    auxiliar->clave = 7;
    printf("Borro nodo hoja (7): %s\n", (arbol_borrar(arbol, auxiliar)) == 0?"SI":"NO");

    auxiliar->clave = 6;
    printf("Borro nodo con un hijo (6): %s\n", (arbol_borrar(arbol, auxiliar)) == 0?"SI":"NO");

    auxiliar->clave = 2;
    printf("Borro nodo con dos hijos (2): %s\n", (arbol_borrar(arbol, auxiliar)) == 0?"SI":"NO");

    auxiliar->clave = 4;
    printf("Borro la raiz (4): %s\n", (arbol_borrar(arbol, auxiliar)) == 0?"SI":"NO");

    auxiliar->clave = 3;
    printf("Busco el elemento (3): %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave == 3?"SI":"NO");


    cosa* elementos[TAM_ARRAY];

    printf("Recorrido inorden (deberian salir en orden 1 3 5): ");
    int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, TAM_ARRAY);

    for(int i = 0; i < cantidad; i++){
	   printf("%i ", elementos[i]->clave);
    }

    printf("\n\nInserto mas valores y pruebo el iterador interno\n\n");
    arbol_insertar(arbol, crear_cosa(15));
    arbol_insertar(arbol, crear_cosa(0));
    arbol_insertar(arbol, crear_cosa(9));
    arbol_insertar(arbol, crear_cosa(7));
    arbol_insertar(arbol, crear_cosa(4));

    
    printf("Recorrido inorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
    printf("\n");

    printf("Recorrido preorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
    printf("\n");
    
    printf("Recorrido postorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
    printf("\n");

    printf("\nRecorrido inorden hasta encontrar el 5: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    printf("Recorrido preorden hasta encontrar el 5: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    printf("Recorrido postorden hasta encontrar el 5: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    int acumulador=0;
    printf("\nRecorrido inorden acumulando los valores: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador);
    printf("\n");

    acumulador=0;
    printf("Recorrido preorden acumulando los valores: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador);
    printf("\n");

    acumulador=0;
    printf("Recorrido postorden acumulando los valores: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador);
    printf("\n");
    
    free(auxiliar);
    arbol_destruir(arbol);
}


// Pre C.: ---
// Post C.: Crea un ABB vacío y verifica si el nodo raíz es NULL, imprimiendo el resultado de la prueba por pantalla.
void si_abb_esta_vacio_la_raiz_deberia_ser_NULL(){
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    printf("\nPrueba #1: Verificar si la raíz de un ABB vacío es NULL.\n");

    printf("\t%s: La raíz de un ABB vacío %s NULL.\n",
          (arbol_raiz(arbol) == NULL)?"EXITO":"FALLO",
          (arbol_raiz(arbol) == NULL)?"es":"no es");
    
    arbol_destruir(arbol);
}

// Pre C.: ---
// Post C.: Inserta 3 elementos. Luego invoca a las funciones 'arbol_buscar' y 'arbol_borrar' con un elemento distinto de los previamente
//          insertados y verifica si esta acción devuelve NULL (para la función de búsqueda) y el código de error establecido '-1'
//          (para la función de borrado), imprimiendo el resultado de la prueba por pantalla.
void buscar_y_borrar_un_elemento_que_no_esta_devuelve_NULL_y_error(){
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    printf("\nPrueba #2: Verificar si buscar y borrar un elemento que no está devuelve NULL/error.\n");

    cosa* elemento_1 = crear_cosa(1);
    cosa* elemento_2 = crear_cosa(2);
    cosa* elemento_3 = crear_cosa(3);
    cosa* elemento_extra = crear_cosa(4);
    
    arbol_insertar(arbol, elemento_2);
    arbol_insertar(arbol, elemento_1);
    arbol_insertar(arbol, elemento_3);

    printf("\t%s: Buscar un elemento que no está %s NULL. \n",
          (arbol_buscar(arbol, elemento_extra)) == NULL?"EXITO":"FALLO",
          (arbol_buscar(arbol, elemento_extra)) == NULL?"devuelve":"no devuelve");

    printf("\t%s: Borrar un elemento que no está %s error. \n",
          (arbol_borrar(arbol, elemento_extra)) == ERROR?"EXITO":"FALLO",
          (arbol_borrar(arbol, elemento_extra)) == ERROR?"devuelve":"no devuelve");

    free(elemento_extra);
    arbol_destruir(arbol);
}

// Pre C.: ---
// Post C.: Inserta un elemento en el ABB y verifica si luego el ABB se encuentra vacío, imprimiendo el resultado de la prueba por pantalla.
void luego_de_insertar_elemento_el_abb_no_deberia_estar_vacio(){
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    printf("\nPrueba #3: Verificar si luego de insertar un elemento el arbol no está vacío.\n");

    cosa* elemento_1 = crear_cosa(1);
    arbol_insertar(arbol, elemento_1);

    printf("\t%s: Luego de insertar un elemento, el árbol %s vacío. \n",
          (!arbol_vacio(arbol))?"EXITO":"FALLO",
          (arbol_vacio(arbol))?"está":"no está");

    arbol_destruir(arbol);
}

// Pre C.: ---
// Post C.: Verifica si (sobre un ABB nulo) las funciones 'arbol_borrar' y 'arbo_insertar' devuelven el código de error
//          establecido '-1', imprimiendo el resultado de la prueba por pantalla.
void si_abb_es_nulo_insertar_y_borrar_devuelven_NULL(){
    abb_t* arbol = NULL;

    printf("\nPrueba #4: Verificar si insertar y borrar sobre un árbol nulo devuelve error.\n");

    cosa* elemento_1 = crear_cosa(1);

    printf("\t%s: Insertar un elemento sobre un árbol nulo %s error. \n",
          (arbol_insertar(arbol, elemento_1)) == ERROR?"EXITO":"FALLO",
          (arbol_insertar(arbol, elemento_1)) == ERROR?"devuelve":"no devuelve");

    printf("\t%s: Borrar un elemento de un árbol nulo %s error. \n",
          (arbol_borrar(arbol, elemento_1)) == ERROR?"EXITO":"FALLO",
          (arbol_borrar(arbol, elemento_1)) == ERROR?"devuelve":"no devuelve");

    free(elemento_1);
}

// Pre C.: ---
// Post C.: Inserta y borra 100 elementos aleatorios, y verifica si al finalizar el proceso queda vacío el ABB,
//          imprimiendo el resultado de la prueba por pantalla.
void si_inserto_y_borro_la_misma_cantidad_de_elementos_el_arbol_deberia_quedar_vacio(){
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    printf("\nPrueba #5: Verificar si al insertar y borrar una misma cantidad de elementos, el árbol queda vacío.\n");

    srand((unsigned int)time(NULL));
    cosa* array_elementos[100];

    for(int i = 0; i < 100; i++){
        array_elementos[i] = crear_cosa(i);
    }

    // Inserción de números del 0 al 99:
    for(int i = 0; i < 100; i++){
        arbol_insertar(arbol, array_elementos[i]);
    }

    // Borrado en orden inverso:
    for(int i = 99; i >= 0; i--){
        arbol_borrar(arbol, array_elementos[i]);
    }

    printf("\t%s: Al insertar y borrar una misma cantidad de elementos, el árbol %s vacío. \n\n",
          (arbol_vacio(arbol))?"EXITO":"FALLO",
          (arbol_vacio(arbol))?"queda":"no queda");

    arbol_destruir(arbol);
}


int main(){
    // Test provisto por la cátedra:
    testear_caso_feliz();

    // Tests propios:
    si_abb_esta_vacio_la_raiz_deberia_ser_NULL();
    buscar_y_borrar_un_elemento_que_no_esta_devuelve_NULL_y_error();
    luego_de_insertar_elemento_el_abb_no_deberia_estar_vacio();
    si_abb_es_nulo_insertar_y_borrar_devuelven_NULL();
    si_inserto_y_borro_la_misma_cantidad_de_elementos_el_arbol_deberia_quedar_vacio();

    return 0;
}
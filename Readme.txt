TDA ABB (Árbol Binario de Búsqueda)

La implementación del TDA ABB incluído en 'TDA ABB (Lucas Leoni).zip' posee los siguientes programas:
    1) 'abb.h' es la biblioteca que incluye las firmas de las funciones primitivas para el funcionamiento del ABB.
    2) 'abb.c' es el programa con la implementación dele ABB.
    3) 'minipruebas_abb.c' es el programa que contiene las pruebas que testean el funcionamiento del ABB implementado.
    4) 'makefile' es el programa que facilita el acceso a las líneas de compilación y ejecución del ABB, las pruebas y Valgrind.
    5) 'Consigna' es la consigna del trabajo pŕactico.


Estructuras utilizadas:

1) Nodo: cada nodo posee un puntero 'void*' al elemento que apunta y dos punteros a sus nodos izquierdo/derecho.
             La estructura 'nodo_abb_t nodo' utilizada es la siguiente:

typedef struct nodo_abb{
  	void* elemento;
  	struct nodo_abb* izquierda;
  	struct nodo_abb* derecha;
} nodo_abb_t;


2) Árbol: el árbol posee un puntero al primer nodo (nodo_raíz), junto con dos punteros a funciones que implementará el usuario (comparador y destructor).
          La estructura 'abb_t arbol' utilizada es la siguiente:

typedef struct abb{
  	nodo_abb_t* nodo_raiz;
  	abb_comparador comparador;
  	abb_liberar_elemento destructor;
} abb_t;

    2.1) Los punteros a las funciones 'Comparador' y 'Destructor' son:

            typedef int (*abb_comparador)(void*, void*);
            typedef void (*abb_liberar_elemento)(void*);


Funciones del TDA ABB

Aclaración: todas las funciones utilizadas verifican (previo a ser ejecutadas) que no haya ningún error (arbol o raíz nulos).

1) Creación del ABB ---> abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor);
     Crea la estructra 'abb_t arbol'.
     Devuelve un puntero a la estructura 'abb_t arbol' y reserva la memoria necesaria para su almacenamiento en el Heap,
     incializando el puntero al 'nodo_raiz' en NULL y asignando los punteros a las funciones de comparación y destrucción
     a los campos correspondientes de l aestructura del ABB.
     Devuelve NULL en caso de haber habido un error al crear el ABB.

2) Insertar elementos ---> int arbol_insertar(abb_t* arbol, void* elemento);
     Inserta el elemento recibido, reservando la memoria necesaria para el nuevo nodo que lo contiene y actualizando los punteros correspondientes,
     invocando a la función propia 'arbol_insertar_recursiva'.
     Si el árbol esta vacío, el 'nodo_raiz' apuntará al nuevo nodo (el único).
     Devuelve '0' si la operación tuvo éxito y '-1' si falló.

3) Borrar elementos ---> int arbol_borrar(abb_t* arbol, void* elemento);
     Busca y borra el elemento recibido, actualizando los punteros correspondientes y liberando la memoria ocupada por el nodo borrado,
     invocando a la función propia 'arbol_borrar_recursiva'.
     Disminuye la cantidad de elementos de la lista.
     Devuelve '0' si la operación tuvo éxito y '-1' si falló (o si no se encontró el elemento).

4) Buscar un elemento determinado ---> void* arbol_buscar(abb_t* arbol, void* elemento);
     Busca un elemento coincidente con el recibido, por medio de la función comparadora.
     Devuelve el elemento encontrado o NULL si no lo encuentra.

5) Primer elemento del ABB (raíz) ---> void* arbol_raiz(abb_t* arbol);
     Devuelve un puntero al elemento contenido en el 'nodo_raíz' del ABB.
     Si el ABB está vacío, devuelve NULL.

6) ABB vacío ---> bool arbol_vacio(abb_t* arbol);
     Determina si el ABB está vacío (es decir, si tiene 0 elementos/nodos).
     Devuelve 'true' si el ABB está vacío o es nulo, y 'false' en cualquier otro caso.

7) Destrucción del ABB ---> void arbol_destruir(abb_t* arbol);
     En caso de no estar vacío, borra todos los elementos/nodos del ABB hasta que no tenga ninguno, invocando la función
     destructora con cada elemento presente en el arbol.
     Luego, destruye la estructura 'abb_t arbol' (liberando la memoria ocupada por esta).

8) Iterador interno ---> void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra);
     Recorre el árbol e invoca la función con cada elemento del mismo. El recorrido finaliza cuando la función devuelve 'true',
     aún si quedan elementos por recorrer, o si ya se recorrieron todos los elementos presentes en el ABB.
     Si el ABB está vacío o es nulo, finaliza el procedimiento sin ejecutar el bloque de acciones.
     El recorrido se realiza de acuerdo al recorrido solicitado. Los recorridos válidos son:
       - Inorden.
       - Preorden.
       - Postorden.


Recorridos sobre el ABB

Las tres funciones siguientes, llenan el array del tamaño dado con los elementos de árbol, cada una respetando su recorrido correspondiente.
Todas devuelven la cantidad de elementos del array que pudo llenar (si el espacio en el array no alcanza para almacenar todos los elementos,
llena hasta donde puede y devuelve la cantidad de elementos que pudo poner):

1) Recorrido Inorden ---> int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array);
2) Recorrido Preorden ---> int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array);
3) Recorrido Postorden ---> int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array);


Funciones Propias (para modularizar/simplificar la implementacíon del ABB)

1) void arbol_insertar_recursiva(nodo_abb_t* raiz, nodo_abb_t* nuevo_nodo, abb_comparador comparador);
     Función auxiliar para poder insertar elementos de forma recursiva.

2) int arbol_borrar_recursiva(nodo_abb_t* raiz, nodo_abb_t** nodo_padre, void* elemento_a_borrar, abb_comparador comparador, abb_liberar_elemento destructor);
     Función auxiliar para poder borrar elementos de forma recursiva.

3) nodo_abb_t* nodo_menor_de_los_mayores(nodo_abb_t* raiz);
     Al intentar borrar un nodo con dos hijos (izquierdo y derecho), se utiliza esta función para buscar el nodo con el menor elemento
     del sub-árbol derecho del nodo mencionado, quien será el reemplazo del elemento del nodo a borrar, y devuelve un puntero a dicho nodo.

4) void* arbol_buscar_recursiva(nodo_abb_t* raiz, void* elemento_buscado, abb_comparador comparador);
     Función auxiliar para poder buscar elementos de forma recursiva.

5) void arbol_recorrido_inorden_recursiva(nodo_abb_t* raiz, void** array, int* posicion_array, int tamanio_array);
     Función auxiliar para poder recorrer los elementos del árbol de la forma 'Inorden' de forma recursiva.

6) void arbol_recorrido_preorden_recursiva(nodo_abb_t* raiz, void** array, int* posicion_array, int tamanio_array);
     Función auxiliar para poder recorrer los elementos del árbol de la forma 'Preorden' de forma recursiva.

7) void arbol_recorrido_postorden_recursiva(nodo_abb_t* raiz, void** array, int* posicion_array, int tamanio_array);
     Función auxiliar para poder recorrer los elementos del árbol de la forma 'Postorden' de forma recursiva.


Funciones para el Iterador Interno

Las 3 funciones siguientes permiten recorrer el ABB con los 3 recorridos mencionados a continuación para aplicar la función recibida a cada elementos del árbol.    

1) void arbol_inorden(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* extra);
2) void arbol_preorden(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* extra);
3) void arbol_postorden(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* extra);


Compilación y Convenciones

1) Tamaño del ABB
     Inicialmente, el ABB se creará totalmente vacío (0 elementos/nodos).

2) Inserción de elementos iguales
     Si se inserta un elemento ya existente, este se insertrá en el sub-árbol derecho de su elemento semejante, es decir:
        - Si el elemento a insertar es menor, se inserta a izquierda.
        - Si el elemento a insertar es mayor o igual, se inserta a derecha.

3) Makefile
   La carpeta cuenta con un programa 'makefile' que posee los siguientes comandos:
     3.1) 'make compile' compilará el programa 'abb.c' junto con las pruebas que testean su funcionamiento, ejecutando la línea de compilación:
              gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 *.c -o abb -g

     3.2) 'make arbol' compilará el programa con la línea mencionada en el punto (3.1) y luego ejecutará las pruebas (incluídas en la carpeta) con la línea:
              ./abb

     3.2) 'make valgrind' ejecutrá Valgrind (mostrando los resultados de las pruebas por pantalla) con la línea:
              valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

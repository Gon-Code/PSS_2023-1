#include <stdio.h>
#include <stdlib.h>

#include "elim-rango.h"

void eliminarRango(Nodo **phead, double y, double z) {
    //Funcion eliminar rango recibe una lista enlaza simple
    //Elimina de la lista los valores entre [y,z] incluyendo z e y
    //Haremos un recorrido de forma iterariva sobre la lista
    //Tambíen nos aprovecharamos de que la lista esta ordenada de manera ascendente
    // -----------------------------------
    //Crearemos dos punteros,uno que guarda el puntero anterior y otro que recorre la lista
    //Notemos que inicializamos el puntero prev como NULL cuando actual apunta a la cabeza
    Nodo *prev = NULL;
    Nodo *actual = *phead;
    
    //En este primer ciclo, buscamos el primer elemento mayor o igual a y
    while(actual!=NULL && actual->x <y){
        prev = actual;
        actual = actual->prox;
    }
    
    //Como el ciclo anterior acaba cuando encuentra el primer elemento mayor o igual a y
    //Nos basta encontrar un elemento menor o igual a z para eliminar ese nodo
    //Si el elemento tambien resulta ser mayor a z, significa que no tenemos mas nodos que cambiar, pues la lista esta ordenada
    while(actual!=NULL && actual->x <=z){
        //El caso base es cuando la cabeza de lista esta en el rango a eliminar
        if(prev==NULL){
            //La nueva cabeza será el 2 elemento de la lista
            *phead = actual->prox;
            //Guardamos un puntero con la direccion de la cabeza
            Nodo* tmp=actual;
            //Actualizamos el puntero actual
            actual = *phead;
            //Liberamos de memoria el anterior puntero cabeza
            free(tmp);
        }
        else{
        //Este es el caso donde el nodo actual no es la cabeza de la lista
            //Para eliminar el nodo siguiente, hacemos que el nodo prev apunte a prev.prox.prox
            //Que es lo mismo que actual.prox
            prev->prox = actual->prox;
            //Guardamos un puntero con la direccion del elemento eliminado
            Nodo* tmp = actual;
            //Actualizamos el nodo actual al del ahora nuevo elemento prev.prox
            actual = prev->prox;
            //Liberamos de memoria el nodo eliminado
            free(tmp);
        }
    }
    return;
}

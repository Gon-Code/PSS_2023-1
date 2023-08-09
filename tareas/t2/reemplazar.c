#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

//Parte a
char *reemplazo(char *s, char c, char *pal) {
    //Cada vez que aparezca el caracter 'c' en s, lo reemplazamos por pal.
    //La dificultad es que cambiaremos un caracter por varios caracteres
    //Primero calcularemos el largo del string resultante al reemplazar los 'c' por pal.
    int i=0; //Calcula el largo de s
    int j=0; //La cantidad de 'c' en el arreglo
    char *ptr = s;
    while(*ptr != '\0'){
        if( *ptr == c){
            j++;
            i++;
            ptr++;
            continue;
        }
        i++;
        ptr++;   
    }
    //Recorremos pal ahora
    char *ptr_2 = pal;
    int k = 0; //Largo de pal
    while(*ptr_2!='\0'){
        k++;
        ptr_2++;
    }
    //Creamos un string de tamaño (i-j)+j*k + 1
    int largo = (i-j)+j*k + 1;
    char* w = (char*) malloc(sizeof(char) * (largo)); 
    //Le agregamos los elementos de s
    //Si agregamos un caracter 'c', colocamos pal
    char *ptr_3 = w;
    char *ptr_4 = s;
    //NO OLVIDAR AÑADIR EL 0 AL FINAL DEL STRING  !!!!
    //ES LA UNICA RAZON PARA AÑADIR +1 AL LARGO DE W !!!!!
    while(*ptr_4!='\0'){
        if(*ptr_4==c){
            char *ptr_5 = pal; //Creamos un puntero en el inico de pal y lo recorremos
            while(*ptr_5!='\0'){
                *ptr_3=*ptr_5;
                ptr_5++;
                ptr_3++;
            }
            ptr_4++;
            continue;
        }   
        //En cualquier otro caso agregamos la letra de s en w
        *ptr_3=*ptr_4;
        ptr_3++;
        ptr_4++;
    }
    *ptr_3='\0';
    return w;
} 

//Parte b
void reemplazar(char *s, char c, char *pal) {
  //Almacenamos el largo de s
  int i = strlen(s);
  if(i==0){
    return;
  }
  //Almacenamos el largo de pal
  int k = strlen(pal);
  //Si el caracter c no está en c, entonces no hacemos nada en s
  char *ptr=s;
  int cantidad_c = 0;
  while(*ptr!='\0'){
    //Si leemos una c lo contamos
    if(*ptr==c){
        cantidad_c++;
        ptr++;
    }
    ptr++;
  }
  //Si no hay 'c' en s, terminamos el proceso
  if(cantidad_c==0){
    return;
  }
  //Dividimos el problema de acuerdo al largo de k
  //Caso k = 0
  //Cuando veamos una 'c' eliminamos 'c' haciendo que el valor a la derecha de c ahora esté en la posicion de 'c' hasta llegar al final de s
  if(k==0){
    char *ptr_k0=s;
    while(*ptr_k0!='\0'){
        char *s1=ptr_k0;
        if(*ptr_k0==c){
            char *s2= ptr_k0 + 1;
            while(*s1!='\0'){
                *s1=*s2;
                s1++;
                s2++;
            }
            ptr_k0++;
            continue;
        }
        ptr_k0++;
    }
    return;
  }
  //Caso k = 1
  //Cuando veamos una 'c' simplemente reemplazamos por pal, que ahora es un solo caracter
  if(k==1){
    char *ptr_k1=s;
    while(*ptr_k1!='\0'){
        if(*ptr_k1==c){
            char *aux_k1=pal;
            *ptr_k1=*aux_k1;
            ptr_k1++;
        }
        ptr_k1++;
    }
    return;
  }
  //Caso k > 1
  //Ahora debemos recorrer s de derecha a izquierda
  
  if(k>1){
    int move = cantidad_c*(k-1);
    //Ubicamos el \0 al final de s
    char *ptr_s1=s;
    char *ptr_s2=s;
    while(*ptr_s1!='\0'){
        ptr_s1++;
        ptr_s2++;
    }
    //Ahora que s1 y s2 estan ubicados en \0, movemos todos los elementos en cantidad_c(k-1) a la derecha
    //Ubicamos s2 al final del string resultante y s1 en \0
    char *start=s;
    ptr_s2+=move;
    while(ptr_s1>start-1){
        //Cuando s1 no esta en una a, movemos los elementos a la derecha
        if(*ptr_s1!=c){
            *ptr_s2=*ptr_s1;
            ptr_s1--;
            ptr_s2--;  
        }
        else{
            //Ubicamos un puntero a la ultima letra de pal 
            char *ptr_pal=pal;
            ptr_pal+=k-1;
            int j=k;
            //Aqui agregamos pal
            while(j>0){
                *ptr_s2=*ptr_pal;
                ptr_s2--;
                ptr_pal--;
                j--;
            }
            //como ya llenamos pal por primera vez, ahora movemos s1 a la izquierda a un caracter que posiblemente no es un a
            ptr_s1--;
        }  
    }
   return;
  }
}















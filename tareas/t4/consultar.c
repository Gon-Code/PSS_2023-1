#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pss.h"

#define MAXTAM (800+2)
#define MAX_LINEAS 10000

int main(int argc, char *argv[]) {
    //Si hay mas de 2 parametros devolvemos un error
    if(argc != 3){
        fprintf(stderr,"Uso: ./consultar.bin <diccionario> <llave>\n");
        return 1;
    }
    //Tomo los argumentos de la funcion, primero el nombre del archivo, luego la palabra
    char *filename = argv[1];
    char *llave = argv[2];
    
    //Creamos el puntero dict que apunta al archivo que queremos abrir
    FILE *dict = fopen(filename,"r");
    
    //Chequeamos que el archivo exista
    if(access(filename,F_OK)!=0){
        fprintf(stderr,"%s: ",filename);
        fprintf(stderr,"No such file or directory\n");
        return 1;
    }
    //Chequeamos tener permisos de lectura para el archivo
    if(access(filename,R_OK)!=0){
        fprintf(stderr,"%s: ",filename);
        fprintf(stderr,"Permission denied\n");
        return 1;   
    }
    //Si el diccionario esta vacio devolvemos un error
    //Para saber si el diccionario esta vacio, mandamos un puntero al final del archivo
    //Si esta en la misma primero posicion del archivo es porque esta vacio
    
   
    //----------------------------------------------------------------------------------------
    //Aqui comienza el algoritmo que imprime las definiciones de las palabras del diccionario
    //----------------------------------------------------------------------------------------
    
    //Primero calcularemos el largo de las lineas
    char buf[MAXTAM];
    //Termina de escribir en buf cuando lee '\n'
    fgets(buf,MAXTAM,dict);
    //Contamos los caracteres de buf hasta llegar a '\0'
    char *ptr = buf;
    int largo_linea = 0;
    while(*ptr!='\0'){
        ptr++;
        largo_linea++;
    }
    //Ahora buscamos la llave en la linea n
    //donde n se calcula como hash_string(llave)%j
    //j es la cantidad de lineas del archivo
    fseek(dict,0,SEEK_END);
    long int tamaño = ftell(dict);
    if(tamaño == 0){
        fprintf(stderr,"%s: ",filename);
        fprintf(stderr,"el dicionario esta vacio\n");
        return 1;
    }
    if(tamaño%largo_linea != 0){
        fprintf(stderr,"%s: ",filename);
        fprintf(stderr,"el tamaño del archivo no es multiplo del tamaño de la linea\n");
        return 1;
    }
    long int j = tamaño/largo_linea  ;
    //i es la linea en la que estamos buscando, siempre empezamos por la que da el hash
    long int i = hash_string(llave)%j;
    //Guardaremos la def en el siguiente string
    char def[largo_linea];
    //cnt cuenta las lineas que hemos revisado
    //cuando cnt sea igual a j, es porque no hay lineas en blanco en el archivo
    //es decir, la llave no esta y ademas el archivo esta lleno
    int cnt = 1;
    while(cnt<=j){
        //Posicionamos un puntero en cada inicio de linea para ver si esta ahí el string de la llave
        fseek(dict,largo_linea*i,SEEK_SET);
        //Si la linea esta vacia, saltamos a la siguiente
        if(fgets(buf,MAXTAM,dict)==NULL){
        //Con fprintf podemos elegir en que salida mostrar los errores
            fprintf(stderr, "%s: ",filename);
            fprintf(stderr, "el diccionario no contiene la llave %s\n",llave);
            return 1;
        }
        
        //Aquí fgets ya reescribio en buf la linea completa
        //Chequeamos que la linea tiene el mismo largo que todas las demas
        char test[MAXTAM];
        fgets(test,MAXTAM,dict);
        if(strlen(test)!=largo_linea){
            fprintf(stderr,"%s: ",filename);
            fprintf(stderr,"linea %ld de tamaño incorrecto\n",i-3);
            return 1;
        }
        //Buscaremos la llave en el comienzo de la linea
       
        if(strncmp(llave,buf,strlen(llave))==0){
                //Si la llave esta en el comienzo de la linea
                //Creamos un string auxiliar para ver si esta el caracter ':'
                char test[MAXTAM];
                strcpy(test,buf+strlen(llave));
                if(test[0]!=':'){
                    fprintf(stderr,"%s: ",filename);
                    fprintf(stderr,"linea %ld no posee : para terminar la llave\n",i);
                    return 1;
                }
                //Copiamos la definicion en def despues del char ':'
                strcpy(def,buf+strlen(llave)+1);
                printf("%s",def);
                break;
            
        }
        //Si no se encontro la llave ,seguimos buscando en la sgt linea
        i++;
        //Si la linea no esta en el archivo entonces volvemos a la primera linea
        if(i>j){
            i=0;
        }
        //Aumentamos el contador pues ya revisamos una linea
        cnt++;
        
   }   
   fclose(dict);
   return 0;
}


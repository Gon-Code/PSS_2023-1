
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "maleta.h"




// Use la funcion leer para obtener los resultados del pipe
int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double llenarMaleta(double w[], double v[], int z[], int n, double maxW, int k) {
    //Inicializamos los array para los pids y para los file descriptors
    int pids[8];
    int fds[8][2];
    //Tamaño de los subconjuntos que revisara cada CORE
    //int tam_bloque = n/8;
    for(int i=0; i<8; i++){
        close(fds[i][0]);
        pipe(fds[i]);
        pids[i] = fork();
        if(pids[i] == 0){ //En los hijos
            srandom(getUSecsOfDay()*getpid());
            //Cada hijo hace k/8
            int newk = k/8;
            //Aqui implementamos algoritmo de llenarMaletaSEC
            double best = -1;
            for(int l=i*newk;l<=(i+1)*newk;l++){
                int x[n];
                double sumW=0,sumV=0;
                for(int j=0;j<n;j++){
                    x[j] = (random0or1() && sumW+w[j] <= maxW ) ? 1 : 0;
                    if(x[j]==1){
                        sumW += w[j];
                        sumV += v[j];
                    }
                }
                if(sumV > best){
                    best = sumV;
                    for(int j=0;j<n;j++){
                        z[j] = x[j];
                    }
                }
            }
            //z contiene los articulos elegidos, asi que lo escribimos en el pipe
            write(fds[i][1],z,n*sizeof(int));
            close(fds[i][1]);
            exit(0);
        }
        else{ // En el padre
            close(fds[i][1]);
        }
    }
    
    double result = 0;
    for(int i=0;i<8;i++){
        int z_cpy[n];
        //Ahora copiamos el resultado de cada hijo en z_cpy
        leer(fds[i][0],z_cpy,n*sizeof(int));
        close(fds[i][0]);
        waitpid(pids[i],NULL,0);
        //Ahora comparamos z con z_cpy, si , la suma de valores de z_cpy es mejor que la anterior,la guardamos
        double res_hijo = 0;
        for(int j=0;j<n;j++){
            //Si z_cpy[j] es igual a 1 es porque estamos sumando su valor
            if(z_cpy[j]==1){
                res_hijo += v[j];
            }
        }
        //Ahora si el resultado del hijo es mejor que el anterior, lo guardamos y copiamos z_cpy en z
        if(res_hijo > result){
            result = res_hijo;
            for(int j=0; j<n; j++){
                if(z_cpy[j]==1){
                    z[j] = z_cpy[j];
                }
                else{
                    z[j] = 0;
                }
            }
        }
    }

    return result;
}

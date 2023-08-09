#include <stdlib.h>
#include <string.h>

#include "comprimir.h"


uint comprimir(uint a[], int nbits) {
    int cnt = 0; // Variable para avanzar en el arreglo a
    uint ans = 0; // ans retorna el numero que comprime el arreglo a 
    uint mask = ~0; // mascara de bits 11111...11111
    mask <<= (nbits-1); // Separamos el desplazamiento porque nbits puede ser 32 
    mask <<= 1;         // 1111111 ... 000000  nbits en 0
    mask = ~mask;       // 000000.....111111 nbits en 1
    //Recorremos de nbits en nbits hasta que i sea mayor al tamaño de la estructura uint desplazado en 3 
    for(int i=nbits;i<=(sizeof(uint)<<3);i+=nbits){
        ans = ans << (nbits-1) << 1; // Colocamos los bits menos significativos de ans en 0 
        // Tomamos los nbits menos significativos de a[cnt] 
        // Guardamos los nbits menos significativos de a[cnt] en ans
        ans |= a[cnt] & mask;       
        cnt++; // Vamos al siguiente elemento de a
    }
    return ans;
}
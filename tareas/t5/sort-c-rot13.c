#include <string.h>
//strCmp devuelve 0 si los strings son igual
//strCmp devuelve -1 si s1 es menor lexicograficamente que s2
//strCmp devuelve 1 si s1 es mayor lexicograficamente que s2
//Primero hay que descifrar las palabras
int strCmp(char *s1, char *s2) {
    // Recorremos ambos strings
    // El ciclo se termina cuando las letras no son iguales
    // O cuando se recorre por completo alguna palabra
    while (*s1 != '\0') {
        if (*s1 != *s2) {
            break;
        }
        s1++;
        s2++;
    }
    
    // Aquí guardamos las letras que difieren
    // ch1 alberga el caracter al que apunta s1
    // ch2 alberga el caracter al que apunta s2
    char a2 = *s1;
    char a3 = *s2;
    if (a2 > 'm') {
        a2 = *s1 - 13;
    } else {
        a2 = *s1 + 13;
    }

    if (a3 > 'm') {
        a3 = *s2 - 13;
    } else {
        a3 = *s2 + 13;
    }

    if (a2 < a3) {
        return -1;
    } else if (a2 > a3) {
        return 1;
    } else {
        return 0;
    }
}


void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {
 
    int t1= strCmp(p[0], p[1]);
    
    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}

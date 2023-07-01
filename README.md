# Programación de Software y Sistemas
## Disclaimer
Este repositorio ha sido creado con el único objetivo de aprender de manera práctica el uso de GitHub, y al mismo tiempo usarlo de respaldo para mis tareas. Habiendo dicho esto, quiero recalcar que la intención no es compartir ni difundir el material del curso sino mostrar a grandes rasgos los tópicos que abarca a través del desarrollo de las tareas del semestre Otoño 2023.
### Índice
- [Introducción](#introducción)
- [Tareas](#tareas)
  - [Tarea 1 : Bits](#tarea-1-bits)
  - [Tarea 2 : Strings](#tarea-2-strings)
  - [Tarea 3 : Estructuras](#tarea-3-estructuras)
  - [Tarea 4 : Archivos](#tarea-4-archivos)
  - [Tarea 5 : RISC-V ASSEMBLY](#tarea-5-assembly)
- [Soluciones](#soluciones)
  - [Tarea 1 : Bits](#solucion-tarea-1-bits)
  - [Tarea 2 : Strings](#tarea-2-strings)
  - [Tarea 3 : Estructuras](#tarea-3-estructuras)
  - [Tarea 4 : Archivos](#tarea-4-archivos)
  - [Tarea 5 : RISC-V ASSEMBLY](#tarea-5-assembly)
## Introducción
Espero que este Repositorio te sirva para entender un poco más este difícil pero para mi gusto, interesantísimo ramo del dcc.
## Tareas 
Esta es la principal sección de este repositorio, la cual está subdividida en 8 tareas. Cada tarea contiene: El enunciado de la tarea, los archivos para corroborar su solución y mi propia solución del problema. Cabe mencionar que las soluciones no son necesariamente las más óptimas, pero resuelven de manera correcta el ejercicio correspondiente.
## Tarea 1 Bits
Programe la función ``comprimir`` con el siguiente encabezado:
Esta es la principal sección de este repositorio, la cual está subdividida en 8 tareas. Cada tarea contiene: El enunciado de la tarea, los archivos para corroborar su solución y mi propia solución del problema. Cabe mencionar que las soluciones no son necesariamente las más óptimas, pero resuelven de manera correcta el ejercicio correspondiente. Para corroborar que su solución es correcta debe hacer lo siguiente:
* Requerimientos para aprobar su solución :
  * make run debe felicitarlo por aprobar este modo de ejecución. Su Solución no debe ser 80% más lenta que la solución del profesor.
  * make run-g debe felicitarlo
  * make run-san debe felicitarlo y no reportar ningún problema como por ejemplo desplazamientos indefinidos
Lo anterior solo aplica desde la tarea 1 hasta la tarea 5.
## Tarea 1 Bits
Puedes ver el enunciado en formato pdf [aquí](https://github.com/Gon-Code/PSS_2023-1/blob/main/img/Tarea_1_PSS.pdf).Los archivos con los casos de prueba y la plantilla con el encabezado de la función ``comprimir`` se encuentran en la carpeta [t1](https://github.com/Gon-Code/PSS_2023-1/blob/main/tareas/t1).
Programe la función ``comprimir`` con el siguiente encabezado:
```c
typedef unsigned int uint;
uint comprimir(uint *a, int nbits);
```
Esta función comprime múltiples enteros sin signo almacenados en el arreglo ``a`` en un solo entero sin signo. Para ello se retorna la concatenación de todos los elementos en ``a`` truncados a ``nbits``. La cantidad de elementos almacenados en el arreglo ``a`` es el número de enteros de nbits que caben en un entero sin signo, es decir, el máximo numero ``k`` que cumple con ``k*nbits<=sizeof(uint)*8``, en donde ``sizeof()*8`` es el tamaño de un entero sin signo (no es 32 en algunas plataformas).
Ejemplo de uso:
```c
uint a[] = { 0b 100 110 101 011 000, 0b 000 101 101 011, 0b 100 001 010 000};
uint a[] = { 0b 100 110 101 011 000, 0b 000 101 101 011, 0b 100 001 010 000 };
uint r[] = comprimir(a,9);
// r es 0b 101 011 000    101 101 011    001 010 000
//         <---a[0]--->   <---a[1]--->   <---a[2]--->
```
Restricciones:
  -Usted no puede usar los operadores de multiplicación, división o módulo. Use los operadores de bits eficientemente.
  -Si necesita calcular el número de bits en variables de tipo ``uint``, calcule ``sizeof(uint)<<3``. La cantidad de bits en un byte es siempre 8.
  -El estándar de C no especifica el resultado para desplazamientos mayores o iguales al tamaño del operando. Sanitize rechaza el desplazamiento ``x<<nbits`` cuando ``nbits`` es 32 o superior. En esta tarea use ``x<<(nbits-1)<<1`` porque sí va a funcionar considerando las restricciones en el rango que puede tomar ``nbits`` en esta tarea.

* Restricciones :
  * Usted no puede usar los operadores de multiplicación, división o módulo. Use los operadores de bits eficientemente.
  * Si necesita calcular el número de bits en variables de tipo ``uint``, calcule ``sizeof(uint)<<3``. La cantidad de bits en un byte es siempre 8.
  * El estándar de C no especifica el resultado para desplazamientos mayores o iguales al tamaño del operando. Sanitize rechaza el desplazamiento ``x<<nbits`` cuando ``nbits`` es 32 o superior. En esta tarea use ``x<<(nbits-1)<<1`` porque sí va a funcionar considerando las restricciones en el rango que puede tomar ``nbits`` en esta tarea.

## Tarea 2 Strings
Aqui la tarea 2
## Tarea 3 Estructuras
Aqui la tarea 3
## Tarea 4 Archivos
Aqui la tarea 4
## Tarea 5 ASSEMBLY
Aqui la tarea 5
## Soluciones
En esta sección se encuentran las soluciones de todas las tareas. 
## Solucion Tarea 1 Bits
```c
uint comprimir(uint a[], int nbits) {
    int j = 0;
    uint respuesta = 0;
    uint y = ~0;
    uint mascara = y <<(nbits-1)<<1;
    uint mascarafinal = ~(mascara);
    for(int i=nbits;i<=(sizeof(uint)<<3);i+=nbits){
        respuesta = respuesta << (nbits-1) << 1;
        respuesta |= a[j] & mascarafinal; 
        j++   
    }
    return respuesta;
}
```

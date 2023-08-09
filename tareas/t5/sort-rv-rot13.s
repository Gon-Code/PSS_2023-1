# sort: Ordena ascendentemente un arreglo de enteros sin signo usando un
# algoritmo ridiculamente ineficiente.

# La funcion sort esta programada en assembler RiscV. El codigo equivalente
# en C esta comentado, mostrando la ubicacion de las variables en los
# registros.  La funcion recorre el arreglo revisando que los elementos
# consecutivos esten ordenados.  Si encuentra 2 elementos consecutivos
# desordenados, los intercambia y reinicia el recorrido del arreglo
# desde el comienzo.  El arreglo esta ordenado cuando se recorre
# completamente sin encontrar elementos consecutivos desordenados.

    .file "sort-rv.s"
    .text
    .globl sort         # Se necesita para que la etiqueta sea conocida en
                        # test-sort.c
    .type sort, @function # typedef unsigned int uint;
sort:                   # void sort(uint nums[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   // Apila registro de activacion
    sw      ra, 60(sp)  #   // resguarda direccion de retorno
    sw      a0,56(sp)   #   uint *p= nums; // p esta en sp+56
    addi    a1,a1,-1    #   uint *ult= &nums[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   // tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   // nums esta en direccion sp+48
    mv      t0,a0       #   // p esta en registro t0
                        #   while (p<ult) {
    j       .while_cond #     // la condicion del while se evalua al final
.while_begin:           #     // del ciclo para mayor eficiencia

    sw      t0,56(sp)   # resguardar p en memoria

    # Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################

    # no puede alterar los registros s0-s11, si lo hace debe resguardarlos
    # en 0(sp), 4(sp), ... o 44(sp)
    # El valor de p esta temporalmente en el registro t0
    # No puede hacer mas trabajo que la comparacion (no puede usar ret)
    
    ##################################################################
    ######  AUTOR : GONZALO JAVIER CARTES ORTEGA    ##################
    ##################################################################
    
    lw      a0,0(t0)    #     int rc= strcmp(p[0], p[1]); // registro t1
    lw      a1,4(t0)    # En a0 esta s1 y en a1 esta s2
    li      a5,109      #Guardamos 'm' en a5
    li      a6,13       #Guardamos 13 en a6 
    
.inicio: 
    lbu      a2,0(a0)    #Cargamos a0 en a2
    lbu      a3,0(a1)    #Cargamos a1 en a3
    bne     a2,zero,.L1 #Si a2 es distinto de vacio
    beq     a2,zero,.L2 #Si a2 es vacio, desciframos los caracteres

.L1:
    bne     a2,a3,.L2      #Si son distintos los desciframos
    beq     a2,a3,.L3      #Si son iguales vamos a la siguiente letra

.L3:                       #En L3 vamos al siguiente caracter
    addi    a0,a0,1
    addi    a1,a1,1
    j       .inicio      #Volvemos a iterar
        
.L2:
    bgt     a2,a5,.L4      #Si a2 es mas grande que 'm'
    add    a2,a2,a6        #SI a2 es menor o igual a 'm' le sumamos 13
    andi    a2,a2,0xff     #Nos quedamos solo con los 1
    j           .L5        #Vamos a ver a3 ahora

.L4:
    addi    a2,a2,-13      #Si a2 es mas grande que 'm' le restamos 13
    andi    a2,a2,0xff     #Nos quedamos solo con los 1
    j           .L5        #Vamos a ver a3 ahora

.L5:
    bgt     a3,a5,.L6    #Si a3 es mas grande que 'm'
    add    a3,a3,a6      #Si a3 es menor o igual a 'm' le sumamos 13
    andi    a3,a3,0xff   #Nos quedamos solo con los 1
    j           .L7      #Vamos a ver como se comparan a2 y a3 

.L6:
    addi    a3,a3,-13    #Si a3 es mas grande que 'm' le restamos 13
    andi    a3,a3,0xff   #Nos quedamos solo con los 1
    j            .L7     #Vamos a ver como se comparan a2 y a3

.L7:
    bgt     a2,a3,.L8   #a2 es mayor a a3
    blt     a2,a3,.L9   #a2 es menor a a3
    j          .L10     #a2 y a2 son iguales
  
.L8:
    li      a0,1        #Como a2 es mayor que a3 guardamos 1 en a0
    sw      t0,56(sp)   # resguardar p en memoria antes de llamar a strcmp
    
    mv      t1,a0       # Dejar resultado de la comparacion en t1
    j       .decision   #Terminamos de modificar el codigo, continuamos en .decision

.L9:
    li      a0,-1       #Como a2 es menor que a3 guardamos -1 en a0
    sw      t0,56(sp)   # resguardar p en memoria antes de llamar a strcmp
    
    mv      t1,a0       # Dejar resultado de la comparacion en t1
    j       .decision   #Terminamos de modificar el codigo, continuamos en .decision 
    
.L10:    
    li      a0,0        #Como a2 es igual a a3 guardamos 0 en a0
    sw      t0,56(sp)   # resguardar p en memoria antes de llamar a strcmp
    
    mv      t1,a0       #Dejar resultado de la comparacion en t1
    j       .decision   #Terminamos de modificar el codigo, continuamos en .decision
    # En el registro t1 debe quedar la conclusion de la comparacion:
    # si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.

    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

    # Desde aca no puede modificar nada
    # Si t1>0 se intercambian p[0] y p[1] y se asigna p= noms para revisar
    # nuevamente que los elementos esten ordenados desde el comienzo del arreglo

.decision:              #     if (0>=rc) {
    lw      t0,56(sp)   #       // p esta en registro t0
    blt     zero,t1,.else
    addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
    j       .while_cond #     }

.else:                  #     else { // intercambar p[0] y p[1], y reiniciar
    lw      a0,0(t0)    #       int aux= p[0]; // a0
    lw      a1,4(t0)    #       int aux2= p[1];
    sw      a0,4(t0)    #       p[0]= aux2;
    sw      a1,0(t0)    #       p[1]= aux;
    lw      t0,48(sp)   #       p= noms;
                        #     }

.while_cond:            #     // se evalua la condicion del while
    lw      t1,52(sp)   #     // ult esta en t1
    bltu    t0,t1,.while_begin #  // Condicion del while es p<ult
			#   }
    lw      ra,60(sp)   #   // Se restaura direccion de retorno
    addi    sp,sp,64    #   // Desapila registro de activacion
    ret			# }
    
    
    
    
    ##################################################################
    ######  AUTOR : GONZALO JAVIER CARTES ORTEGA    ##################
    ##################################################################

# ALSP-IA-FC-CBJ-CPP

## Para compilar
```
make comp
```
Retorna un programa llamado FCCBJ

## Para ejecutar
Se hicieron dos comandos make exe para dos instancias, una creada por mí (airland0.txt) que termina en muy poco tiempo pero que sirve para ver que la técnica implementada funciona [más facil ver con debug = 1 (debug está en el Makefile)] y la otra entregada por el ayudante (airland1.txt) que nunca ejecuté por el suficiente tiempo para encontrar la mejor solución debido a su larga demora.

### Para airland0.txt
```
make exe0
```

### Para airland1.txt
```
make exe1
```

### Para otras instancias
En caso de otras instancias, compilar con
```
make comp
```
y después usar
```
./FCCBJ directorio_instancia random semilla debug
```

Ejemplo:
```
./FCCBJ "InstanciasALSP/Txt/airland0.txt 1 439923 1
```

Con 

directorio_instancia: Directorio de la instancia.

random = 2 Si se quiere instanciación en el orden ascendente que viene en la instancia.

random = 1 Si se quiere instanciación de variables y valores aleatorios.

random = 0 Si se quiere instanciación de variables con mayores penalizaciones (g y h) primero y con sus mejores valores (más cercanos a T) primero.

semilla: Semilla utilizada si random = 1

debug = 1 Si se desea mostrar por terminal qué variables se instancian, qué valores se filtran y qué soluciones se encuentran en el instante.

debug = 0 Si no se desea lo anterior.

## Para limpiar
```
make clean
```

## Información
Algoritmo = Forward Checking con CBJ

Problema = ALSP o Aircraft Landing Spacing Problem

Acercamiento = Búsqueda completa con órdenes de instanciación de variables y de valores aleatorios ó ordenados instanciando quienes penalizan más primero.

Representación = Arreglo de enteros

Función objetivo = Minimizar el costo de la separación del tiempo óptimo de aterrizaje

## Consideraciones
Cuando el programa termina, entrega por pantalla la mejor solución, el costo total y el tiempo de cómputo para llegar a esa solución.
Cuando se corta la ejecución del programa con Ctrl + C, se muestra la cantidad de instanciaciones, chequeos y retornos contados hasta la mejor solución.
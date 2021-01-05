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
./FCCBJ directorio_instancia semilla debug
```
con directorio_instancia el directorio de la instancia, semilla la semilla que se usará y debug = 0 si no se desean prints, debug = 1 si se desean prints de las soluciones que encuentra el programa.

## Para limpiar
```
make clean
```

## Información
Algoritmo = Forward Checking con CBJ

Problema = ALSP o Aircraft Landing Spacing Problem

Acercamiento = Búsqueda completa con órdenes de instanciación de variables y de valores aleatorios

Representación = Arreglo de enteros

Función objetivo = Minimizar el costo de la separación del tiempo óptimo de aterrizaje

## Consideraciones
Cuando el programa termina, entrega por pantalla la mejor solución, el costo total y el tiempo de cómputo para llegar a esa solución.
Cuando se corta la ejecución del programa con Ctrl + C, se muestra la cantidad de instanciaciones, chequeos y retornos contados hasta la mejor solución.
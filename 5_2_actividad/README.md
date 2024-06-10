
# Comparación de Ejecución: Programa Secuencial vs Paralelo

## Ejecución de los Programas
### Programa secuencial
Para ejecutar la versión secuencial del programa, use el siguiente comando:
```
./sumPrimeSeq [número]
```
donde `[número]` es el valor hasta el cual se desea calcular la suma de los números primos.

### Programa paralelo
Para ejecutar la versión paralelo del programa, use el siguiente comando:
```
./sumPrimeAsync [número de hilos] [número]
```
donde `[número de hilos]` es la cantidad de hilos a lanzar y `[número]` es el valor hasta el cual se desea calcular la suma de los números primos.

## Tiempos de ejecución usando time y una muestra de las ejecuciones
### Programa secuencial
```
./sumPrimeSeq 12389467
FINAL VALUE: 4852635144983
./sumPrimeSeq 12389467  4.57s user 0.00s system 99% cpu 4.577 total
```
- **Tiempo total (total)**: 4.577 segundos
- **Tiempo de CPU en modo usuario (user)**: 4.57 segundos

### Programa paralelo
```
./sumPrimeAsync 4 12389467
FINAL VALUE: 4852635144983 (Expected 49557868)
./sumPrimeAsync 4 12389467  4.90s user 0.00s system 302% cpu 1.623 total
```
- **Tiempo total (total)**: 1.623 segundos
- **Tiempo de CPU en modo usuario (user)**: 4.90 segundos

## Cálculo del Speedup

El speedup ($S_p$) se calcula usando la siguiente fórmula:

$$
S_p = \frac{T_1}{T_p} = \frac{4.577}{1.623}
$$

donde:
- $T_1$ es el tiempo de ejecución de la versión secuencial.
- $T_p$ es el tiempo de ejecución de la versión paralela con $p$ procesadores (en mi caso 4).

### Cálculo:
$$
S_p = \frac{4.577}{1.623} \approx 2.82
$$

El speedup obtenido usando 4 procesadores es aproximadamente 2.82, indicando que la versión paralela es **2.82** veces más rápida que la versión secuencial en **una** muestra.
# Comparación de Ejecución: Programa Secuencial vs Paralelo

## Ejecución de los Programas
### Programa secuencial
Para ejecutar la versión secuencial del programa, use el siguiente comando:
```
time elixir lexer.ex sync <path_de_archivos.cpp>
```

### Programa paralelo
Para ejecutar la versión paralelo del programa, use el siguiente comando:
```
time elixir lexer.ex async <path_de_archivos.cpp> <numero_de_cores>
```

## Tiempos de ejecución usando time y una muestra de las ejecuciones
### Programa secuencial
```
elixir lexer.ex sync   4.25s user 0.25s system 101% cpu 4.344 total
```
```
elixir lexer.ex sync   4.33s user 0.25s system 101% cpu 4.422 total
```
```
elixir lexer.ex sync   4.22s user 0.25s system 101% cpu 4.294 total
```
```
elixir lexer.ex sync   4.42s user 0.25s system 101% cpu 4.641 total
```
```
elixir lexer.ex sync   4.41s user 0.25s system 101% cpu 4.581 total
```
```
elixir lexer.ex sync   4.27s user 0.25s system 101% cpu 4.341 total
```
- **Promedio tiempo total (total)**: 4.437 segundos
- **Promedio tiempo de CPU en modo usuario (user)**: 4.32 segundos

### Programa paralelo
```
elixir lexer.ex async  8  5.38s user 0.37s system 301% cpu 1.879 total
```
```
elixir lexer.ex async  8  5.33s user 0.37s system 301% cpu 2.018 total
```
```
elixir lexer.ex async  8  5.3s user 0.37s system 301% cpu 1.855 total
```
```
elixir lexer.ex async  8  5.24s user 0.37s system 301% cpu 1.982 total
```
```
elixir lexer.ex async  8  5.34s user 0.37s system 301% cpu 1.897 total
```
```
elixir lexer.ex async  8  5.32s user 0.37s system 301% cpu 1.861 total
```
- **Promedio tiempo total (total)**: 1.915 segundos
- **Promedio tiempo de CPU en modo usuario (user)**: 5.32 segundos

## Cálculo del Speedup

El speedup ($S_p$) se calcula usando la siguiente fórmula:

$$
S_p = \frac{T_1}{T_p} = \frac{4.437}{1.915}
$$

donde:
- $T_1$ es el tiempo de ejecución de la versión secuencial.
- $T_p$ es el tiempo de ejecución de la versión paralela con $p$ procesadores.

### Cálculo:
$$
S_p = \frac{4.437}{1.915}  \approx  2.32
$$

El speedup obtenido usando 8 procesadores es aproximadamente 2.32, indicando que la versión paralela es **2.32** veces más rápida que la versión secuencial en **varias** muestras.

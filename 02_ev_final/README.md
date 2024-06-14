# Lexer Secuencial vs Paralelo

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


## Análisis de Complejidad

### Consideraciones
1. **Siempre se encuentra un patrón**: Esto significa que en el peor de los casos recorreremos todos los patrones (regex) hasta encontrar un match.

### Apertura y Cierre de Archivos
```elixir
{:ok, out_fd} = File.open(out_filename, [:write])
File.close(out_fd)
```
- Complejidad: O(1)

### Lectura de Archivos Línea por Línea
```elixir
File.stream!(in_filename)
|> Enum.map(&find_token(&1))
|> List.flatten()
```
- Complejidad de `File.stream!/1`: O(L), donde \( L \) es el número de líneas en el archivo.

### Extracción de Tokens
```elixir
defp find_token(line, res) do
  patterns = [...]
  ...
end
```
- La función `find_token/2` será llamada para cada línea y por cada remanente de línea.
- **Comparación de patrones**: Dado que siempre se encuentra un patrón, en el peor de los casos, se recorrerá la lista de patrones hasta encontrar el match. La complejidad de comparar con patrones será:
  - Si el match se encuentra al final de la lista de patrones, la complejidad es O(P), donde \( P \) es el número de patrones total.
- Entonces, para cada línea, la complejidad es O(N \* P), donde \( N \) es la longitud promedio de una la línea (el número de veces que se vuelve a llamar la función recursiva) y \( P \) es el número de patrones.

### Transformación y Filtrado de Resultados
- `Enum.map/2` tiene una complejidad de O(L) respecto al número de líneas.
- `List.flatten/1` tiene una complejidad de O(T), donde \( T \) es el número total de tokens.

### Generación de HTML
```elixir
def doHtml(list, out_fd) do
  Enum.map(list, fn {class, word} -> ... end)
  |> Enum.join("")
  ...
end
```
- Complejidad: O(T), donde \( T \) es el número total de tokens a escribir o concatenar con el html que depende del número de líneas de archivo.

### Complejidad Total

La complejidad total del programa, considerando las partes más significativas:
1. **Lectura de archivo**: O(L)
2. **Extracción de tokens por línea**: O(L \* N \* P)
3. **Transformación y filtrado**: O(T)
4. **Generación de HTML**: O(T)

Dado que la extracción de tokens es la operación dominante ya que las demas dependen del numero de lineas que tiene un archivo:

$$ \text{Complejidad~total} \approx O(L \cdot N \cdot P) $$

Donde:
- \( L \) es el número de líneas en el archivo.
- \( N \) es la longitud promedio de una línea (veces que se vuelve a llamar la función recursiva).
- \( P \) es el número de patrones.

Al asegurarse que siempre se encontrará un patrón (siempre y cuando este implementado correctamente), la complejidad en la extracción de tokens sigue siendo lineal respecto a la longitud de la línea.

## Reflexión
Considero que la principal implicación sobre este trabajo es la automatización de tareas de análisis de código puede reducir la necesidad de ciertos roles laborales, lo que puede tener un impacto negativo en el empleo. Además creo que promoviendo la re-capacitación y el desarrollo de nuevas habilidades en la fuerza laboral se puede lograr un equilibrio
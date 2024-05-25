# Lexer for C++ code
## José Manuel García Zumaya
## A01784238

Este programa define funciones para tokenizar una línea de texto.
Utiliza expresiones regulares para identificar y clasificar diferentes tipos de tokens
como palabras reservadas, directivas de preprocesamiento, referencias de bibliotecas, y más.

### Cómo ejecutar el programa

1. **Pre-requisitos**: Asegúrate de tener Elixir instalado en tu sistema. Puedes verificarlo ejecutando `elixir --version` en tu terminal.

2. **Preparación**:
   - Guarda tu código C++ en un archivo de texto con la extensión `.cpp`. Por ejemplo, `example.cpp`.

3. **Ejecución**:
   - Abre una terminal y navega al directorio donde tienes el archivo `ev_final_imc.ex` y el archivo C++.
   - Ejecuta el siguiente comando, reemplazando `example.cpp` con el nombre de tu archivo C++:

     ```sh
     elixir 07_file_io.exs example.cpp
     ```

4. **Resultado**:
   - El programa generará un archivo HTML con los tokens encontrados en tu archivo C++. El nombre del archivo de salida será el mismo que el archivo de entrada, pero con la extensión `-tokens.html`.
   - Por ejemplo, si tu archivo de entrada se llama `example.cpp`, el archivo de salida será `example-tokens.html`.

### Descripción del programa

El programa lee un archivo de texto línea por línea, buscando tokens usando expresiones regulares. Luego, escribe los tokens encontrados en un archivo HTML, clasificándolos según su tipo. Los tipos de tokens incluyen:

- **Palabras reservadas**: `~r/^break\b|^try\b|^catch\b|^char\b|^class\b|^const\b|^continue\b|^default\b|^delete\b|^auto\b|^else\b|^friend\b|^for\b|^float\b|^long\b|^new\b|^operator\b|^private\b|^protected\b|^public\b|^return\b|^short\b|^sizeof\b|^static\b|^this\b|^typedef\b|^enum\b|^throw\b|^mutable\b|^struct\b|^case\b|^register\b|^switch\b|^and\b|^or\b|^namespace\b|^static_cast\b|^goto\b|^not\b|^xor\b|^bool\b|^do\b|^double\b|^int\b|^unsigned\b|^void\b|^virtual\b|^union\b|^while\b|^cout\b|^endl\b|^using\b|^if\b/`
- **Directivas de preprocesamiento**: `~r/^#\w+/`
- **Referencias de bibliotecas**: `~r/^[<][\w\.]+[>]/`
- **Saltos de línea**: `~r/^\n+/`
- **Espacios**: `~r/^\s/`
- **Símbolos especiales**: `~r/^;/`
- **Nombres de estructuras o clases**: `~r/^\w+(?=\s*\{)/`
- **Declaraciones de instancias de estructuras o clases**: `~r/^\w+(?=\s+\w+)/`
- **Llaves**: `~r/^{|^}/`
- **Paréntesis**: `~r/^$begin:math:text$|^$end:math:text$/`
- **Nombres de funciones**: `~r/^\w+(?=\s*\()/`
- **Números enteros**: `~r/^[-+]?\d+\b(?!\.)/`
- **Números flotantes**: `~r/^[+-]?\d*\.\d+/`
- **Operadores**: `~r/^\+(?!\+)|^\-(?!\-)|^\=(?!\=)|^\:(?!\:)|^\:\:|^\<(?!\<)|^\>(?!\>)|^\&(?!\&)|^\<\<|^\>\>|^\.|^\+\+|^\-\-|^\=\=|^\&\&|^\,/`
- **Strings**: `~r/^".*"/`
- **Comentarios**: `~r/^\/\/.*|\/\*[\s\S]*?\*\//`
- **Variables**: `~r/^\w+/`

El archivo HTML generado puede abrirse en un navegador web para visualizar los tokens con estilos específicos según su tipo.

# Complejidad

## 1. get_tokens/2

Esta función procesa un archivo de entrada línea por línea y extrae tokens de cada línea, escribiéndolos en un archivo de salida en formato HTML.

- **Abrir el archivo para escritura (File.open/2):** O(1)
- **Leer el archivo línea por línea (File.stream!/1):** O(n), donde n es el número de líneas en el archivo.
- **Mapear cada línea para encontrar tokens (Enum.map/2):** Cada línea es procesada por find_token/1, cuya complejidad analizaremos más adelante.
- **Aplanar la lista de listas de tokens (List.flatten/1):** O(m), donde m es el total de tokens encontrados en todas las líneas.
- **Escribir tokens en el archivo de salida (doHtml/2):** La complejidad de esta función será analizada más adelante.
- **Cerrar el archivo (File.close/1):** O(1)

## 2. find_token/2 (privada)

Esta función recursiva encuentra y clasifica tokens en una línea de texto.

- **Base case:** Cuando la línea está vacía: O(1)
- **Patrones para coincidencias:** 17 patrones definidos. Comprobar cada patrón contra la línea es O(k) para cada patrón, donde k es la longitud de la línea.
- **Enum.find_value/2 para encontrar la coincidencia:** En el peor de los casos, debe revisar todos los patrones. Si p es el número de patrones y k es la longitud de la línea, esto es O(p * k).
- **Slicing la línea restante:** O(k), donde k es la longitud de la línea.
- **Llamada recursiva:** La función se llama recursivamente para procesar la línea restante.

Si consideramos que la línea tiene una longitud k, la función recursiva find_token/2 tiene una complejidad O(p * k^2) en el peor de los casos, ya que puede verificar todos los patrones para cada carácter de la línea.

## 3. doHtml/2

Esta función genera un archivo HTML con los tokens encontrados.

- **Imprimir la cabecera HTML:** O(1)
- **Mapear los tokens para generar contenido HTML:** O(m), donde m es el número total de tokens.
- **Convertir cada token a una cadena:** O(1) por token.
- **Reemplazar caracteres especiales en cada token:** O(l) por token, donde l es la longitud del token.
- **Unir los tokens procesados en una sola cadena (Enum.join/1):** O(m)
- **Imprimir el contenido HTML generado:** O(1)
- **Imprimir las etiquetas HTML de cierre:** O(1)

## Análisis de Complejidad Total

- **get_tokens/2:** O(n) para leer líneas del archivo.
- **Cada línea procesada por find_token/1:** O(p * k^2), donde p es el número de patrones y k es la longitud de la línea.
- **Aplanar la lista de tokens:** O(m), donde m es el número total de tokens.
- **Generar HTML (doHtml/2):** O(m * l), donde m es el número de tokens y l es la longitud promedio del token.

Si combinamos todo:

- **Lectura del archivo:** O(n)
- **Procesamiento de cada línea:** O(p * k^2) por línea, lo que da O(n * p * k^2) para todas las líneas.
- **Aplanar y generar HTML:** O(m * l), donde m es el número total de tokens y l es la longitud promedio del token.

## Complejidad Asintótica Combinada

Asumiendo que cada línea tiene un número promedio de tokens constante, el número total de tokens m es proporcional al número de líneas n.

- **Complejidad combinada:** O(n) + O(n * p * k^2) + O(m * l)
- **Si m ≈ n y l es constante, la complejidad se puede simplificar a O(n * p * k^2).**

Por lo tanto, la complejidad total del programa es O(n * p * k^2), donde n es el número de líneas en el archivo, p es el número de patrones, y k es la longitud promedio de las líneas.

# Reflexión sobre Expresiones Regulares y Algoritmos en el Programa Lexer

## Expresiones Regulares
Considero que las expresiones regulares son una herramienta muy poderosa, en este programa, se utilizan para definir patrones que corresponden a diferentes tipos de tokens en el código C++.
Además, estas tienen aplicaciones prácticas en la vida cotidiana. Su capacidad para identificar, manipular y transformar texto de manera eficiente las convierte en una herramienta indispensable para los programadores, desde la edición de documentos hasta la gestión de correos electrónicos y la validación de formatos.

La familiaridad con las expresiones regulares y su uso en aplicaciones cotidianas no solo mejoran la eficiencia en la realización de tareas, sino que también aportan ayuda en simplificación de procesos. 

### Proceso Recursivo
1. **Base Case**: Si la línea está vacía, se retorna la lista acumulada de tokens.
2. **Recursive Case**: 
   - Se define una lista de patrones.
   - Se encuentra el primer patrón que coincide con el inicio de la línea.
   - Se extrae el token correspondiente y el resto de la línea.
   - Se llama recursivamente a la función con el resto de la línea y la lista actualizada de tokens.

## Reflexión Final
El uso de expresiones regulares y algoritmos recursivos en este lexer para C++ demuestra la eficacia de estas técnicas para el análisis. Las expresiones regulares permiten definir patrones complejos de manera concisa, mientras que el algoritmo recursivo asegura un procesamiento estructurado y eficiente del texto. Por otro lado, la generación de HTML como salida proporciona una herramienta útil para visualizar y comprender la estructura del código fuente.

En resumen, este programa ejemplifica cómo las expresiones regulares y los algoritmos recursivos pueden combinarse para crear sistemas eficientes para el análisis y procesamiento de texto en el contexto del desarrollo de software.
#include <iostream>
#include <vector>

struct Punto {
    int x;
    int y;
};

int suma(int a, int b) {
    return a + b;
}

int main() {
    Punto p = {10, 20};
    std::vector<int> numeros = {1, 2, 3, 4, 5};

    for (int i = 0; i < numeros.size(); i++) {
        std::cout << "Numero: " << numeros[i] << std::endl;
    }

    int resultado = suma(p.x, p.y);
    std::cout << "Suma de p.x y p.y: " << resultado << std::endl;

    return 0;
}
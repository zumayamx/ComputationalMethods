#include <iostream>
using namespace std;

enum class Colors { RED, GREEN, BLUE };

int main() {
    Colors color = Colors::GREEN;

    switch (color) {
        case Colors::RED:
            cout << "Red" << endl;
            break;
        case Colors::GREEN:
            cout << "Green" << endl;
            break;
        case Colors::BLUE:
            cout << "Blue" << endl;
            break;
    }

    return 0;
}
#include <iostream>
using namespace std;

template <typename T>
class Calculator {
public:
    T add(T a, T b) {
        return a + b;
    }
};

int main() {
    Calculator<int> intCalc;
    Calculator<float> floatCalc;

    cout << intCalc.add(1, 2) << endl;
    cout << floatCalc.add(1.5, 2.5) << endl;

    return 0;
}
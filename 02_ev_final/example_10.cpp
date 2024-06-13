#include <iostream>
#include <functional>
using namespace std;

int main() {
    function<int(int, int)> add = [](int a, int b) {
        return a + b;
    };

    cout << add(3, 4) << endl;

    return 0;
}
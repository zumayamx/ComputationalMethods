#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> numbers = {1, 5, 3, 4, 2};

    sort(numbers.begin(), numbers.end());

    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
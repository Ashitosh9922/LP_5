// Problem statement: Min, Max, Sum, Average using parallel reduction
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    int sum = 0;
    int min_val = arr[0];
    int max_val = arr[0];

    // 🔹 Parallel Reduction
    #pragma omp parallel for reduction(+:sum) reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (arr[i] < min_val)
            min_val = arr[i];

        if (arr[i] > max_val)
            max_val = arr[i];
    }

    double avg = (double)sum / n;

    cout << "\nResults:\n";
    cout << "Sum = " << sum << endl;
    cout << "Minimum = " << min_val << endl;
    cout << "Maximum = " << max_val << endl;
    cout << "Average = " << avg << endl;

    return 0;
}

✅ Compile Command
Linux / WSL / macOS:
g++ -fopenmp reduction.cpp -o reduction
▶️ Run Command
./reduction
✅ Windows (MinGW / MSYS2)
Compile:
g++ -fopenmp reduction.cpp -o reduction.exe
Run:
reduction.exe */

/*
Enter number of elements: 5
Enter elements:
10 20 30 40 50

Results:
Sum = 150
Minimum = 10
Maximum = 50
Average = 30*/

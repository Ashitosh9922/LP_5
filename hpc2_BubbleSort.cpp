// Problem statement: Parallel Bubble sort
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void parallelBubbleSort(vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    parallelBubbleSort(arr);

    cout << "\nSorted Array:\n";
    for (int x : arr) cout << x << " ";

    return 0;
}

/*
✅ Compile Command
Linux / WSL / macOS:
g++ -fopenmp bubble.cpp -o bubble
▶️ Run Command
./bubble
✅ Windows (MinGW / MSYS2)
Compile:
g++ -fopenmp bubble.cpp -o bubble.exe
Run:
bubble.exe */

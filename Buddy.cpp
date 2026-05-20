#include <iostream>
#include <cmath>
using namespace std;

// Function to find next power of 2
int nextPowerOf2(int n) {
    return pow(2, ceil(log2(n)));
}

int main() {
    int totalMemory, n;

    cout << "Enter total memory (power of 2): ";
    cin >> totalMemory;

    cout << "Enter number of processes: ";
    cin >> n;

    int process[n];

    cout << "Enter process sizes:\n";
    for (int i = 0; i < n; i++)
        cin >> process[i];

    cout << "\nBuddy Allocation Process:\n";

    for (int i = 0; i < n; i++) {
        int required = nextPowerOf2(process[i]);

        if (required > totalMemory) {
            cout << "Process " << i + 1 << " (" << process[i] 
                 << ") -> Not Allocated\n";
            continue;
        }

        int block = totalMemory;

        cout << "\nProcess " << i + 1 << " (" << process[i] << "):\n";

        // Splitting
        while (block / 2 >= required) {
            cout << "Split block " << block 
                 << " -> " << block/2 << " + " << block/2 << endl;
            block /= 2;
        }

        cout << "Allocated block: " << block << endl;
    }

    return 0;
}
  /*#include <iostream>
#include <cmath>
using namespace std;

// Function to find next power of 2
int nextPowerOf2(int n) {
    return pow(2, ceil(log2(n)));
}

int main() {
    int totalMemory, n;

    cout << "Enter total memory (power of 2): ";
    cin >> totalMemory;

    cout << "Enter number of processes: ";
    cin >> n;

    int process[n];

    cout << "Enter process sizes:\n";
    for (int i = 0; i < n; i++)
        cin >> process[i];

    cout << "\nBuddy Allocation Process:\n";

    for (int i = 0; i < n; i++) {
        int required = nextPowerOf2(process[i]);

        if (required > totalMemory) {
            cout << "Process " << i + 1 << " (" << process[i] 
                 << ") -> Not Allocated\n";
            continue;
        }

        int block = totalMemory;

        cout << "\nProcess " << i + 1 << " (" << process[i] << "):\n";

        // Splitting
        while (block / 2 >= required) {
            cout << "Split block " << block 
                 << " -> " << block/2 << " + " << block/2 << endl;
            block /= 2;
        }

        cout << "Allocated block: " << block << endl;
    }

    return 0;
}
*/
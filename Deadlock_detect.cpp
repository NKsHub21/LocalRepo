#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    int allocation[n][m], request[n][m], available[m];

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "Enter Request Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> request[i][j];

    cout << "Enter Available Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> available[j];

    bool finish[n] = {false};

    cout << "\nDeadlock Detection Process:\n";

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {

            if (!finish[i]) {
                bool canAllocate = true;

                for (int j = 0; j < m; j++) {
                    if (request[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    cout << "Process " << i << " is executed\n";

                    for (int j = 0; j < m; j++)
                        available[j] += allocation[i][j];

                    finish[i] = true;
                }
            }
        }
    }

    bool deadlock = false;

    cout << "\nProcesses in Deadlock:\n";
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            cout << "P" << i << " ";
            deadlock = true;
        }
    }

    if (!deadlock)
        cout << "No Deadlock Detected";

    cout << endl;

    return 0;
}

#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> avail[i];

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Print Need Matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    bool finish[n] = {false};
    int safeSeq[n];
    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT in safe state\n";
            return 0;
        }
    }

    cout << "\nSystem is in SAFE state\nSafe sequence: ";
    for (int i = 0; i < n; i++)
        cout << "P" << safeSeq[i] << " ";

    return 0;
}
/*tep-by-Step Working
Step 1: Find Executable Process

Code:

if (need[i][j] > avail[j])

Checks:

Need <= Available ?

If yes:

Process can safely execute
Example

Suppose:

Available = [3 2 2]

P1 Need = [1 0 2]

Since:

1<=3
0<=2
2<=2

P1 can execute.

Step 2: Process Finishes

When process finishes:

It releases allocated resources back to system

Implemented here:

avail[j] += alloc[i][j];
Example

Suppose:

P1 Allocation = [2 1 0]

Then:

Available becomes:
Old + Allocation

Resources increase.

Step 3: Add to Safe Sequence
safeSeq[count++] = i;

Stores execution order.

Example:

P1 → P3 → P4 → P0 → P2
What Safe Sequence Means
Processes can execute in this order without deadlock
Step 4: Repeat

Algorithm repeatedly:

Find executable process
Execute it
Release resources

until all processes finish.

SAFE STATE Output
System is in SAFE state
Safe sequence: P1 P3 P4 P0 P2

Meaning:

There exists an order where all processes complete safely

No deadlock possible.

UNSAFE STATE Output

If no process can execute:

if (!found)

then:

System is NOT in safe state

Meaning:

Processes may enter deadlock
Technical OS Concept

Banker’s Algorithm is:

Deadlock Avoidance Algorithm

OS pretends:

"If I allocate resources now,
can all processes still finish later?"

If yes:

Grant resources

Else:

Deny request temporarily
Real-Life Analogy

Bank = OS

Customers = Processes

Money = Resources

Bank gives loans only if:

All customers can eventually repay safely

Otherwise bank refuses.

Hence:

Banker's Algorithm
Example Output Interpretation

Suppose output:

Need Matrix:
7 4 3
1 2 2
6 0 0
0 1 1
4 3 1

System is in SAFE state
Safe sequence: P1 P3 P4 P0 P2

Meaning:

P1 Executes First

Its need is satisfied.

After finishing:

Resources released
Then P3 Executes

More resources released.

Eventually All Processes Finish

So system safe.

OS Concepts Demonstrated

This program demonstrates:

Deadlock avoidance
Safe state checking
Resource allocation
Resource request analysis
Process scheduling feasibility
System safety analysis*/
#include <iostream>
using namespace std;

// ---------------- FIRST FIT ----------------
void firstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[20];

    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    for(int i = 0; i < processes; i++)
    {
        for(int j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;

                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\nFIRST FIT:\n";

    for(int i = 0; i < processes; i++)
    {
        cout << "Process " << i + 1
             << " (" << processSize[i] << ") -> ";

        if(allocation[i] != -1)
            cout << "Block " << allocation[i] + 1;
        else
            cout << "Not Allocated";

        cout << endl;
    }
}

// ---------------- BEST FIT ----------------
void bestFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[20];

    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    for(int i = 0; i < processes; i++)
    {
        int best = -1;

        for(int j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(best == -1 || blockSize[j] < blockSize[best])
                    best = j;
            }
        }

        if(best != -1)
        {
            allocation[i] = best;
            blockSize[best] -= processSize[i];
        }
    }

    cout << "\nBEST FIT:\n";

    for(int i = 0; i < processes; i++)
    {
        cout << "Process " << i + 1
             << " (" << processSize[i] << ") -> ";

        if(allocation[i] != -1)
            cout << "Block " << allocation[i] + 1;
        else
            cout << "Not Allocated";

        cout << endl;
    }
}

// ---------------- WORST FIT ----------------
void worstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[20];

    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    for(int i = 0; i < processes; i++)
    {
        int worst = -1;

        for(int j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(worst == -1 || blockSize[j] > blockSize[worst])
                    worst = j;
            }
        }

        if(worst != -1)
        {
            allocation[i] = worst;
            blockSize[worst] -= processSize[i];
        }
    }

    cout << "\nWORST FIT:\n";

    for(int i = 0; i < processes; i++)
    {
        cout << "Process " << i + 1
             << " (" << processSize[i] << ") -> ";

        if(allocation[i] != -1)
            cout << "Block " << allocation[i] + 1;
        else
            cout << "Not Allocated";

        cout << endl;
    }
}

// ---------------- NEXT FIT ----------------
void nextFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[20];

    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    int j = 0;

    for(int i = 0; i < processes; i++)
    {
        int count = 0;

        while(count < blocks)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;

                blockSize[j] -= processSize[i];
                break;
            }

            j = (j + 1) % blocks;
            count++;
        }
    }

    cout << "\nNEXT FIT:\n";

    for(int i = 0; i < processes; i++)
    {
        cout << "Process " << i + 1
             << " (" << processSize[i] << ") -> ";

        if(allocation[i] != -1)
            cout << "Block " << allocation[i] + 1;
        else
            cout << "Not Allocated";

        cout << endl;
    }
}

// ---------------- MAIN ----------------
int main()
{
    int blocks, processes;

    cout << "Enter number of memory blocks: ";
    cin >> blocks;

    int blockSize1[20], blockSize2[20], blockSize3[20], blockSize4[20];

    cout << "Enter block sizes:\n";

    for(int i = 0; i < blocks; i++)
    {
        cin >> blockSize1[i];

        blockSize2[i] = blockSize1[i];
        blockSize3[i] = blockSize1[i];
        blockSize4[i] = blockSize1[i];
    }

    cout << "Enter number of processes: ";
    cin >> processes;

    int processSize[20];

    cout << "Enter process sizes:\n";

    for(int i = 0; i < processes; i++)
        cin >> processSize[i];

    firstFit(blockSize1, blocks, processSize, processes);

    bestFit(blockSize2, blocks, processSize, processes);

    worstFit(blockSize3, blocks, processSize, processes);

    nextFit(blockSize4, blocks, processSize, processes);

    return 0;
}
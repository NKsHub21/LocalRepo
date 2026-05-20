#include <iostream>
using namespace std;

// ---------------- PAGING ----------------
void paging()
{
    int pageSize, logicalAddress;
    int pageTable[10];
    int n;

    cout << "\n--- PAGING ---\n";

    cout << "Enter number of pages: ";
    cin >> n;

    cout << "Enter page table (frame numbers):\n";
    for(int i = 0; i < n; i++)
    {
        cout << "Page " << i << " -> Frame: ";
        cin >> pageTable[i];
    }

    cout << "Enter page size: ";
    cin >> pageSize;

    cout << "Enter logical address: ";
    cin >> logicalAddress;

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if(pageNumber >= n)
    {
        cout << "Invalid Page Number\n";
        return;
    }

    int frameNumber = pageTable[pageNumber];

    int physicalAddress = (frameNumber * pageSize) + offset;

    cout << "\nPage Number: " << pageNumber << endl;
    cout << "Offset: " << offset << endl;
    cout << "Frame Number: " << frameNumber << endl;
    cout << "Physical Address: " << physicalAddress << endl;
}

// ---------------- SEGMENTATION ----------------
void segmentation()
{
    int n;

    cout << "\n--- SEGMENTATION ---\n";

    cout << "Enter number of segments: ";
    cin >> n;

    int base[10], limit[10];

    cout << "Enter Base Address and Limit for each segment:\n";

    for(int i = 0; i < n; i++)
    {
        cout << "Segment " << i << " Base: ";
        cin >> base[i];

        cout << "Segment " << i << " Limit: ";
        cin >> limit[i];
    }

    int segmentNumber, offset;

    cout << "Enter Segment Number: ";
    cin >> segmentNumber;

    cout << "Enter Offset: ";
    cin >> offset;

    if(segmentNumber >= n || offset >= limit[segmentNumber])
    {
        cout << "Invalid Logical Address\n";
        return;
    }

    int physicalAddress = base[segmentNumber] + offset;

    cout << "\nBase Address: " << base[segmentNumber] << endl;
    cout << "Offset: " << offset << endl;
    cout << "Physical Address: " << physicalAddress << endl;
}

// ---------------- MAIN ----------------
int main()
{
    paging();

    segmentation();

    return 0;
}
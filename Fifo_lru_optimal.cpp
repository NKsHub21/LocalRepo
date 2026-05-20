#include <iostream>
using namespace std;

void fifo(int pages[], int n, int frames)
{
    int f[50], front = 0, faults = 0;

    for(int i=0;i<frames;i++) f[i] = -1;

    for(int i=0;i<n;i++)
    {
        int found = 0;

        for(int j=0;j<frames;j++)
        {
            if(f[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            f[front] = pages[i];
            front = (front + 1) % frames;
            faults++;
        }
    }

    cout<<"FIFO Page Faults: "<<faults<<endl;
}

void lru(int pages[], int n, int frames)
{
    int f[50], time[50], faults = 0, t = 0;

    for(int i=0;i<frames;i++)
    {
        f[i] = -1;
        time[i] = 0;
    }

    for(int i=0;i<n;i++)
    {
        int found = 0;

        for(int j=0;j<frames;j++)
        {
            if(f[j] == pages[i])
            {
                t++;
                time[j] = t;
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            int min = time[0], pos = 0;

            for(int j=1;j<frames;j++)
            {
                if(time[j] < min)
                {
                    min = time[j];
                    pos = j;
                }
            }

            f[pos] = pages[i];
            t++;
            time[pos] = t;
            faults++;
        }
    }

    cout<<"LRU Page Faults: "<<faults<<endl;
}

void optimal(int pages[], int n, int frames)
{
    int f[50], faults = 0;

    for(int i=0;i<frames;i++) f[i] = -1;

    for(int i=0;i<n;i++)
    {
        int found = 0;

        for(int j=0;j<frames;j++)
        {
            if(f[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            int pos = -1, farthest = i;

            for(int j=0;j<frames;j++)
            {
                int k;
                for(k=i+1;k<n;k++)
                {
                    if(f[j] == pages[k]) break;
                }

                if(k == n)
                {
                    pos = j;
                    break;
                }

                if(k > farthest)
                {
                    farthest = k;
                    pos = j;
                }
            }

            if(pos == -1) pos = 0;

            f[pos] = pages[i];
            faults++;
        }
    }

    cout<<"Optimal Page Faults: "<<faults<<endl;
}

int main()
{
    int pages[50], n, frames;

    cout<<"Enter number of pages: ";
    cin>>n;

    cout<<"Enter reference string: ";
    for(int i=0;i<n;i++)
        cin>>pages[i];

    cout<<"Enter number of frames: ";
    cin>>frames;

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
/*This program implements three **Page Replacement Algorithms** used in **Virtual Memory Management** in Operating Systems:

1. FIFO (First In First Out)
2. LRU (Least Recently Used)
3. Optimal Page Replacement

The purpose is:

```text id="v1p9a0"
To minimize page faults during page replacement
```

---

# Core OS Concept

In virtual memory:

```text id="k2m8b1"
Processes use logical pages
```

but RAM has limited frames.

When a required page is not in memory:

```text id="q3n7c2"
Page Fault occurs
```

OS must:

1. Bring required page from disk
2. Replace some existing page if memory full

The replacement strategy is decided by these algorithms.

---

# Important Terms

---

# 1. Page

Fixed-size block of process memory.

Example:

```text id="t4x6d3"
Page 0
Page 1
Page 2
```

---

# 2. Frame

Fixed-size block in RAM.

Pages are loaded into frames.

---

# 3. Reference String

Sequence of pages requested by CPU.

Example:

```text id="u5y5e4"
7 0 1 2 0 3 0 4
```

Means CPU accesses pages in this order.

---

# 4. Page Fault

Occurs when requested page is absent in memory.

Example:

```text id="r6z4f5"
Requested page = 3
Frames contain = 0 1 2
```

Since 3 absent:

```text id="s7a3g6"
Page Fault
```

---

# Overall Program Flow

---

# Input

```cpp id="p8b2h7"
Enter number of pages
Enter reference string
Enter number of frames
```

---

# Then Program Runs

```text id="o9c1i8"
FIFO
LRU
Optimal
```

and prints page faults.

---

# 1. FIFO Algorithm

---

# Concept

```text id="n0d0j9"
Remove oldest loaded page first
```

Like a queue.

---

# Variable

```cpp id="m1e9k0"
front
```

tracks oldest page position.

---

# Working

---

## Step 1: Check if Page Exists

```cpp id="l2f8l1"
if(f[j] == pages[i])
```

If found:

```text id="k3g7m2"
No page fault
```

---

## Step 2: If Not Found

Replace oldest page:

```cpp id="j4h6n3"
f[front] = pages[i];
```

---

## Step 3: Move Front

```cpp id="i5i5o4"
front = (front + 1) % frames;
```

Circular movement.

---

# FIFO Example

Frames = 3

Reference:

```text id="h6j4p5"
1 2 3 4
```

---

## Initially

```text id="g7k3q6"
Empty Empty Empty
```

---

## Insert 1

```text id="f8l2r7"
1 _ _
```

Fault.

---

## Insert 2

```text id="e9m1s8"
1 2 _
```

Fault.

---

## Insert 3

```text id="d0n0t9"
1 2 3
```

Fault.

---

## Insert 4

Oldest page = 1

```text id="c1o9u0"
4 2 3
```

Fault.

---

# FIFO Drawback

May remove frequently used pages.

Can cause:

```text id="b2p8v1"
Belady’s Anomaly
```

where increasing frames increases faults.

---

# 2. LRU Algorithm

---

# Concept

```text id="a3q7w2"
Replace least recently used page
```

OS assumes:

```text id="z4r6x3"
Recently used pages likely needed again
```

---

# Additional Array

```cpp id="y5s5y4"
time[]
```

Stores last usage time.

---

# Global Counter

```cpp id="x6t4z5"
t
```

increases whenever page accessed.

---

# Working

---

## If Page Found

Update usage time:

```cpp id="w7u3a6"
time[j] = t;
```

Meaning:

```text id="v8v2b7"
Page recently used
```

---

## If Page Fault

Find minimum time:

```cpp id="u9w1c8"
Least recently used page
```

and replace it.

---

# Example

Suppose:

| Page | Last Used |
| ---- | --------- |
| 1    | 5         |
| 2    | 10        |
| 3    | 7         |

Smallest time:

```text id="t0x0d9"
5
```

So page 1 replaced.

---

# LRU Advantage

Better than FIFO because:

```text id="s1y9e0"
Uses usage history
```

---

# LRU Disadvantage

Needs extra tracking overhead.

---

# 3. Optimal Algorithm

---

# Concept

```text id="r2z8f1"
Replace page that will not be used for longest future time
```

This gives:

```text id="q3a7g2"
Minimum possible page faults
```

---

# Important

Optimal is theoretical because OS cannot perfectly know future references.

Used mainly for comparison.

---

# Working

---

## For Each Page in Frames

Program checks:

```cpp id="p4b6h3"
When will this page be used next?
```

---

# Case 1: Never Used Again

```cpp id="o5c5i4"
if(k == n)
```

Then immediately replace it.

Best choice.

---

# Case 2: Used Furthest in Future

Replace page whose next use is farthest away.

---

# Example

Frames:

```text id="n6d4j5"
1 2 3
```

Future references:

```text id="m7e3k6"
2 1 5 6 7 3
```

Next uses:

| Page | Next Use  |
| ---- | --------- |
| 1    | soon      |
| 2    | immediate |
| 3    | very late |

Replace:

```text id="l8f2l7"
3
```

---

# Final Output

Example:

```text id="k9g1m8"
FIFO Page Faults: 10
LRU Page Faults: 8
Optimal Page Faults: 7
```

Meaning:

| Algorithm | Faults |
| --------- | ------ |
| FIFO      | 10     |
| LRU       | 8      |
| Optimal   | 7      |

Lower faults = better memory utilization.

---

# OS Concepts Demonstrated

This program demonstrates:

* Virtual memory
* Demand paging
* Page replacement
* Frame allocation
* Page faults
* Memory management

---

# Technical Summary

---

## FIFO

```text id="j0h0n9"
Replace oldest page
```

---

## LRU

```text id="i1i9o0"
Replace least recently used page
```

---

## Optimal

```text id="h2j8p1"
Replace page used farthest in future
```
*/
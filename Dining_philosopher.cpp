#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define N 5

pthread_mutex_t chopstick[N];
pthread_mutex_t print_mutex;   // mutex for structured output
sem_t room;

void* philosopher(void* arg)
{
    int id = *((int*)arg);

    while (true)
    {
        // Thinking
        pthread_mutex_lock(&print_mutex);
        cout << "Philosopher " << id << " is thinking" << endl;
        pthread_mutex_unlock(&print_mutex);

        sleep(1);

        sem_wait(&room);

        pthread_mutex_lock(&chopstick[id]);
        pthread_mutex_lock(&chopstick[(id + 1) % N]);

        // Eating
        pthread_mutex_lock(&print_mutex);
        cout << "Philosopher " << id << " is eating" << endl;
        pthread_mutex_unlock(&print_mutex);

        sleep(1);

        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id + 1) % N]);

        sem_post(&room);
    }

    return NULL;
}

int main()
{
    pthread_t ph[N];
    int ids[N];

    sem_init(&room, 0, N - 1);

    // Initialize chopsticks
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Initialize print mutex
    pthread_mutex_init(&print_mutex, NULL);

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < N; i++)
    {
        pthread_join(ph[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_destroy(&chopstick[i]);
    }

    pthread_mutex_destroy(&print_mutex);

    sem_destroy(&room);

    return 0;
}/*1. Basic Scenario

Imagine:

5 philosophers sitting around a circular table

Between every two philosophers there is:

1 chopstick

Each philosopher needs:

2 chopsticks

to eat.

Problem

A philosopher alternates between:

Thinking
Eating

But:

Chopsticks are shared resources.
Only one philosopher can use a chopstick at a time.
2. OS Analogy
Dining Philosophers	Operating System
Philosopher	Process/Thread
Chopstick	Resource
Eating	Using resource
Thinking	Idle/processing
Picking chopsticks	Resource allocation
3. Core Synchronization Problem

Suppose all philosophers do this simultaneously:

Pick left chopstick
Wait for right chopstick

Then:

Everyone holds one chopstick
Nobody gets second chopstick

System freezes.

This is called:

Deadlock
4. Deadlock Conditions

Dining philosophers demonstrates the 4 Coffman conditions:

(A) Mutual Exclusion

Only one philosopher can use a chopstick.

Implemented using:

pthread_mutex_t chopstick[N];
(B) Hold and Wait

Philosopher holds one chopstick while waiting for another.

(C) No Preemption

Chopstick cannot be forcibly taken away.

(D) Circular Wait

Each philosopher waits for next philosopher’s chopstick.

Example:

P0 waits for P1
P1 waits for P2
P2 waits for P3
P3 waits for P4
P4 waits for P0
5. Your Solution’s Concept

Your code prevents deadlock using:

sem_t room;
6. Room Semaphore

Initialized as:

sem_init(&room, 0, N - 1);

Meaning:

Only 4 philosophers allowed to try eating at once

when N = 5.

Why This Prevents Deadlock

If only 4 philosophers enter:

At least one philosopher remains outside

So one chopstick pair remains available.

Hence circular waiting breaks.

Deadlock avoided.

7. Chopsticks as Mutexes
pthread_mutex_lock(&chopstick[id]);

Locks left chopstick.

pthread_mutex_lock(&chopstick[(id + 1) % N]);

Locks right chopstick.

Why Mutex?

Mutex ensures:

Only one philosopher uses chopstick at a time

This provides:

Mutual Exclusion
8. Philosopher Execution Flow
Step 1: Thinking
cout << "thinking";

No resources used.

Step 2: Enter Room
sem_wait(&room);

Checks if philosopher can attempt eating.

Step 3: Pick Left Chopstick
pthread_mutex_lock(&chopstick[id]);
Step 4: Pick Right Chopstick
pthread_mutex_lock(&chopstick[(id + 1) % N]);

Now philosopher has both resources.

Step 5: Eat
cout << "eating";
Step 6: Release Chopsticks
pthread_mutex_unlock(...)

Resources become available.

Step 7: Leave Room
sem_post(&room);

Another philosopher may now try eating.

9. Why Threads Are Used
pthread_create()

creates concurrent philosophers.

This simulates:

Concurrent processes in OS

OS scheduler switches CPU among them.

10. Why Output Order Changes

Threads execute independently.

OS performs:

Context Switching

So order is unpredictable.

11. Infinite Loop
while(true)

means philosophers continuously:

Think → Eat → Think → Eat

simulating an ongoing operating system.

12. What This Program Demonstrates

This program demonstrates:

Process synchronization
Deadlock prevention
Mutual exclusion
Resource allocation
Concurrency
Semaphore usage
Thread scheduling
13. Real-Life OS Examples

Dining Philosophers resembles:

Database Locks

Multiple transactions waiting for resources.

Printer Allocation

Processes waiting for printers/devices.

File Access

Processes requesting exclusive file access.*/
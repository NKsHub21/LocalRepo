#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;

int readcount = 0;

void* reader(void* arg)
{
    int id = *(int*)arg;

    printf("Reader %d wants to read\n", id);

    pthread_mutex_lock(&mutex);
    readcount++;

    if(readcount == 1)
    {
        printf("First reader blocking writer\n");
        sem_wait(&wrt);
    }

    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(2);

    pthread_mutex_lock(&mutex);
    readcount--;

    if(readcount == 0)
    {
        printf("Last reader allowing writer\n");
        sem_post(&wrt);
    }

    pthread_mutex_unlock(&mutex);

    printf("Reader %d finished reading\n", id);

    return NULL;
}

void* writer(void* arg)
{
    int id = *(int*)arg;

    printf("Writer %d wants to write\n", id);

    sem_wait(&wrt);

    printf("Writer %d is writing\n", id);
    sleep(3);

    printf("Writer %d finished writing\n", id);

    sem_post(&wrt);

    return NULL;
}

int main()
{
    pthread_t r1,r2,w1;

    int a=1,b=2,c=1;

    sem_init(&wrt,0,1);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&r1,NULL,reader,&a);
    pthread_create(&r2,NULL,reader,&b);
    pthread_create(&w1,NULL,writer,&c);

    pthread_join(r1,NULL);
    pthread_join(r2,NULL);
    pthread_join(w1,NULL);

    return 0;
}
  /*  program implements the Readers–Writers Problem in Operating Systems using:

pthread → threads
semaphore → synchronization
mutex → protect shared variable
Core OS Concept

The Readers–Writers problem is a synchronization problem where:

Multiple readers can read simultaneously.
Only one writer can write at a time.
No reader should read while writer is writing.
Shared Resource

The shared resource can be:

Database
File
Memory
Shared Data

Readers only read data.

Writers modify data.

Important Rule
Many Readers Allowed Together
Only One Writer Allowed
Components in Your Code
1. Semaphore
sem_t wrt;

wrt controls writer access.

Value meanings:

wrt = 1 → resource free
wrt = 0 → resource busy
2. Mutex
pthread_mutex_t mutex;

Protects:

readcount

because multiple readers modify it simultaneously.

3. readcount
int readcount = 0;

Tracks number of active readers.

Example:

readcount = 2

means 2 readers currently reading.

Reader Function Concept
Step 1
pthread_mutex_lock(&mutex);

Locks access to readcount.

Step 2
readcount++;

Reader enters.

Step 3
if(readcount == 1)

If first reader enters:

Block writers

using:

sem_wait(&wrt);
Why Only First Reader?

Suppose:

Reader 1 enters
Reader 2 enters
Reader 3 enters

Only Reader 1 locks writer.

Other readers directly read simultaneously.

This improves efficiency.

Step 4
pthread_mutex_unlock(&mutex);

Allow other readers to update readcount.

Step 5
Reader is reading

Multiple readers can reach here together.

Step 6

After reading:

readcount--;

Reader leaves.

Step 7
if(readcount == 0)

If last reader exits:

Allow writer

using:

sem_post(&wrt);
Writer Function Concept
Step 1
sem_wait(&wrt);

Writer requests exclusive access.

If readers active:

Writer waits
Step 2
Writer is writing

Now no reader or writer can access resource.

Step 3
sem_post(&wrt);

Writer releases resource.

Technical OS Behavior
Readers Section
Reader 1 enters
↓
Locks writer
↓
Reader 2 enters simultaneously
↓
Both read together
Writer Section
Writer waits until all readers finish
↓
Writer gets exclusive access
↓
Writes alone
Critical Section

Shared variables:

readcount
shared data

must be protected.

Mutex ensures:

No race condition on readcount
Why Semaphore + Mutex Both Needed
Mutex

Protects:

readcount variable
Semaphore

Controls:

access to shared resource
Real-Life Examples
Readers
Students reading library book
Multiple users viewing webpage
Applications reading database
Writers
Updating database
Editing file
Bank transaction update
Example Execution Flow

Possible output:

Reader 1 wants to read
First reader blocking writer

Reader 1 is reading
Reader 2 is reading

Writer 1 wants to write

Reader 1 finished reading
Last reader allowing writer

Reader 2 finished reading

Writer 1 is writing
Writer 1 finished writing
OS Concepts Demonstrated

This program demonstrates:

Process synchronization
Mutual exclusion
Semaphore synchronization
Reader priority
Critical section handling
Concurrent thread execution
Which Readers-Writers Version?

Your code implements:

First Readers-Writers Problem
(Readers Preference)

Meaning:

Readers are given priority over writers

So if readers continuously arrive, writer may starve.*/
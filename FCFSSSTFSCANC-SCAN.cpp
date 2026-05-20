#include <iostream>
using namespace std;

void fcfs(int req[], int n, int head)
{
    int seek = 0;

    for(int i=0;i<n;i++)
    {
        seek += abs(req[i] - head);
        head = req[i];
    }

    cout<<"FCFS Seek Time: "<<seek<<endl;
}

void sstf(int req[], int n, int head)
{
    int visited[50]={0};
    int seek = 0;

    for(int i=0;i<n;i++)
    {
        int min = 9999, pos = -1;

        for(int j=0;j<n;j++)
        {
            if(!visited[j] && abs(req[j]-head) < min)
            {
                min = abs(req[j]-head);
                pos = j;
            }
        }

        seek += min;
        head = req[pos];
        visited[pos] = 1;
    }

    cout<<"SSTF Seek Time: "<<seek<<endl;
}

void scan(int req[], int n, int head)
{
    int seek = 0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(req[j] > req[j+1])
            {
                int t = req[j];
                req[j] = req[j+1];
                req[j+1] = t;
            }
        }
    }

    int i;
    for(i=0;i<n;i++)
        if(req[i] > head) break;

    for(int j=i;j<n;j++)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    for(int j=i-1;j>=0;j--)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    cout<<"SCAN Seek Time: "<<seek<<endl;
}

void cscan(int req[], int n, int head)
{
    int seek = 0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(req[j] > req[j+1])
            {
                int t = req[j];
                req[j] = req[j+1];
                req[j+1] = t;
            }
        }
    }

    int i;
    for(i=0;i<n;i++)
        if(req[i] > head) break;

    for(int j=i;j<n;j++)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    seek += abs(head - 0);
    head = 0;

    for(int j=0;j<i;j++)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    cout<<"C-SCAN Seek Time: "<<seek<<endl;
}

int main()
{
    int n, head, req[50];

    cout<<"Enter number of requests: ";
    cin>>n;

    cout<<"Enter request queue: ";
    for(int i=0;i<n;i++)
        cin>>req[i];

    cout<<"Enter initial head position: ";
    cin>>head;

    fcfs(req,n,head);
    sstf(req,n,head);
    scan(req,n,head);
    cscan(req,n,head);

    return 0;
}
/*ode:
#include <iostream>
using namespace std;

void fcfs(int req[], int n, int head)
{
    int seek = 0;

    for(int i=0;i<n;i++)
    {
        seek += abs(req[i] - head);
        head = req[i];
    }

    cout<<"FCFS Seek Time: "<<seek<<endl;
}

void sstf(int req[], int n, int head)
{
    int visited[50]={0};
    int seek = 0;

    for(int i=0;i<n;i++)
    {
        int min = 9999, pos = -1;

        for(int j=0;j<n;j++)
        {
            if(!visited[j] && abs(req[j]-head) < min)
            {
                min = abs(req[j]-head);
                pos = j;
            }
        }

        seek += min;
        head = req[pos];
        visited[pos] = 1;
    }

    cout<<"SSTF Seek Time: "<<seek<<endl;
}

void scan(int req[], int n, int head)
{
    int seek = 0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(req[j] > req[j+1])
            {
                int t = req[j];
                req[j] = req[j+1];
                req[j+1] = t;
            }
        }
    }

    int i;
    for(i=0;i<n;i++)
        if(req[i] > head) break;

    for(int j=i;j<n;j++)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    for(int j=i-1;j>=0;j--)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    cout<<"SCAN Seek Time: "<<seek<<endl;
}

void cscan(int req[], int n, int head)
{
    int seek = 0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(req[j] > req[j+1])
            {
                int t = req[j];
                req[j] = req[j+1];
                req[j+1] = t;
            }
        }
    }

    int i;
    for(i=0;i<n;i++)
        if(req[i] > head) break;

    for(int j=i;j<n;j++)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    seek += abs(head - 0);
    head = 0;

    for(int j=0;j<i;j++)
    {
        seek += abs(req[j] - head);
        head = req[j];
    }

    cout<<"C-SCAN Seek Time: "<<seek<<endl;
}

int main()
{
    int n, head, req[50];

    cout<<"Enter number of requests: ";
    cin>>n;

    cout<<"Enter request queue: ";
    for(int i=0;i<n;i++)
        cin>>req[i];

    cout<<"Enter initial head position: ";
    cin>>head;

    fcfs(req,n,head);
    sstf(req,n,head);
    scan(req,n,head);
    cscan(req,n,head);

    return 0;
}
*/
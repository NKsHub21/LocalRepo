#include <iostream>
using namespace std;

struct Process {
    int id, at, bt, priority;
    int wt, ct, tat;
};

int main() {
    int n, choice;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[10];

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time for P" << p[i].id << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time for P" << p[i].id << ": ";
        cin >> p[i].bt;
    }

    cout << "\n1. FCFS\n2. SJF\n3. Priority\n4. Preemptive Priority\nEnter choice: ";
    cin >> choice;

    

    switch(choice) {

        case 1:
{
    // Sort according to Arrival Time
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    float avgwt = 0, avgtat = 0;

    for(int i = 0; i < n; i++) {

        if(time < p[i].at)
            time = p[i].at;   // CPU idle case

        p[i].wt = time - p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    cout << "\nProcess  AT  BT  WT  CT  TAT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "       "
             << p[i].at << "   "
             << p[i].bt << "   "
             << p[i].wt << "   "
             << p[i].ct << "   "
             << p[i].tat << endl;
    }

    cout << "\nAverage Waiting Time: " << avgwt/n;
    cout << "\nAverage Turnaround Time: " << avgtat/n;

    // Gantt Chart
    cout << "\n\nGantt Chart:\n|";
    for(int i = 0; i < n; i++)
        cout << " P" << p[i].id << " |";

    cout << "\n0";
    for(int i = 0; i < n; i++)
        cout << "    " << p[i].ct;

    break;
}

        case 2:
          
  
{
    int completed = 0, time = 0;
    bool done[10] = {false};
    int order[10];
    int k = 0;

    while(completed < n) {
        int idx = -1;
        int minBT = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !done[i] && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if(idx == -1) {
            time++;
        } else {
            p[idx].wt = time - p[idx].at;
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            done[idx] = true;
            order[k++] = idx;
            completed++;
        }
    }

    float avgwt = 0, avgtat = 0;

    cout << "\nProcess  AT  BT  WT  CT  TAT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "       "
             << p[i].at << "   "
             << p[i].bt << "   "
             << p[i].wt << "   "
             << p[i].ct << "   "
             << p[i].tat << endl;

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << avgwt/n;
    cout << "\nAverage Turnaround Time: " << avgtat/n;

    cout << "\n\nGantt Chart:\n|";
    for(int i = 0; i < n; i++)
        cout << " P" << p[order[i]].id << " |";

    cout << "\n0";
    for(int i = 0; i < n; i++)
        cout << "    " << p[order[i]].ct;

    return 0;
}

       case 3:
{
    for(int i = 0; i < n; i++) {
        cout << "Enter Priority for P" << p[i].id << ": ";
        cin >> p[i].priority;
    }

    int type;
    cout << "\n1. Higher number = Higher priority";
    cout << "\n2. Lower number = Higher priority";
    cout << "\nEnter choice: ";
    cin >> type;

    int completed = 0, time = 0;
    bool done[10] = {false};
    int order[10];
    int k = 0;

    while(completed < n) {
        int idx = -1;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !done[i]) {

                if(idx == -1)
                    idx = i;
                else {
                    if(type == 1) {
                        if(p[i].priority > p[idx].priority)
                            idx = i;
                    } else {
                        if(p[i].priority < p[idx].priority)
                            idx = i;
                    }
                }
            }
        }

        if(idx == -1) {
            time++;
        } else {
            p[idx].wt = time - p[idx].at;
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            done[idx] = true;
            order[k++] = idx;
            completed++;
        }
    }

    float avgwt = 0, avgtat = 0;

    cout << "\nProcess  AT  BT  Priority  WT  CT  TAT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "       "
             << p[i].at << "   "
             << p[i].bt << "   "
             << p[i].priority << "        "
             << p[i].wt << "   "
             << p[i].ct << "   "
             << p[i].tat << endl;

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << avgwt/n;
    cout << "\nAverage Turnaround Time: " << avgtat/n;

    cout << "\n\nGantt Chart:\n|";
    for(int i = 0; i < n; i++)
        cout << " P" << p[order[i]].id << " |";

    cout << "\n0";
    for(int i = 0; i < n; i++)
        cout << "    " << p[order[i]].ct;

    return 0;
}
case 4:
{
    for(int i = 0; i < n; i++)
    {
        cout << "Enter Priority for P" << p[i].id << ": ";
        cin >> p[i].priority;
    }

    int type;
    cout << "\n1. Higher number = Higher priority";
    cout << "\n2. Lower number = Higher priority";
    cout << "\nEnter choice: ";
    cin >> type;

    int completed = 0, time = 0;
    int remaining[10];
    int gantt[100];
    int tindex = 0;

    for(int i = 0; i < n; i++)
        remaining[i] = p[i].bt;

    float avgwt = 0, avgtat = 0;

    while(completed < n)
    {
        int idx = -1;

        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time && remaining[i] > 0)
            {
                if(idx == -1)
                    idx = i;
                else
                {
                    if(type == 1)
                    {
                        if(p[i].priority > p[idx].priority)
                            idx = i;
                    }
                    else
                    {
                        if(p[i].priority < p[idx].priority)
                            idx = i;
                    }
                }
            }
        }

        if(idx == -1)
        {
            gantt[tindex++] = -1;
            time++;
        }
        else
        {
            gantt[tindex++] = idx;
            remaining[idx]--;
            time++;

            if(remaining[idx] == 0)
            {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                avgwt += p[idx].wt;
                avgtat += p[idx].tat;
            }
        }
    }

    cout << "\nGantt Chart:\n|";
    for(int i = 0; i < tindex; i++)
    {
        if(gantt[i] == -1)
            cout << " Idle |";
        else
            cout << " P" << p[gantt[i]].id << " |";
    }

    cout << "\n0";
    for(int i = 1; i <= tindex; i++)
        cout << "    " << i;

    cout << "\n\nProcess  AT  BT  Priority  WT  CT  TAT\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "       "
             << p[i].at << "   "
             << p[i].bt << "   "
             << p[i].priority << "        "
             << p[i].wt << "   "
             << p[i].ct << "   "
             << p[i].tat << endl;
    }

    cout << "\nAverage Waiting Time: " << avgwt/n;
    cout << "\nAverage Turnaround Time: " << avgtat/n;

    break;
}
    }
return 0;
}

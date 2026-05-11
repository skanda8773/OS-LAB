#include <stdio.h>

struct Process
{
    int at, bt, rt;
    int ct, tat, wt, resp;
    int visited;
};

int main()
{
    struct Process p[20];
    int queue[100];

    int n, tq;
    int front = 0, rear = 0;
    int time = 0, completed = 0;

    float avgwt = 0, avgtat = 0, avgrt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);

        p[i].rt = p[i].bt;
        p[i].resp = -1;
        p[i].visited = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    queue[rear++] = 0;
    p[0].visited = 1;

    while(completed != n)
    {
        int i = queue[front++];

        if(p[i].resp == -1)
            p[i].resp = time - p[i].at;

        if(p[i].rt > tq)
        {
            time += tq;
            p[i].rt -= tq;
        }
        else
        {
            time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = time;
            completed++;
        }

        for(int j = 0; j < n; j++)
        {
            if(p[j].at <= time && p[j].visited == 0)
            {
                queue[rear++] = j;
                p[j].visited = 1;
            }
        }

        if(p[i].rt > 0)
            queue[rear++] = i;

        printf("\nReady Queue: ");
        for(int j = front; j <rear; j++)
            printf("P%d ", queue[j] + 1);
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avgwt += p[i].wt;
        avgtat += p[i].tat;
        avgrt += p[i].resp;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].resp);
    }

    printf("\nAverage Turnaround Time = %.2f", avgtat / n);
    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Response Time = %.2f\n", avgrt / n);

    return 0;
}

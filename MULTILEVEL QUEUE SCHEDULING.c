#include <stdio.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int type;   // 0 = System, 1 = User
    int ct;
    int tat;
    int wt;
};

int main()
{
    struct Process p[20];

    int n, i, time = 0;
    int sys[20], user[20];
    int sc = 0, uc = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        p[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Type (0=System, 1=User): ");
        scanf("%d", &p[i].type);

        if(p[i].type == 0)
            sys[sc++] = i;
        else
            user[uc++] = i;
    }

    printf("\nGantt Chart:\n");
    printf("%d ", time);

    // Execute System Processes first
    for(i = 0; i < sc; i++)
    {
        int k = sys[i];

        if(time < p[k].at)
            time = p[k].at;

        printf("| P%d ", p[k].pid);

        time += p[k].bt;
        p[k].ct = time;

        printf("| %d ", time);

        p[k].tat = p[k].ct - p[k].at;
        p[k].wt = p[k].tat - p[k].bt;
    }

    // Execute User Processes next
    for(i = 0; i < uc; i++)
    {
        int k = user[i];

        if(time < p[k].at)
            time = p[k].at;

        printf("| P%d ", p[k].pid);

        time += p[k].bt;
        p[k].ct = time;

        printf("| %d ", time);

        p[k].tat = p[k].ct - p[k].at;
        p[k].wt = p[k].tat - p[k].bt;
    }

    printf("\n");

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid, p[i].at, p[i].bt, p[i].type,
        p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}

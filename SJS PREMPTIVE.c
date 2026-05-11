#include <stdio.h>

struct process {
    int pid;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int rt;     // Remaining Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int st;     // Start Time
    int visited;
};

int main() {

    int n, time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);

        p[i].rt = p[i].bt;
        p[i].visited = 0;
    }

    while(completed != n) {

        int idx = -1;
        int min = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].rt < min) {
                    min = p[i].rt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {

            if(p[idx].visited == 0) {
                p[idx].st = time;
                p[idx].visited = 1;
            }

            p[idx].rt--;
            time++;

            if(p[idx].rt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                avg_tat += p[idx].tat;
                avg_wt += p[idx].wt;
                avg_rt += (p[idx].st - p[idx].at);

                completed++;
            }

        } else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt,
               p[i].st - p[i].at);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Response Time = %.2f\n", avg_rt / n);

    return 0;
}

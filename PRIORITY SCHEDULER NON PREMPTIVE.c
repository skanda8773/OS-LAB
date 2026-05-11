#include <stdio.h>

struct process {
    int pid;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int pr;     // Priority
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int rt;     // Response Time
    int finished;
};

int main() {

    int n, time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter Arrival Time, Burst Time and Priority for P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);

        p[i].finished = 0;
    }

    while(completed < n) {

        int idx = -1;
        int highest_priority = 9999;

        for(int i = 0; i < n; i++) {

            if(p[i].at <= time && p[i].finished == 0) {

                if(p[i].pr < highest_priority) {
                    highest_priority = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1) {

            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt;

            avg_tat += p[idx].tat;
            avg_wt += p[idx].wt;
            avg_rt += p[idx].rt;

            p[idx].finished = 1;
            completed++;
        }
        else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Response Time = %.2f\n", avg_rt / n);

    return 0;
}

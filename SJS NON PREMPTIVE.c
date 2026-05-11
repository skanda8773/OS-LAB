#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int response;
    int finished;
};

int main() {
    int n, time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];


    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].finished = 0;
    }

    while(completed < n) {
        int idx = -1;
        int minBurst = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].arrival <= time && p[i].finished == 0) {
                if(p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            time += p[idx].burst;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].response = p[idx].waiting; // same in non-preemptive
            p[idx].finished = 1;

            avg_tat += p[idx].turnaround;
            avg_wt += p[idx].waiting;
            avg_rt += p[idx].response;

            completed++;
        }
        else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid,
            p[i].arrival,
            p[i].burst,
            p[i].completion,
            p[i].turnaround,
            p[i].waiting,
            p[i].response);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Response Time = %.2f\n", avg_rt / n);

    return 0;
}

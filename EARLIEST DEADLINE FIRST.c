#include <stdio.h>
#define MAX 10

int main()
{
    int n, i;
    int arrival[MAX], deadline[MAX];
    int execution[MAX], remaining[MAX];
    int completed[MAX] = {0};
    float U = 0.0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrival[i]);
        printf("Execution Time (C): ");
        scanf("%d", &execution[i]);
        printf("Deadline (D): ");
        scanf("%d", &deadline[i]);
        remaining[i] = execution[i];
        U += (float)execution[i] / deadline[i];
    }
    printf("\nCPU Utilization (U) = %.2f\n", U);
    if(U > 1.0) {
        printf("Scheduling not feasible (deadlines may be missed)\n");
        return 0;
    } else {
        printf("Scheduling feasible\n");
    }
    int t = 0, done = 0;
    printf("\n--- Execution Start ---\n");
    while(done < n)
    {
        int idx = -1;
        int min_deadline = 9999;
        for(i = 0; i < n; i++)
        {
            if(arrival[i] <= t && !completed[i])
            {
                if(deadline[i] < min_deadline)
                {
                    min_deadline = deadline[i];
                    idx = i;
                }
            }
        }
        if(idx == -1)
        {
            printf("Time %d: CPU Idle\n", t);
            t++;
            continue;
        }
        printf("Time %d: Running P%d\n", t, idx + 1);
        remaining[idx]--;
        if(remaining[idx] == 0)
        {
            completed[idx] = 1;
            done++;
            printf("P%d completed at time %d\n", idx + 1, t + 1);
        }
        t++;
    }
    printf("\n All Processes Completed \n");
    return 0;
}

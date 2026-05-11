#include <stdio.h>
#define MAX 10
#define TIME_QUANTUM 10.0

int main()
{
    int n, i;
    int weight[MAX];
    float remaining_time[MAX];
    int completed[MAX] = {0};
    float total_weight = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i + 1);
        printf("Enter weight: ");
        scanf("%d", &weight[i]);
        printf("Enter burst time: ");
        scanf("%f", &remaining_time[i]);
        total_weight += weight[i];
    }
    printf("\n Execution Start\n");
    while(1)
    {
        int all_done = 1;
        for(i = 0; i < n; i++)
        {
            if(!completed[i])
            {
                all_done = 0;
                float time_slice = (weight[i] / total_weight) * TIME_QUANTUM;
                if(remaining_time[i] < time_slice)
                {
                    time_slice = remaining_time[i];
                }
                printf("Running P%d for %.2f units\n", i + 1, time_slice);
                remaining_time[i] -= time_slice;
                if(remaining_time[i] <= 0)
                {
                    completed[i] = 1;
                    total_weight -= weight[i];
                    printf("P%d completed\n", i + 1);
                }
            }
        }
        if(all_done)
            break;
    }
    printf("\n All Processes Completed \n");
    return 0;
}

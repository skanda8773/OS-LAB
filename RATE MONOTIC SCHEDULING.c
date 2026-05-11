#include <stdio.h>
#include <math.h>

#define MAX_TASKS 10
#define MAX_TIME 50

// Structure for a task
typedef struct {
    int id;
    int C;  // Execution time
    int P;  // Period
    int remaining_time;
    int next_arrival;
} Task;

// Function to sort tasks by period (ascending)
void sortByPeriod(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].P > tasks[j].P) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Task tasks[MAX_TASKS];
    int time = 0;
    float cpu_util = 0;

    int gantt[MAX_TIME]; // To store execution timeline

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Input tasks
    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        tasks[i].id = i + 1;

        printf("Execution Time (C): ");
        scanf("%d", &tasks[i].C);

        printf("Period (P): ");
        scanf("%d", &tasks[i].P);

        tasks[i].remaining_time = 0;
        tasks[i].next_arrival = 0;

        cpu_util += (float)tasks[i].C / tasks[i].P;
    }

    // Sort tasks by priority
    sortByPeriod(tasks, n);

    printf("\n--- Scheduling Start ---\n");

    // Scheduling loop
    while (time < MAX_TIME) {

        // Step 1: Check arrivals
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].P;
            }
        }

        // Step 2: Select highest priority task
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                current = i;
                break;
            }
        }

        // Step 3: Execute
        if (current != -1) {
            printf("Time %d: Task T%d is running\n", time, tasks[current].id);
            tasks[current].remaining_time--;
            gantt[time] = tasks[current].id; // store task id
        } else {
            printf("Time %d: CPU Idle\n", time);
            gantt[time] = 0; // idle
        }

        // Step 4: Deadline check
        for (int i = 0; i < n; i++) {
            if (time >= tasks[i].next_arrival &&
                tasks[i].remaining_time > 0) {
                printf("Deadline Missed for Task T%d at time %d\n",
                       tasks[i].id, time);
            }
        }

        time++;
    }

    printf("\n--- Scheduling End ---\n");

    // Print Gantt Chart
    printf("\nGantt Chart:\n");

    // Top bar
    for (int i = 0; i < MAX_TIME; i++)
        printf("----");
    printf("\n|");

    // Task execution row
    for (int i = 0; i < MAX_TIME; i++) {
        if (gantt[i] == 0)
            printf(" I |");  // Idle
        else
            printf("T%d |", gantt[i]);
    }

    printf("\n");

    // Bottom bar
    for (int i = 0; i < MAX_TIME; i++)
        printf("----");

    printf("\n");

    // Time indices
    for (int i = 0; i <= MAX_TIME; i++)
        printf("%-4d", i);

    printf("\n");

    // CPU Utilization
    printf("\nCPU Utilization = %.2f\n", cpu_util);

    // RMS Bound
    float bound = n * (pow(2, (float)1/n) - 1);
    printf("RMS Utilization Bound = %.2f\n", bound);

    if (cpu_util <= bound)
        printf("Schedulable under RMS\n");
    else
        printf("May NOT be schedulable under RMS\n");

    return 0;
}

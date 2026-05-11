#include <stdio.h>

#define P 4
#define R 3

struct System {
    int allocation[P][R];
    int request[P][R];
    int available[R];
};

int main() {
    struct System sys;
    int work[R], finish[P] = {0}, safeSeq[P];
    int count = 0;
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &sys.allocation[i][j]);
    printf("Enter Request Matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &sys.request[i][j]);
    printf("Enter Available Resources:\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &sys.available[i]);
    for (int i = 0; i < R; i++)
        work[i] = sys.available[i];
    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (sys.request[i][j] > work[j])
                        break;
                }
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += sys.allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            break;
    }
    int deadlock = 0;
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            deadlock = 1;
            printf("Process %d is in deadlock\n", i);
        }
    }
    if (!deadlock) {
        printf("No deadlock\nSafe sequence: ");
        for (int i = 0; i < P; i++)
            printf("P%d ", safeSeq[i]);
    }
    return 0;
}

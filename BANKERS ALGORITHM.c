#include <stdio.h>
#define MAX 10
int n, m;
int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
int available[MAX];

//safety algorithm

int isSafe() {
    int work[MAX], finish[MAX] = {0}, safeSeq[MAX];
    for (int i = 0; i < m; i++)
        work[i] = available[i];
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int possible = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            break;
    }
    if (count == n) {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);
            if (i != n - 1)
                printf(" -> ");
        }
        printf("\n");
        return 1;
    }
    else {
        printf("\nSystem is NOT in SAFE state.\n");
        return 0;
    }
}

// Resource Request Algorithm

void requestResources() {
    int p, request[MAX];
    printf("\nEnter process number: ");
    scanf("%d", &p);
    printf("Enter request vector:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);
    for (int i = 0; i < m; i++) {
        if (request[i] > need[p][i]) {
            printf("\nError: Process exceeded maximum claim.\n");
            return;
        }
    }
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("\nResources not available. Process must wait.\n");
            return;
        }
    }
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }
    printf("\nChecking for safe state...\n");
    if (isSafe()) {
        printf("Request can be granted.\n");
    } else {
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[p][i] -= request[i];
            need[p][i] += request[i];
        }
        printf("Request cannot be granted. State restored.\n");
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    isSafe();
    requestResources();
    return 0;
}

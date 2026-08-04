#include <stdio.h>

int main() {
    int i, n, t, bu[10], rem_bt[10], wt[10], tat[10], ct[10];
    int time = 0, done;
    float awt = 0, att = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bu[i]);
        rem_bt[i] = bu[i];   // remaining burst time
    }

    printf("Enter the time slice: ");
    scanf("%d", &t);

    // Round Robin scheduling
    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > t) {
                    time += t;
                    rem_bt[i] -= t;
                } else {
                    time += rem_bt[i];
                    tat[i] = time;   // completion time for process i
                    rem_bt[i] = 0;
                }
            }
        }
    } while (!done);

    // Calculate waiting time and averages
    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - bu[i];
        awt += wt[i];
        att += tat[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bu[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", awt / n);
    printf("\nAverage Turnaround Time: %.2f\n", att / n);

    return 0;
}

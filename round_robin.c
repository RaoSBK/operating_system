#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n];
    int wt[n], tat[n];

    printf("Enter Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Remaining Time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    while (completed < n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;

                if (rt[i] > tq) {
                    printf("P%d executes from %d to %d\n",
                           i + 1, time, time + tq);

                    time += tq;
                    rt[i] -= tq;
                } else {
                    printf("P%d executes from %d to %d\n",
                           i + 1, time, time + rt[i]);

                    time += rt[i];

                    wt[i] = time - bt[i];
                    tat[i] = wt[i] + bt[i];

                    rt[i] = 0;
                    completed++;
                }
            }
        }

        if (done)
            break;
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nProcess\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}
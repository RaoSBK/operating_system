
#include <stdio.h>

int main()
{
    int n, i, j;
    int pid[20], bt[20], priority[20];
    int wt[20], tat[20];
    int temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("Enter burst time of P%d: ", pid[i]);
        scanf("%d", &bt[i]);

        printf("Enter priority of P%d: ", pid[i]);
        scanf("%d", &priority[i]);
    }

    // Sort processes according to priority
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (priority[i] > priority[j])
            {
                // Swap priority
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process ID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    wt[0] = 0;

    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display results
    printf("\nPID\tBT\tPriority\tWT\tTAT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t\t%d\t%d\n",
               pid[i], bt[i], priority[i], wt[i], tat[i]);
    }

    avg_wt = avg_wt / n;
    avg_tat = avg_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}









//Sample input
// Enter number of processes: 3
// Enter burst time of P1: 5
// Enter priority of P1: 3
// Enter burst time of P2: 2
// Enter priority of P2: 1
// Enter burst time of P3: 4
// Enter priority of P3: 2
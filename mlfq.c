
#include <stdio.h>

int main()
{
    int n, i, time = 0;
    int at[20], bt[20], rt[20];
    int ct[20], tat[20], wt[20];
    int queue[20] = {0};

    int tq1 = 2, tq2 = 4;
    int completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for(i = 0; i < n; i++)
    {
        printf("\nEnter Arrival Time of P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time of P%d: ", i + 1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    // MLFQ Scheduling
    while(completed < n)
    {
        int executed = 0;

        // Queue 1: Round Robin (Time Quantum = 2)
        for(i = 0; i < n; i++)
        {
            if(queue[i] == 0 && rt[i] > 0 && at[i] <= time)
            {
                executed = 1;

                if(rt[i] > tq1)
                {
                    time += tq1;
                    rt[i] -= tq1;
                    queue[i] = 1;
                }
                else
                {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
        }

        // Queue 2: Round Robin (Time Quantum = 4)
        for(i = 0; i < n; i++)
        {
            if(queue[i] == 1 && rt[i] > 0 && at[i] <= time)
            {
                executed = 1;

                if(rt[i] > tq2)
                {
                    time += tq2;
                    rt[i] -= tq2;
                    queue[i] = 2;
                }
                else
                {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
        }

        // Queue 3: FCFS
        for(i = 0; i < n; i++)
        {
            if(queue[i] == 2 && rt[i] > 0 && at[i] <= time)
            {
                executed = 1;

                time += rt[i];
                rt[i] = 0;
                ct[i] = time;
                completed++;
            }
        }

        // CPU is idle if no process is ready
        if(!executed)
            time++;
    }

    // Display results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    float totalTAT = 0, totalWT = 0;

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        totalTAT += tat[i];
        totalWT += wt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f",
           totalTAT / n);

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    return 0;
}

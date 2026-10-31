
#include <stdio.h>

int main()
{
    int n, i, tq = 2;
    int at[20], bt[20], rt[20];
    int ct[20], tat[20], wt[20];
    int queue[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for(i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Queue (1-System / 2-User): ");
        scanf("%d", &queue[i]);

        rt[i] = bt[i];
    }

    int time = 0;
    int completed = 0;

    // Queue 1: Round Robin
    while(1)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(queue[i] == 1 && rt[i] > 0 && at[i] <= time)
            {
                found = 1;

                if(rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
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

        if(!found)
            break;
    }

    // Queue 2: FCFS
    for(i = 0; i < n; i++)
    {
        if(queue[i] == 2)
        {
            if(time < at[i])
                time = at[i];

            time += bt[i];
            ct[i] = time;
            completed++;
        }
    }

    // Calculate TAT and WT
    printf("\nProcess\tAT\tBT\tQueue\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], queue[i],
               ct[i], tat[i], wt[i]);
    }

    return 0;
}

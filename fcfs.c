#include <stdio.h>
#include <conio.h>

int main(){
    int bt[20], wt[20], tat[20], i,n;
    float wtavg, tatavg;

    // clrscr();

    printf("Enter the number of the process--");
    scanf("%d", &n);

    for(i=0; i<n;i++){
        printf("\n Enter Burst time for process %d --", i);
        scanf("%d", &bt[i]);
    }

    wt[0] = wtavg =0;
    tat[0]=tatavg = 0;

    for(i=1; i<n; i++){
        wt[i] = wt[i-1]+bt[i-1];
        tat[i]= tat[i-1]+bt[i];
        wtavg=wtavg+wt[i];
        tatavg = tatavg +tat[i];
    }

    printf("\t Processes \t Burst Time \t Waiting Time \t Turnaround time \n");
    for(i=0; i<n; i++){
        printf("\n \t P%d \t\t %d \t\t%d \t\t%d",i, bt[i], wt[i], tat[i]);
    }

    printf("\n Average Waiting time--%f", wtavg/n);
    printf("\n Average turnaournd Time--%f", tatavg/n);

    return 0;   
    getch();
}
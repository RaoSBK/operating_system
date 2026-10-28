
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, head;
    int request[100], visited[100] = {0};
    int total_seek = 0;
    int min, distance, index;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request sequence:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nDisk head movement:\n");
    printf("%d", head);

    for (int count = 0; count < n; count++)
    {
        min = 999999;
        index = -1;

        // Find the nearest unvisited request
        for (i = 0; i < n; i++)
        {
            if (visited[i] == 0)
            {
                distance = abs(head - request[i]);

                if (distance < min)
                {
                    min = distance;
                    index = i;
                }
            }
        }

        // Move the head to the selected request
        total_seek += min;
        head = request[index];
        visited[index] = 1;

        printf(" -> %d", head);
    }

    printf("\n\nTotal head movement = %d cylinders\n",
           total_seek);

    printf("Average head movement = %.2f cylinders\n",
           (float)total_seek / n);

    return 0;
}

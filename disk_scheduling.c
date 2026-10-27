
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i;
    int request[100];
    int head, total_seek = 0;

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

    for (i = 0; i < n; i++)
    {
        printf("%d -> ", head);

        total_seek += abs(head - request[i]);
        head = request[i];
    }

    printf("%d\n", head);

    printf("\nTotal head movement = %d cylinders\n", total_seek);
    printf("Average head movement = %.2f cylinders\n",
           (float)total_seek / n);

    return 0;
}

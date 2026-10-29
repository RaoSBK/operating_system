
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, head, size, direction;
    int request[100], temp;
    int total_seek = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request sequence:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (number of cylinders): ");
    scanf("%d", &size);

    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    // Sort requests in ascending order
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (request[i] > request[j])
            {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    printf("\nDisk head movement:\n");
    printf("%d", head);

    if (direction == 0)
    {
        // Service requests on the left
        for (i = n - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                total_seek += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }

        // Move to the left disk boundary
        total_seek += head;
        head = 0;
        printf(" -> %d", head);

        // Reverse direction and service remaining requests
        for (i = 0; i < n; i++)
        {
            if (request[i] >= head)
            {
                total_seek += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    }
    else
    {
        // Service requests on the right
        for (i = 0; i < n; i++)
        {
            if (request[i] > head)
            {
                total_seek += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }

        // Move to the right disk boundary
        total_seek += (size - 1) - head;
        head = size - 1;
        printf(" -> %d", head);

        // Reverse direction and service remaining requests
        for (i = n - 1; i >= 0; i--)
        {
            if (request[i] <= head)
            {
                total_seek += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\n\nTotal head movement = %d cylinders\n",
           total_seek);

    return 0;
}

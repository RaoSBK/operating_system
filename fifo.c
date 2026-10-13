
#include <stdio.h>   // Provides printf() and other input/output functions

int fr[3];           // Array representing the three memory frames

// Function declaration: displays the current contents of the frames
void display(void);

int main(void)
{
    // Pages requested by the CPU, in the given order
    int page[12] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};

    int i, j;            // Loop variables
    int flag1 = 0;       // Indicates whether the page is already present
    int flag2 = 0;       // Indicates whether the page was handled
    int pf = 0;          // Counts replacements after frames become full
    int frsize = 3;      // Number of available frames
    int top = 0;         // Next frame position to replace using FIFO

    // Initially, all three frames are empty
    for (i = 0; i < frsize; i++)
    {
        fr[i] = -1;      // -1 means that the frame is empty
    }

    // Process each page in the reference string
    for (j = 0; j < 12; j++)
    {
        flag1 = 0;       // Assume the requested page is absent
        flag2 = 0;       // Assume the page has not been handled

        // Step 1: Check whether the requested page is already in memory
        for (i = 0; i < frsize; i++)
        {
            if (fr[i] == page[j])
            {
                flag1 = 1;   // Page is already present: page hit
                flag2 = 1;   // No insertion or replacement is needed
                break;       // Stop checking the frames
            }
        }

        // Step 2: If absent, search for an empty frame
        if (flag1 == 0)
        {
            for (i = 0; i < frsize; i++)
            {
                if (fr[i] == -1)
                {
                    fr[i] = page[j]; // Load page into the empty frame
                    flag2 = 1;        // Page has been handled
                    break;            // Stop after filling one frame
                }
            }
        }

        // Step 3: If absent and no empty frame exists, replace a page
        if (flag2 == 0)
        {
            fr[top] = page[j]; // Replace the oldest page's frame
            top++;             // Move to the next replacement position
            pf++;              // Count this replacement as a page fault

            // Return to frame 0 after reaching the last frame
            if (top >= frsize)
            {
                top = 0;
            }
        }

        // Step 4: Display the frames after processing this page
        display();
    }

    // The first three page faults filled the initially empty frames.
    // pf counts the subsequent faults that required replacement.
    printf("\nNumber of page faults: %d\n", pf + frsize);

    return 0;
}

// Function to print the current contents of the three frames
void display(void)
{
    int i;

    printf("\n");

    for (i = 0; i < 3; i++)
    {
        printf("%d\t", fr[i]);
    }
}

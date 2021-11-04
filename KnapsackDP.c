#include <stdlib.h>
#include <stdio.h>

int main()
{
    int numInstances;
    scanf("%d", &numInstances);

    for (int i = 0; i < numInstances; i++)
    {
        // get input
        int numJobs;
        int capacity;
        scanf("%d", &numJobs);
        scanf("%d", &capacity);

        // create 2D array
        int** knapsack = malloc(sizeof(int*) * (numJobs + 1));
        knapsack[0] = calloc(capacity + 1, sizeof(int)); // base case

        for (int j = 1; j < numJobs + 1; j++)
        {
            knapsack[j] = malloc(sizeof(int) * (capacity + 1));
            // create row in 2D array

            int weight;
            int value;
            scanf("%d", &weight); // get job input
            scanf("%d", &value);

            for (int k = 0; k < capacity + 1; k++)
            {
                if (weight > k)
                {
                    knapsack[j][k] = knapsack[j-1][k];
                }
                else // k >= weight, k - weight >= 0
                {
                    if (knapsack[j-1][k] >= (knapsack[j-1][k - weight] + value)) // bellman equation
                    {
                        knapsack[j][k] = knapsack[j-1][k];
                    }
                    else
                    {
                        knapsack[j][k] = knapsack[j-1][k - weight] + value;
                    }
                }
            }
        }

        printf("%d\n", knapsack[numJobs][capacity]);

        for (int j = 0; j < numJobs + 1; j++)
        {
            free(knapsack[j]);
        }
        free(knapsack);
    }

    return 0;
}
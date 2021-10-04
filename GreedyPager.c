#include <stdio.h>

int main() 
{
    int numInstances;
    scanf("%d", &numInstances);

    for (int i = 0; i < numInstances; i++) 
    {
        int pageFaults = 0;
        int numPages;
        scanf("%d", &numPages);
        int* cache = malloc(numPages * sizeof(int));

        int spaceNeeded;
        scanf("%d", &spaceNeeded);
        int* pagesToInsert = malloc(spaceNeeded * sizeof(int));

        for (int j = 0; j < spaceNeeded; j++) 
        {
            int temp;
            scanf("%d", &temp);
            pagesToInsert[j] = temp;
        }

        int cacheLength = 0; // keep track of the current length of the cache
        for (int j = 0; j < spaceNeeded; j++) // iterate through input
        { 
            int needToContinue = 0;
            for (int k = 0; k < cacheLength; k++) 
            {
                if (cache[k] == pagesToInsert[j]) 
                {
                    needToContinue = 1;
                    break;
                }
            }

            if (needToContinue == 1) // we have a hit?
                continue;
                
            pageFaults++; // we have a fault
            if (cacheLength == numPages) // cache is full, use greedy heuristic to replace
            {
                int furthestAway = 0;
                int cachePos = 0;
                int furthestFound = 0; // keeps track if one page isn't in the future of the page input

                for (int k = 0; k < numPages; k++) // loop checks elements in cache
                { 
                    int nextHit = 0; // how far away the next hit will be for this page

                    for (int l = j + 1; l < spaceNeeded; l++) // loop iterates through offline input we haven't visited
                    { 
                        if (l == spaceNeeded - 1 && cache[k] != pagesToInsert[l]) 
                        {
                            cachePos = k;
                            furthestFound = 1;
                            break;
                        }

                        nextHit++;
                        if (cache[k] == pagesToInsert[l]) 
                        {
                            if (nextHit > furthestAway) 
                            {
                                furthestAway = nextHit;
                                cachePos = k;
                            }
                            break;
                        }
                    }

                    if (furthestFound == 1)
                        break;
                }

                cache[cachePos] = pagesToInsert[j]; // replace page in cache
            } else // have a miss and cache isn't full yet
            {
                cache[cacheLength] = pagesToInsert[j];
                cacheLength++;
            }
        }

        printf("%d\n", pageFaults);
        pageFaults = 0;
    }

  return 0;
}

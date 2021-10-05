#include <stdio.h>

typedef struct ElementAndNext {
    int pageNumber;
    int nextInstance;
} PageAndInstance;

int main() 
{
    int numInstances;
    scanf("%d", &numInstances);

    for (int i = 0; i < numInstances; i++) 
    {
        int pageFaults = 0;
        int numPages;
        scanf("%d", &numPages);
        PageAndInstance* cache = malloc(numPages * sizeof(PageAndInstance));

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
            int furthestAway = 0; // loop double functions to get furthest away
            int cachePos = 0;
            int needToContinue = 0;
            for (int k = 0; k < cacheLength; k++) 
            {
                cache[k].nextInstance--; // decrement since we're moving forward in page list
                if (cache[k].nextInstance == 0)
                {
                    int howFarInFuture = 0;
                    for (int l = j + 1; l < spaceNeeded; l++)
                    {
                        howFarInFuture++;
                        if (cache[k].pageNumber == pagesToInsert[l])
                        {
                            cache[k].nextInstance = howFarInFuture;
                            break;
                        }
                        else if (l == spaceNeeded - 1)
                        {
                            cache[k].nextInstance = howFarInFuture + 1;
                            break;
                        }
                    }
                }

                if (cache[k].pageNumber == pagesToInsert[j]) // have a hit?
                {
                    needToContinue = 1;
                }

                if (cache[k].nextInstance > furthestAway)
                {
                    cachePos = k;
                    furthestAway = cache[k].nextInstance;
                }
            }

            if (needToContinue == 1) // we have a hit?
                continue;
                
            pageFaults++; // else we have a fault
            if (cacheLength == numPages) // cache is full, use greedy heuristic to replace
            {
                cache[cachePos].pageNumber = pagesToInsert[j]; // already know furthest
            } else // have a miss and cache isn't full yet
            {
                cache[cacheLength].pageNumber = pagesToInsert[j];
                cachePos = cacheLength;
                cacheLength++;
            }

            int howFarInFuture = 0; // get when next element is for one we're adding
            for (int k = j + 1; k < spaceNeeded; k++)
            {
                howFarInFuture++;
                if (cache[cachePos].pageNumber == pagesToInsert[k])
                {
                    cache[cachePos].nextInstance = howFarInFuture;
                    break;
                } else if (k == spaceNeeded - 1)
                {
                    cache[cachePos].nextInstance = howFarInFuture + 1;
                    break; // would leave loop after this anyway, but one less condition to check
                }
            }
        }

        printf("%d\n", pageFaults);
    }

  return 0;
}

#include <iostream>
#include <sstream>

using namespace std;

int main() 
{
    int numInstances;
    cin >> numInstances;

    for (int i = 0; i < numInstances; i++) 
    {
        int pageFaults = 0;
        int numPages;
        cin >> numPages;
        int* cache = new int[numPages];

        int spaceNeeded;
        cin >> spaceNeeded;
        int* pagesToInsert = new int[spaceNeeded];

        string pageNumbers;
        getline(cin, pageNumbers); // first time gets an empty line
        getline(cin, pageNumbers); // this line gets the string of ints

        stringstream newStream(pageNumbers);
        for (int j = 0; j < spaceNeeded; j++) 
        {
            newStream >> pagesToInsert[j];
        }

        int cacheLength = 0; // keep track of the current length of the cache
        for (int j = 0; j < spaceNeeded; j++) // iterate through input
        { 
            bool needToContinue = false;
            for (int k = 0; k < cacheLength; k++) 
            {
                if (cache[k] == pagesToInsert[j]) 
                {
                    needToContinue = true;
                    break;
                }
            }

            if (needToContinue) // we have a hit?
                continue;
                
            pageFaults++; // we have a fault
            if (cacheLength == numPages) // cache is full, use greedy heuristic to replace
            {
                int furthestAway = 0;
                int cachePos = 0;
                bool furthestFound = false; // keeps track if one page isn't in the future of the page input

                for (int k = 0; k < numPages; k++) // loop checks elements in cache
                { 
                    int nextHit = 0; // how far away the next hit will be for this page

                    for (int l = j + 1; l < spaceNeeded; l++) // loop iterates through offline input we haven't visited
                    { 
                        if (l == spaceNeeded - 1 && cache[k] != pagesToInsert[l]) 
                        {
                            cachePos = k;
                            furthestFound = true;
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

                    if (furthestFound)
                        break;
                }

                cache[cachePos] = pagesToInsert[j]; // replace page in cache
            } else // have a miss and cache isn't full yet
            {
                cache[cacheLength] = pagesToInsert[j];
                cacheLength++;
            }
        }

        cout << pageFaults << endl;
        pageFaults = 0;
    }

  return 0;
}

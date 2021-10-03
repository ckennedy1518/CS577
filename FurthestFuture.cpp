#include <iostream>
#include <sstream>

using namespace std;

int main() {
  int numInstances;
  cin >> numInstances;

  for (int i = 0; i < numInstances; i++) {
    int pageFaults = 0;
    int numPages;
    cin >> numPages;
    int* cache = new int[numPages];

    int spaceNeeded;
    cin >> spaceNeeded;
    int* pagesToInsert = new int[spaceNeeded];

    string pageNumbers;
    getline(cin, pageNumbers);  // first time gets an empty line
    getline(cin, pageNumbers);  // this line gets the string of ints

    stringstream newStream(pageNumbers);
    for (int j = 0; j < spaceNeeded; j++) {
      newStream >> pagesToInsert[j];
    }

    int nextEmptySpot = 0;
    for (int j = 0; j < spaceNeeded; j++) {  // iterate through input
      bool needToContinue = false;           // check if we have a hit
      for (int k = 0; k < numPages; k++) {
        if (cache[k] == pagesToInsert[j]) {
          needToContinue = true;
          break;
        }
      }

      if (needToContinue) {
        continue;
      } else if (nextEmptySpot == numPages) {  // cache is full
        pageFaults++;
        int furthestAway = 0;
        int cachePos = 0;
        bool furthestFound =
            false;  // if one element isn't in the future at all

        for (int k = 0; k < numPages; k++) {  // loop checks elements in cache
          int nextHit = 0;

          for (int l = j + 1; l < spaceNeeded;
               l++) {  // loop iterates through rest of the array
            if (l == spaceNeeded - 1 && cache[k] != pagesToInsert[l]) {
              cachePos = k;
              furthestFound = true;
              break;
            }

            nextHit++;
            if (cache[k] == pagesToInsert[l]) {
              if (nextHit > furthestAway) {
                furthestAway = nextHit;
                cachePos = k;
              }
              break;
            }
          }

          if (furthestFound) {
            break;
          }
        }

        cache[cachePos] = pagesToInsert[j];  // replace node
      } else {
        cache[nextEmptySpot] = pagesToInsert[j];
        pageFaults++;
        nextEmptySpot++;
      }
    }

    cout << pageFaults << endl;
    pageFaults = 0;
  }

  return 0;
}

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int numInversions = 0;

// takes in two pointers that will be combined into one list and returned
vector<int> Merge(vector<int> frontHalf, vector<int> backHalf, int fhLength, int bhLength)
{
    vector<int> toRet(fhLength + bhLength);
    int fhCounter = 0;
    int bhCounter = 0;

    while (fhCounter != fhLength || bhCounter != bhLength) // an element still needs to be added
    {
        if (fhCounter == fhLength) // already added all the fh elements
        {
            toRet[fhCounter + bhCounter] = backHalf[bhCounter];
            bhCounter++; // don't need to increment inversions since we've already been through the whole front half
        } else if (bhCounter == bhLength) // already added all the bh elements
        {
            toRet[fhCounter + bhCounter] = frontHalf[fhCounter];
            fhCounter++;
        } // next else if and else add the lower of the two elements at the front of each list and increments respective counter
        else if (frontHalf[fhCounter] < backHalf[bhCounter]) 
        {
            toRet[fhCounter + bhCounter] = frontHalf[fhCounter];
            fhCounter++;
        } else
        {
            toRet[fhCounter + bhCounter] = backHalf[bhCounter];
            bhCounter++;
            numInversions += fhLength - fhCounter; // how many inversions there are for this element
        }
    }
    
    return toRet;
}

// takes in a list and works recursively to return an ordered list
vector<int> MergeSort(vector<int> elementList, int elLength)
{
    if (elLength == 1) // base case
    {
        return elementList;
    }

    if (elLength % 2 == 1)
    {
        vector<int> frontHalf(elementList.begin(), elementList.begin() + (elLength / 2));
        vector<int> backHalf(elementList.begin() + (elLength / 2), elementList.end());

        return Merge(MergeSort(frontHalf, elLength / 2), MergeSort(backHalf, elLength / 2 + 1), elLength / 2, elLength / 2 + 1);
        // returns the sorted version of the front half and back half of the element list
    }
    else
    {
        vector<int> frontHalf(elementList.begin(), elementList.begin() + (elLength / 2));
        vector<int> backHalf(elementList.begin() + (elLength / 2), elementList.end());

        return Merge(MergeSort(frontHalf, elLength / 2), MergeSort(backHalf, elLength / 2), elLength / 2, elLength / 2);
    }
}

int main()
{
    int numInstances;
    cin >> numInstances;

    for (int i = 0; i < numInstances; i++)
    {
        int numElements;
        cin >> numElements;
        vector<int> elementList(numElements);

        for (int j = 0; j < numElements; j++)
        {
            cin >> elementList[j];
        }

        MergeSort(elementList, numElements);
        
        cout << numInversions << endl;
        numInversions = 0;
    }

    return 0;
}

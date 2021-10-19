#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ConnectedPoints {
    int topLineVal;
    int bottomLineVal;
};

long long intersectionCounter = 0; // might be larger than MAX_INT

// function helps with sorting the array of structs based on the top line
bool SortTopLine(ConnectedPoints i, ConnectedPoints j)
{
    return i.topLineVal < j.topLineVal;
}

// function used recursively to merge two arrays, counting inversions while it goes
vector<ConnectedPoints> Merge(vector<ConnectedPoints> frontHalf, vector<ConnectedPoints> backHalf, int fhLength, int bhLength)
{
    vector<ConnectedPoints> toRet(fhLength + bhLength);
    int fhCounter = 0;
    int bhCounter = 0;

    while (fhCounter != fhLength || bhCounter != bhLength)
    {
        if (bhCounter == bhLength)
        {
            toRet[fhCounter + bhCounter] = frontHalf[fhCounter];
            fhCounter++;
        }
        else if (fhCounter == fhLength)
        {
            toRet[fhCounter + bhCounter] = backHalf[bhCounter];
            bhCounter++;
        }
        else if (frontHalf[fhCounter].bottomLineVal <= backHalf[bhCounter].bottomLineVal)
        {
            toRet[fhCounter + bhCounter] = frontHalf[fhCounter];
            fhCounter++;
        }
        else
        {
            toRet[fhCounter + bhCounter] = backHalf[bhCounter];
            bhCounter++;

            intersectionCounter += fhLength - fhCounter;
        }
    }

    return toRet;
}

// recursively breaks down arrays to resort arrays given
vector<ConnectedPoints> MergeSort(vector<ConnectedPoints> toSort, int length)
{
    if (length == 1)
        return toSort;
    
    if (length % 2 == 1)
    {
        vector<ConnectedPoints> frontHalf(toSort.begin(), toSort.begin() + (length / 2));
        vector<ConnectedPoints> backHalf(toSort.begin() + (length / 2), toSort.end());

        return Merge(MergeSort(frontHalf, length / 2), MergeSort(backHalf, length / 2 + 1), length / 2, length / 2 + 1);
    }
    else
    {
        vector<ConnectedPoints> frontHalf(toSort.begin(), toSort.begin() + length / 2);
        vector<ConnectedPoints> backHalf(toSort.begin() + length / 2, toSort.end());

        return Merge(MergeSort(frontHalf, length / 2), MergeSort(backHalf, length / 2), length / 2, length / 2);
    }
}

int main()
{
    int numInstances;
    cin >> numInstances;

    for (int i = 0; i < numInstances; i++)
    {
        int numPairs;
        cin >> numPairs; // the number of nodes on each line

        vector<ConnectedPoints> Lines(numPairs);
        for (int j = 0; j < numPairs; j++)
        {
            cin >> Lines[j].topLineVal;
        }

        for (int j = 0; j < numPairs; j++)
        {
            cin >> Lines[j].bottomLineVal;
        }

        sort(Lines.begin(), Lines.end(), SortTopLine); // first sort by top line

        MergeSort(Lines, numPairs); // next sort by bottom line, counting inversions

        cout << intersectionCounter << endl;
        intersectionCounter = 0;
    }

    return 0;
}

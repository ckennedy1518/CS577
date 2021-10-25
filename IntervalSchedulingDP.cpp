#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Job {
    int startTime;
    int endTime;
    int weight;
};

// function assists std::sort algorithm for jobs to be ordered
// from smallest to largest finish time
bool SortByFinishTime(Job i, Job j) { return i.endTime < j.endTime; }

int main() {
    int numInstances;
    cin >> numInstances;

    for (int i = 0; i < numInstances; i++)
    {
        int numJobs;
        cin >> numJobs;

        vector<Job> jobs(numJobs); // store job data

        for (int j = 0; j < numJobs; j++) // get input for jobs
        {
            string info;
            if (j == 0)
            {
                getline(cin, info); // dummy for first line
            }
            getline(cin, info);

            stringstream newstream(info);
            newstream >> jobs[j].startTime;
            newstream >> jobs[j].endTime;
            newstream >> jobs[j].weight;
        }

        sort(jobs.begin(), jobs.end(), SortByFinishTime);
        
        for (int j = 1; j < numJobs; j++) // start at 1, 0 is already max
        { // loop overwrites numJobs as it iterates through it with the new max weight and its end time up until that point
            Job checkIfMax; // we'll see if i.weight + j.weight will be > j-1.weight
            checkIfMax.weight = 0;
            
            for (int k = j - 1; k >= 0; k--)
            { // loop finds "i = k", the closest finishing time that accepts j's start
                if (jobs[k].endTime <= jobs[j].startTime)
                {
                    checkIfMax.weight = jobs[k].weight + jobs[j].weight;
                    checkIfMax.endTime = jobs[j].endTime;
                    break;
                }
            }

            if (checkIfMax.weight == 0) // no job exists with a finish time before j's start
                checkIfMax = jobs[j];
            
            if (checkIfMax.weight > jobs[j - 1].weight) // reassign jobs[j]
                jobs[j] = checkIfMax;
            else
                jobs[j] = jobs[j - 1];
        }

        cout << jobs[numJobs - 1].weight << endl;
    }
}
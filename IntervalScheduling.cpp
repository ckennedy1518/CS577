#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Job {
  int Start;
  int Finish;
};
vector<Job> Jobs;
int JobsCompleted = 0;
int JobsLength = 0;

bool SortFunction(Job i, Job j) { return i.Finish > j.Finish; }

int main() {
  int numInstances;
  cin >> numInstances;

  for (int i = 0; i < numInstances; i++) {
    int numJobs;
    cin >> numJobs;

    for (int j = 0; j < numJobs; j++) {
      string jobStartAndFinish;
      if (j == 0) {
        getline(cin, jobStartAndFinish);
      }
      getline(cin, jobStartAndFinish);

      Job newJob;
      stringstream newStream(jobStartAndFinish);
      newStream >> newJob.Start;
      newStream >> newJob.Finish;
      Jobs.push_back(newJob);
      JobsLength++;
    }

    sort(Jobs.begin(), Jobs.end(), SortFunction);

    int currentTime = 0;
    while (!Jobs.empty()) {
      if (currentTime <= Jobs[JobsLength - 1].Start) {
        currentTime = Jobs[JobsLength - 1].Finish;
        JobsCompleted++;
      }
      Jobs.pop_back();
      JobsLength--;
    }

    cout << JobsCompleted << endl;
    JobsCompleted = 0;  // reset variables for next instance
  }

  return 0;
}

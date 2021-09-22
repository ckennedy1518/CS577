#include <iostream> 
#include <sstream>
#include <algorithm>
#include <map> 
#include <stack> 
#include <string> 
#include <vector> 
#include <cstdlib>

using namespace std; 

map<int, vector<string>> AdjacencyList; 
vector<int> unvisitedNodes; 
vector<int> visitedNodes; 

// function returns the position in the map of the string it is passed
int FindPosInMap(string NodeToFind)
{
    int posCounter = 0;
    for (auto val : AdjacencyList)
    {
        if (val.second[0] == NodeToFind)
        {
            return posCounter;
        }
        posCounter++;
    }
    return -1;
}

vector<string> DFS(string node, int alPos) 
{ 
    vector<string> output; 
    output.push_back(node); 
    visitedNodes.push_back(alPos);

    for (int i = 1; i < (int)AdjacencyList[alPos].size(); i++) // for the children of alPos
    {
        if (count(visitedNodes.begin(), visitedNodes.end(), AdjacencyList[alPos][i]) == 0) // child hasn't been visited
        {
            vector<string> temp = DFS(AdjacencyList[alPos][i], FindPosInMap(AdjacencyList[alPos][i]));
            for (string st : temp)
            {
                output.push_back(st);
            }
        }        
    } 

    return output; 
}

int main() { 
    int numGraphs = 0; 
    cin >> numGraphs; 
    
    stack<string> nodeContainer; 
    vector<string> output; 
    
    for (int i = 0; i < numGraphs; i++) 
    { 
        int numNodes = 0; 
        cin >> numNodes;

        while (!nodeContainer.empty())  // start fresh for next graph
        { 
            nodeContainer.pop(); 
        }
        unvisitedNodes.clear(); 
        visitedNodes.clear(); 
        AdjacencyList.clear(); 
        output.clear(); 

        for (int j = 0; j < numNodes; j++)  // loop gets nodes and edges 
        { 
            string nodeAndAdjacentNodeList; 

            if (j == 0)
            {
                getline(cin, nodeAndAdjacentNodeList); // temp, whitespacing weird for some reason?
            }
            getline(cin, nodeAndAdjacentNodeList);

            string token; 
            stringstream newStream(nodeAndAdjacentNodeList); 
            vector<string> niceInput; 
            while (newStream >> token) 
            { 
                niceInput.push_back(token);
            } 
            
            AdjacencyList.insert({j, niceInput}); 
            unvisitedNodes.push_back(j); 
        }

        int counter = 0; // for keeping track of where at if DFS doesn't complete (disconnected graph)
        while (!unvisitedNodes.empty())
        {
            // two step process here accounts for multiple possibilities
            // if we were to just set output to be = to the next line it could get overwritten
            vector<string> temp = DFS(AdjacencyList[counter][0], counter); 
            for (string s : temp)
            {
                output.push_back(s);
            }
        }
        
        for (int k = 0; k < output.size(); k++)  // output 
        { 
            cout << output[k]; 
            (k == (int)output.size() - 1) ? cout << endl : cout << " "; 
        } 
    } 
    
    return 0; 
}
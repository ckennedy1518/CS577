#include <iostream> 
#include <sstream>
#include <map> 
#include <stack>
#include <vector> 
#include <algorithm>
#include <iterator>

using namespace std; 

map<int, vector<string>> AdjacencyList; 
vector<int> unvisitedNodes; 
vector<int> visitedNodes; 

// function returns the position in the map of the string it is passed or -1 if 
// the string isn't the first element of one of the vector<string>s in the AL
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

// Function recursively pushes and pops nodes off a stack to traverse the adjacency list
vector<string> DFS(string node, int alPos) 
{ 
    vector<string> output; 
    output.push_back(node); 
    visitedNodes.push_back(alPos);

    int alSize = (int)(AdjacencyList[alPos].size());
    for (int i = 1; i < alSize; i++) // for the children of alPos
    {
        int isNodeAlreadyTraversed = (int)count(visitedNodes.begin(), visitedNodes.end(), AdjacencyList[alPos][i]);
        if (isNodeAlreadyTraversed == 0) // child hasn't been visited
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

// Function gets input for the graph, calls DFS to get the output information, then prints it to the screen
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
        
        int outputSize = (int)(output.size());
        for (int k = 0; k < outputSize; k++)  // output 
        { 
            cout << output[k]; 
            (k == outputSize - 1) ? cout << endl : cout << " "; // print new line or space depending on where at in vector
        } 
    } 
    
    return 0; 
}

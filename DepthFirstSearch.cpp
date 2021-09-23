#include <iostream> 
#include <sstream>
#include <vector> 
#include <algorithm>
#include <iterator>

using namespace std; 

vector<vector<string>> AdjacencyList; 
vector<string> unvisitedNodes; 
vector<string> visitedNodes;
int numNodesRemoved = 0;

// function returns the position in the 2D Adjacency List of the string it is passed or -1 if 
// the string isn't the first element of one of the vector<string>s in the AL
int FindPosInList(string NodeToFind)
{
    int posCounter = 0;
    for (vector<string> vs : AdjacencyList)
    {
        if (vs[0] == NodeToFind)
        {
            return posCounter;
        }
        posCounter++;
    }

    return -1;
}

// Function recursively "pushes" and "pops" nodes off a "stack" to traverse the adjacency list
vector<string> DFS(string node) 
{
    vector<string> output;    
    output.push_back(node);
    visitedNodes.push_back(node);
    unvisitedNodes.erase(find(unvisitedNodes.begin(), unvisitedNodes.end(), node));
    numNodesRemoved++;

    for (int i = 1; i < AdjacencyList[FindPosInList(node)].size(); i++) // for the children of node
    {
        //check if child is in visitedNodes
        if (*find(visitedNodes.begin(), visitedNodes.end(), AdjacencyList[FindPosInList(node)][i]) != AdjacencyList[FindPosInList(node)][i]) // child hasn't been visited
        {
            vector<string> temp = DFS(AdjacencyList[FindPosInList(node)][i]);
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
    
    vector<string> output; 
    
    for (int i = 0; i < numGraphs; i++) 
    { 
        int numNodes = 0; 
        cin >> numNodes;

        unvisitedNodes.clear(); 
        visitedNodes.clear(); 
        AdjacencyList.clear(); 
        output.clear(); 

        for (int j = 0; j < numNodes; j++)  // loop gets nodes and edges 
        { 
            string nodeAndAdjacentNodeList; 

            if (j == 0)
            {
                getline(cin, nodeAndAdjacentNodeList); // temp, need to grab line from prev cin in order to accurately grab next line
            }
            getline(cin, nodeAndAdjacentNodeList);

            string token; 
            stringstream newStream(nodeAndAdjacentNodeList); 
            vector<string> niceInput; 
            while (newStream >> token) 
            { 
                niceInput.push_back(token);
            } 
            
            AdjacencyList.push_back(niceInput);
            unvisitedNodes.push_back(AdjacencyList[AdjacencyList.size() - 1][0]);
        }

        while (!unvisitedNodes.empty())
        {
            // two step process here accounts for multiple possibilities
            // if we were to just set output to be = to the next line it could get overwritten

            DFS(AdjacencyList[FindPosInList(unvisitedNodes[0])][0]);
        }
        
        for (int k = 0; k < visitedNodes.size(); k++)  // output 
        { 
            cout << visitedNodes[k]; 
            (k == visitedNodes.size() - 1) ? cout << endl : cout << " "; // print new line or space depending on where at in vector
        } 
    } 
    
    return 0; 
}

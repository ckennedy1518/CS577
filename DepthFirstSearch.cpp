#include <iostream> 
#include <sstream>
#include <vector>

using namespace std; 

vector<vector<string>> AdjacencyList;
vector<bool> visitedNodes;

// returns true if all nodes are visited, false otherwise
bool AllNodesVisited()
{
    for (bool b : visitedNodes)
    {
        if (!b)
        {
            return false;
        }
    }

    return true;
}

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

// Function recursively visits nodes to traverse the adjacency list
vector<string> DFS(string node) 
{
    int nodePosInList = FindPosInList(node);
    vector<string> output;    
    output.push_back(node);
    visitedNodes[nodePosInList] = true;

    for (int i = 1; i < AdjacencyList[nodePosInList].size(); i++) // for the children of node
    {
        if (!visitedNodes[FindPosInList(AdjacencyList[nodePosInList][i])]) // child hasn't been visited
        {
            vector<string> temp = DFS(AdjacencyList[nodePosInList][i]);
            for (string s : temp)
            {
                output.push_back(s);
            }
        }        
    } 

    return output; 
}

int main() { 
    int numGraphs = 0; 
    cin >> numGraphs;

    vector<string> output;
    
    for (int i = 0; i < numGraphs; i++) 
    { 
        int numNodes = 0; 
        cin >> numNodes;
 
        AdjacencyList.clear();
        output.clear();
        visitedNodes.clear();

        for (int j = 0; j < numNodes; j++)  // loop gets nodes and edges (input)
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
            visitedNodes.push_back(false);
        }

        while (!AllNodesVisited()) // DFS portion
        {
            int nextUnvisited = 0;
            for (bool b : visitedNodes)
            {
                if (!b)
                {
                    // two step process here accounts for disconnected graphs
                    // if we were to just set output to be = to the next line it could get overwritten
                    vector<string> temp;
                    temp = DFS(AdjacencyList[nextUnvisited][0]);
                    for (string s : temp)
                    {
                        output.push_back(s);
                    }
                    break;
                }
                else
                {
                    nextUnvisited++;
                }
            }
        }
        
        for (int k = 0; k < output.size(); k++)  // output 
        { 
            cout << output[k]; 
            (k == output.size() - 1) ? cout << endl : cout << " "; // print new line or space depending on where at in vector
        } 
    } 
    
    return 0; 
}

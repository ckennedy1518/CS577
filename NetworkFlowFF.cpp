#include <iostream>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

struct Edge
{
    int source;
    int destination;
    int cost;
};

struct Node
{ // used for makeshift tree to store BFS info
    int nodeNum;
    int parent;
};

// function returns an augmenting path from 1 to n
vector<int> getAP(vector<Edge> edgeArray, int numNodes, int numEdges)
{
    vector<pair<Node, vector<int>>> tree(numNodes); 
    // attach tree info with dynamic sized array (for children)
    for (int i = 0; i < numNodes; i++) // for 1 indexing
    { // create tree structure
        Node t;
        t.nodeNum = i + 1;
        t.parent = 0;
        tree[i] = pair<Node, vector<int>>(t, vector<int>());
    }

    vector<bool> visited(numNodes); // for keeping track of visited nodes during BFS
    for (int i = 0; i < numNodes; i++)
    {
        visited[i] = false;
    }

    queue<int> Q;
    Q.push(1); // first node
    visited[0] = true;
    while (!Q.empty())
    {
        int frontNode = Q.front();
        Q.pop();
        for (int i = 0; i < numEdges; i++)
        {
            if (edgeArray[i].source == frontNode && !visited[edgeArray[i].destination - 1])
            { // neighbors of u not yet visited
                tree[frontNode - 1].second.push_back(edgeArray[i].destination); // this is a child of frontNode - 1
                tree[edgeArray[i].destination - 1].first.parent = frontNode;

                if (edgeArray[i].destination == numNodes)
                { // we have an augmenting path
                    vector<int> toRet; // hold on to path in reverse order
                    Node t;
                    t = tree[numNodes - 1].first; // should be most recent one added
                    toRet.push_back(numNodes);
                    while (t.parent != 0)
                    {
                        toRet.push_back(t.parent);
                        t = tree[t.parent - 1].first;
                    }
                    return toRet;
                }
                
                visited[edgeArray[i].destination - 1] = true;
                Q.push(edgeArray[i].destination);
            }
        }
    }

    return vector<int>(); // no augmenting path if this spot reached
}

// function updates edgeArray and numEdges for purposes of making a residual graph
void bottleneck(vector<Edge>& edgeArray, vector<int> augPath, int& numEdges)
{
    // we know augPath is in reverse order
    // we can get path one edge at a time, keeping track of proper edge location
    vector<int> edgesInAP;
    int EIAPSize = 0;
    int counter = 0;
    while (augPath.size() > 1)
    {
        counter++;
        for (int i = 0; i < numEdges; i++)
        {
            if (edgeArray[i].destination == augPath[0] && edgeArray[i].source == augPath[1])
            {
                edgesInAP.push_back(i);
                EIAPSize++;
                augPath.erase(augPath.begin()); // continue with next
                break; // leave for loop and continue while
            }
        }
    }

    int minVal = INT32_MAX;
    for (int i = 0; i < EIAPSize; i++)
    { // loop gets min val for every edge in augmenting path
        if (minVal > edgeArray[edgesInAP[i]].cost)  
        {
            minVal = edgeArray[edgesInAP[i]].cost;
        }
    }

    vector<int> needToErase; // keep track of indices here so as to not mess up loop
    int NTESize = 0;
    for (int i = 0; i < EIAPSize; i++)
    { // new loop uses minVal to update edges
        edgeArray[edgesInAP[i]].cost -= minVal;

        bool needToAddEdge = true;
        for (int j = 0; j < numEdges; j++)
        {
            if (edgeArray[edgesInAP[i]].destination == edgeArray[j].source && 
            edgeArray[edgesInAP[i]].source == edgeArray[j].destination)
            {
                needToAddEdge = false;
                edgeArray[j].cost += minVal; // since we're reversing for residual graph
                break; // found edge, don't need to keep traversing
            }
        }

        if (needToAddEdge)
        {
            Edge e; // create edge that will point reverse direction
            e.cost = minVal;
            e.source = edgeArray[edgesInAP[i]].destination;
            e.destination = edgeArray[edgesInAP[i]].source;
            edgeArray.push_back(e);
            numEdges++;
        }
        
        if (edgeArray[edgesInAP[i]].cost == 0)
        {
            needToErase.push_back(edgesInAP[i]);
            NTESize++;
            numEdges--;
        }
    }

    for (int i = 0; i < NTESize; i++)
    {
        edgeArray.erase(edgeArray.begin() + needToErase[i]);
    }
}

int main()
{
    int numInstances;
    cin >> numInstances;

    for (int i = 0; i < numInstances; i++)
    {
        int numNodes;
        cin >> numNodes;
        int numEdges;
        cin >> numEdges;

        vector<Edge> edgeArray(numEdges); // get input
        vector<int> edgesToRemove;
        int numETR = 0;
        for (int j = 0; j < numEdges; j++)
        {
            cin >> edgeArray[j].source;
            cin >> edgeArray[j].destination;
            cin >> edgeArray[j].cost;
            for (int k = 0; k < j; k++)
            { // we can combine edges
                if (edgeArray[j].source == edgeArray[k].source && 
                edgeArray[j].destination == edgeArray[k].destination)
                { 
                    edgesToRemove.push_back(j);
                    edgeArray[k].cost += edgeArray[j].cost;
                    numETR++;
                }
            }
        }
        for (int j = 0; j < numETR; j++)
        { // part where we actually combine edges
            edgeArray.erase(edgeArray.begin() + edgesToRemove[j]);
            numEdges--;
        }

        bool augmentingPath = true;
        vector<int> BFSReturn;
        while (augmentingPath)
        { // continue until no more augmenting paths
            BFSReturn = getAP(edgeArray, numNodes, numEdges);

            if (BFSReturn.size() == vector<int>().size())
                augmentingPath = false;
            else
                bottleneck(edgeArray, BFSReturn, numEdges);
        }

        int flow = 0;
        for (int j = 0; j < numEdges; j++)
        { // get max flow from residual graph we've created
            if (edgeArray[j].source == numNodes)
                flow += edgeArray[j].cost;
        }
        cout << flow << endl;
    }

    return 0;
}
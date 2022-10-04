#include <iostream>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

struct Edge
{
    int source;
    int destination;
    int cost = 1; // every edge has capacity one
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

    for (int i = 0; i < numNodes; i++)
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
            { // neighbors not yet visited
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
void bottleneck(vector<Edge>& edgeArray, vector<int> augPath, int& numEdges, int& flow)
{
    // we know augPath is in reverse order
    // we can get path one edge at a time, keeping track of proper edge location
    vector<int> edgesInAP;
    int EIAPSize = 0;
    while (augPath.size() > 1)
    {
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

    flow++;

    vector<int> needToErase; // keep track of indices here so as to not mess up loop
    int NTESize = 0;
    for (int i = 0; i < EIAPSize; i++)
    { // new loop uses minVal to update edges
        edgeArray[edgesInAP[i]].cost -= 1;

        Edge e; // create edge that will point reverse direction
        e.source = edgeArray[edgesInAP[i]].destination;
        e.destination = edgeArray[edgesInAP[i]].source;
        edgeArray.push_back(e);
                
        needToErase.push_back(edgesInAP[i]);
        NTESize++;
    }

    for (int i = 0; i < NTESize; i++)
    {
        for (int j = i + 1; j < NTESize; j++)
        {
            if (needToErase[j] > needToErase[i])
            {
                needToErase[j]--;
            }
        }
        edgeArray.erase(edgeArray.begin() + needToErase[i]);
    }
}

int main()
{
    int numInstances;
    cin >> numInstances;

    for (int i = 0; i < numInstances; i++)
    {
        int setASize; // get input
        cin >> setASize;
        int setBSize;
        cin >> setBSize;
        int numEdges;
        cin >> numEdges;

        vector<Edge> edgeList(numEdges + setASize + setBSize);
        // allocate space for edges and creating a supersource/sink after
        for (int j = 0; j < numEdges; j++)
        { // get edges between nodes
            cin >> edgeList[j].source; // make room for super source
            edgeList[j].source++;
            cin >> edgeList[j].destination;
            edgeList[j].destination += setASize + 1;
        }

        for (int j = numEdges; j < numEdges + setASize; j++)
        { // create super source
            edgeList[j].source = 1; // location of "super source"
            edgeList[j].destination = j - numEdges + 2;
        }

        for (int j = numEdges + setASize; j < numEdges + setASize + setBSize; j++)
        {
            edgeList[j].source = j - numEdges + 2;
            edgeList[j].destination = setASize + setBSize + 2; // loc of "super sink" (also number of nodes)
        }

        bool augmentingPath = true;
        vector<int> BFSReturn;
        int flow = 0;
        numEdges += setASize + setBSize;
        while (augmentingPath)
        { // continue until no more augmenting paths
            BFSReturn = getAP(edgeList, setASize + setBSize + 2, numEdges);

            if (BFSReturn.size() == vector<int>().size())
                augmentingPath = false;
            else
                bottleneck(edgeList, BFSReturn, numEdges, flow);
        }
        
        cout << flow;
        if (flow == setASize && flow == setBSize)
            cout << " Y" << endl;
        else
            cout << " N" << endl;
    }

    return 0;
}
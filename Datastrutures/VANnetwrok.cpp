#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

class vertex {
public:
    int uniqueId;
    string type;
    int weight = INT_MAX;
    vector<int> edgeWeight;
    vertex(int n = 0, string loc = "null") : uniqueId(n), type(loc) {};
};

class minHeap {
public:
    int size;
    vertex* ptr;
    minHeap() {
        std::ifstream inputFile("graph.txt");
        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << endl;
            return;
        }
        string app;
        int uni;
        inputFile >> size;
        ptr = new vertex[size];
        for (int i = 0; i < size; i++) {
            inputFile >> uni;
            inputFile.ignore(uni, ',');
            inputFile >> app;
            vertex graphVert(uni, app);
            ptr[i] = graphVert;
        }
    }

    void heapify(int i = 0) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < size && ptr[l].weight < ptr[i].weight)
            smallest = l;
        if (r < size && ptr[r].weight < ptr[smallest].weight)
            smallest = r;
        if (smallest != i) {
            swap(ptr[i], ptr[smallest]);
            heapify(smallest);
        }
    }

    vertex extractMin() {
        if (size <= 0)
            return INT_MAX;
        if (size == 1) {
            size--;
            return ptr[0];
        }
        vertex root = ptr[0];
        ptr[0] = ptr[size - 1];
        size--;
        heapify(0);
        return root;
    }

    void decreaseKey(int i, int new_val) {
        cout << "dec called\n";
        ptr[i].weight = new_val;
        heapify(0);
    }

    bool isempty() {
        return size == 0;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << ptr[i].type << " ";
        }
    }
};

class graph : public vertex {
    minHeap graphHeap;
public:
    list<vertex>* adjList;
    int totalvertices;
    int totaledges;
    graph(int v = 0) : totalvertices(v) {
        std::ifstream inputFile("graph.txt");
        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << endl;
            return;
        }
        string app;
        inputFile >> totalvertices;
        adjList = new list<vertex>[totalvertices];
    };

    void addEdge(int src = 0, int dest = 0) {
        adjList[src].push_back(adjList[dest].front());
        adjList[dest].push_back(adjList[src].front());
    }

    void buildGraph(string fileName = "null") {
        std::ifstream inputFile("graph.txt");
        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << endl;
            return;
        }
        string app;
        int uni;
        inputFile >> totalvertices;
        for (int i = 0; i < totalvertices; i++) {
            inputFile >> uni;
            inputFile.ignore(uni, ',');
            inputFile >> app;
            vertex graphVert(uni, app);
            adjList[i].push_back(graphVert);
        }
        inputFile >> totaledges;
        int s = 0;
        int d = 0;
        int we = 0;
        for (int i = 0; i < totaledges; i++) {
            inputFile >> s;
            inputFile.ignore(s, ',');
            inputFile >> d;
            inputFile >> we;
            adjList[s - 1].front().edgeWeight.push_back(we);
            adjList[d - 1].front().edgeWeight.push_back(we);
            addEdge(s - 1, d - 1);
        }
    }

    void printgraph() {
        for (int i = 0; i < totalvertices; i++) {
            list<vertex>::iterator it;
            for (it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                cout << it->uniqueId << " ";
            }
            cout << endl;
        }
        cout << endl;
        for (int i = 0; i < totalvertices; i++) {
            cout << graphHeap.ptr[i].uniqueId << " ";
        }
        cout << endl;
        cout << endl;
    }

    bool existsinHeap(int d = 0) {
        for (int i = 0; i < graphHeap.size; i++) {
            if (graphHeap.ptr[i].uniqueId == d)
                return true;
        }
        return false;
    }

    int getindex(int d = 0) {
        for (int i = 0; i < graphHeap.size; i++) {
            if (graphHeap.ptr[i].uniqueId == d)
                return i;
        }
        return -1; // Return -1 if not found
    }

    void findMST() {
        for (int i = 0; i < graphHeap.size; i++) {
            graphHeap.ptr[i].edgeWeight = adjList[i].front().edgeWeight;
        }
        vector<pair<int, int>> mstEdges;
        graphHeap.ptr[0].weight = 0;
        while (!graphHeap.isempty()) {
            vertex min = graphHeap.extractMin();

            std::list<vertex>::iterator pivot = adjList[min.uniqueId - 1].begin();
            int i = 0;

            std::list<vertex>::iterator it = adjList[min.uniqueId - 1].begin();
            ++it;
            for (; it != adjList[min.uniqueId - 1].end(); ++it) {
                if (pivot->edgeWeight[i] < it->weight) {
                    if (existsinHeap(it->uniqueId)) {
                        int index = getindex(it->uniqueId);
                        if (index != -1) { // Check if vertex is found in the heap
                            graphHeap.decreaseKey(index, pivot->edgeWeight[i]);
                            if (it->uniqueId != 2)
                            {
                                mstEdges.push_back({ min.uniqueId, it->uniqueId });
                            }
                        }
                    }
                }
                i++;
            }
        }

        for (const auto& edge : mstEdges) {
   
                cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }
};

void menu(graph g) {
        int option = 0;
    while (option!= -1)
    {
        cout << "To input a graph Enter 1\n";
        cout << "To find MST Enter 2 \n";
        cout << "To out put graph enter 3\n";
        cout << "To add an vertex enter 4\n";
        cout << "to add an edge enter 5\n";
        cin >> option;
        if (option == 1) {
            g.buildGraph();
        }

        if (option == 2) {
            g.findMST();
        }

        if (option == 3) {
            g.printgraph();
        }

        if (option == 4) {
            cout << "enter type\n";
            string type;
            cin >> type;
            vertex v1(g.totalvertices, type);
            ++g.totalvertices;
            g.adjList[g.totalvertices - 1].push_back(v1);
        }

        if (option == 5) {
            int src = 0;
            int dest = 0;
            cin >> src >> dest;
            g.addEdge(src, dest);

        }
    }


}

int main() {
    graph g1;
    menu(g1);
    return 0;
}

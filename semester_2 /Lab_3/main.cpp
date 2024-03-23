#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <queue>
using namespace std;

class GPainter;

class Graph {
    friend class GPainter;
private:
    vector<vector<int>> adjmatrix;
    vector<char> verticies;
public:
    Graph(int, string); // string: dir
public: 
    void putWeights(vector<vector<int>>);
    vector<vector<int>> getMatrix();
    vector<char> getVerticies();
    void printMatrix();    
    template <class T>
    void printMatrix(vector<vector<T>>);
public:
    template <class T>
    void printVector(vector<T>);
    vector<int> getNbrs(int);
};

class GPainter {
public:
    void printMap(map<int, vector<int>>);
    template <class T>
    void printVector(vector<T>);
    map<int, vector<int>> paint(Graph);
};

int main() {

    Graph graph(5, "./test_m.txt");

    graph.printMatrix();

    GPainter painter;
    auto cmap = painter.paint(graph);
    cout << "color map: " << endl;
    painter.printMap(cmap);
    return 0;
}


// implementation


Graph::Graph(int vert_num, string dir) {
    ifstream ifile;
    ifile.open(dir);

    if (!ifile.is_open()) {
        cout << "Bad file" << endl;
    }
    else {
        int input;
        this->adjmatrix = vector<vector<int>>(vert_num, vector<int>(vert_num, 0));

        for (int i = 0; i < vert_num; i++) {
            for (int j = 0; j < vert_num; j++) {
                ifile >> input;
                if (input != 0) {
                    this->adjmatrix[i][j] = input;
                }
                else if (input == 0) {
                    this->adjmatrix[i][j] = 0;
                }
            }
        }
    }
    char c = 'A';
    for (int i = 0; i < vert_num; i++) {
        this->verticies.push_back(c+i);
    }

}

vector<vector<int>> Graph::getMatrix() {
    return this->adjmatrix;
}

vector<char> Graph::getVerticies() {
    return this->verticies;
}

template <class T>
void Graph::printVector(vector<T> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
}

void Graph::printMatrix() {
    cout << "  ";
    printVector(this->verticies);
    cout << endl;
    for (int i = 0; i < this->adjmatrix.size(); i++) {
        cout << this->verticies[i] << " ";
        printVector(this->adjmatrix[i]);
        cout << endl;
    }
}

template <class T>
void Graph::printMatrix(vector<vector<T>> mtx) {
    for (int i = 0; i < mtx.size(); i++) {
        printVector(mtx[i]);
        cout << endl;
    }
}

void Graph::putWeights(vector<vector<int>> weights) {
    this->adjmatrix = weights;
    cout << "There these number of verticies: " << weights.size() << endl;
}

template <class T>
void GPainter::printVector(vector<T> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
}

void GPainter::printMap(map<int, vector<int>> m) {
    for (auto [k, e] : m) {
        cout << k << ": ";
        printVector(e);
        cout << endl;
    }   
}

vector<int> Graph::getNbrs(int vertex) {
    vector<int> adjacent_verticies; 
    for (int i = 0; i < adjmatrix.size(); i++) {
        if (adjmatrix[vertex][i] != 0) {
            adjacent_verticies.push_back(i);
        }
    }
    return adjacent_verticies;
}

map<int, vector<int>> GPainter::paint(Graph graph) {
    int colors = 4; // nubmer of colors we going to use 
    queue<int> q; // we're gonna to realize BFS here 

    vector<bool> used_colors = vector<bool>(colors, false);
    
    vector<bool> visited = vector<bool>(graph.adjmatrix.size(), false);

    q.push(0); // 0 vertex 
    visited[0] = true;

    map<int, vector<int>> color_map;

    for (int i = 0; i < colors; i++) {
        color_map.insert({i, {}});
    }

    vector<int> vertex_color =  vector<int>(graph.adjmatrix.size(), -1);

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        auto adjacent_verticies = graph.getNbrs(vertex); 
        used_colors = vector<bool>(colors, false);

        for (int i = 0; i < adjacent_verticies.size(); i++) {
            if (vertex_color[adjacent_verticies[i]] != -1) {
                used_colors[vertex_color[adjacent_verticies[i]]] = true;
            }

        }

        for (int i = 0; i < colors; i++) {
            if (used_colors[i] == false) {
                vertex_color[vertex] = i;
                color_map[i].push_back(vertex);
                break;
            }
        }

        for (auto nbr : adjacent_verticies) {
            if (visited[nbr] != true) {
                q.push(nbr);
                visited[nbr] = true;
            }
        }
    }
    return color_map;
}

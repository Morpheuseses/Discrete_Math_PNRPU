#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
using namespace std;


class Graph {
    vector<vector<int>> adjmatrix;
    vector<char> vertices;
    int vert_num = 7;

public:
    Graph(vector<char> vertices) {
        this->vertices = vertices;
    }
    Graph(string file_dir) {
        ifstream ifile;
        ifile.open(file_dir);
        if (!ifile.is_open()) {
            cout << "Bad file" << endl;
        }
        else {
            int input;
            this->adjmatrix = vector<vector<int>>(7, vector<int>(7, 0));

            for (int i = 0; i < vert_num; i++) {
                for (int j = 0; j < vert_num; j++) {
                    ifile >> input;
                    if (input == 1) {
                        this->adjmatrix[i][j] = 1;
                    }
                    else if (input == 0) {
                        this->adjmatrix[i][j] = 0;
                    }
                }
            }
        }
        char c = 'A';
        for (int i = 0; i < vert_num; i++) {
            this->vertices.push_back(c+i);
        }
    }

    vector<char> getVerts() {
        return vertices;
    }

    void setMatrix(vector<vector<int>> mtx) {
        if (mtx.size() != vertices.size() || mtx[0].size() != vertices.size()){
            cout << "Size of matrix doesn't corresponds to number of vertices" << endl;
            return;
        }
        this->adjmatrix = mtx;
    }

    template <class T>
    void printvec(vector<T> vec) {
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] << " ";
        }
        cout << endl;
    }

    void printMtx() {
        if (adjmatrix.size() == 0) {
            cout << "There is no links in graph" << endl;
            return;
        }
        cout << "  ";
        printvec(vertices);
        for (int i = 0; i < adjmatrix.size(); i++) {
            cout << vertices[i] << " ";
            printvec(adjmatrix[i]);
        }

    }
    void printMtx(vector<vector<int>> mtx) {
        if (mtx.size() == 0) {
            cout << "There is no links in graph" << endl;
            return;
        }
        
        for (int i = 0; i < mtx.size(); i++) {
            printvec(mtx[i]);
        }
        cout << endl;
    }
    
    vector<vector<int>> get_component() {
        auto mtx = getEqual(this->adjmatrix);
        
        
        mtx = getStrongConnectivity(mtx);

        set<vector<int>> set;

        for (auto elem : mtx) {
            set.insert(elem);
        }

        vector<vector<int>> res;

        for (auto elem : set) {
            res.push_back(elem);
        }

        return res;
    }
private:
    vector<vector<int>> getStrongConnectivity(vector<vector<int>> mtx) {
        auto res = mtx;
        for (int i = 0; i < mtx[0].size(); i++) {
            for (int j = 0; j < mtx.size(); j++) {
                if (i!= j) {
                    res[i][j] = mtx[i][j] == 1 && mtx[j][i] == 1 ? 1 : 0;
                }
            }
        }
        return res;
    }
    vector<vector<int>> getEqual(vector<vector<int>> mtx) {
        auto prev = vector<vector<int>>(mtx.size(), vector<int>(mtx[0].size(), 0));
        auto curr = mtx;
        
        if (mtx.size() == mtx[0].size()) {
            for (int i = 0; i < mtx.size(); i++) {
                curr[i][i] = 1;
            }
        }
        auto mult = curr;
        printMtx(curr);
        while (curr != prev) {
            prev = curr;
            curr = multMtx(curr, mult);
            printMtx(curr);
        }

        return curr;
    }
    vector<vector<int>> multMtx(vector<vector<int>> mtx1, vector<vector<int>> mtx2) {
        if (mtx1.size() != mtx2[0].size()) {
            cout << "Unable to multiply matrices"<< endl;
            return vector<vector<int>>(mtx1.size(), vector<int>(mtx2[0].size(), 0));
        }

        vector<vector<int>> res_mtx = vector<vector<int>>(mtx1.size(), vector<int>(mtx2[0].size(), 0));

        for (int i = 0; i < mtx1.size(); i++) {
            for (int j = 0; j < mtx2[0].size(); j++) {
                int sum = 0;
                for (int k = 0; k < mtx1.size(); k++) {
                    sum += mtx1[i][k] * mtx2[k][j];
                }
                res_mtx[i][j] = sum >= 1 ? 1 : 0; // sum // max(1, abs(sum))
            }
        }
        return res_mtx;
    }
};

int main() {
    //vector<char> vertices = {'A', 'B', 'C', 'D'};

    //Graph graph(vertices);
    /*
    vector<vector<int>> mtx = {
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
    };
    */
    std::string file_dir = "./m1.txt";

    Graph graph(file_dir);
    
    // graph.setMatrix(mtx);

    auto vec = graph.get_component();

    graph.printMtx(vec);
    return 0;
}
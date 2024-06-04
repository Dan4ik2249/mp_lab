#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class Graph_Alg{
    private:
    bool *visited;
	vector<vector<int>> graph;
	int size_gr;
    int size_edge;

    public:
    Graph_Alg(int size){
        size_gr = size;
        graph.reserve(size);
    }

    void add(int src, int dst){
        graph[src].push_back(dst);
    }
    void add2(int src, int dst){
        graph[src].push_back(dst);
        graph[dst].push_back(src);
        size_edge++;
    }

    void Taryan(int start){
        visited = new bool[size_gr];
        vector<int> stack;
        for (int i = 0; i < size_gr; i++) visited[i] = false;

        for (int v=0; v < size_gr; v++) 
            if(visited[v] == false) dfs_inv(v, visited, stack);
        for (int i = stack.size()-1; i > -1; i--) cout << stack[i] << " ";
        cout << endl;
    }

    void dfs_inv(int vert, bool *visited, vector<int> &stack){
        visited[vert] = true;
        for (auto &y: graph[vert]){
            if(visited[y] == false && y!=-1) dfs_inv(y, visited, stack);
            }
        stack.push_back(vert);
    }

    void Fleri(){
        vector<vector<int>> tmp(size_gr);
        for (int i = 0; i < size_gr; i++){
            for (int j = 0; j < graph[i].size(); j++){
                tmp[i].push_back(graph[i][j]);
            }
        }
        int v = 5;
        vector<int> result;
        result.push_back(v);

        while (size_edge > 0){
            int res = 0;
            for (int i = 0; i < tmp[v].size(); i++){
                int u = tmp[v][i];
                if (tmp[u].size() > 1){
                    result.push_back(u);

                    tmp[v].erase(tmp[v].begin() + i);
                    auto it = find(tmp[u].begin(), tmp[u].end(), v);
                    tmp[u].erase(it);
                    v = u;
                    size_edge--;
                    res = 1;
                    break;
                }
            }
            if (res == 0){
                for (int i = 0; i < size_gr; i++){
                    if (tmp[v].size() < 2){
                        for (int i = 0; i < tmp[v].size(); i++){
                            int u = tmp[v][i];
                            result.push_back(u);
                            tmp[v].erase(tmp[v].begin() + i);
                            auto it = find(tmp[u].begin(), tmp[u].end(), v);
                            tmp[u].erase(it);
                            size_edge--;
                        }
                    }
                }
            }
        }

        for (auto &a: result){
            cout << a << " ";
        }
        cout << endl;
    }

    void Cycle_Alg(){
        vector<vector<int>> tmp(size_gr);
        for (int i = 0; i < size_gr; i++){
            for (int j = 0; j < graph[i].size(); j++){
                tmp[i].push_back(graph[i][j]);
            }
        }
        int v = 0;
        vector<int> result;
        FindEulerPath(v, tmp, result);
        for (auto &a: result){
            cout << a << " ";
        }
        cout << endl;
    }

    void FindEulerPath(int v, vector<vector<int>> &tmp, vector<int> &result){
        for (int i = 0; i < tmp[v].size(); i++){
            int u = tmp[v][i];
            tmp[v].erase(tmp[v].begin() + i);
            auto it = find(tmp[u].begin(), tmp[u].end(), v);
            tmp[u].erase(it);
            FindEulerPath(u, tmp, result);
        }
        result.push_back(v);
    }

    void Kosaraju(){
        visited = new bool[size_gr];
        vector<vector<int>> inv_graph(size_gr);
        vector<int> result;
        vector<int> stack;
        for (int i = 0; i < size_gr; i++) visited[i] = false;
        for (int i = 0; i < size_gr; i++){
            for(int j = 0; j < graph[i].size(); j++){
                int n = graph[i][j];
                inv_graph[n].push_back(i);
            }
        }
        for (int v = 0; v < size_gr; v++){
            if (visited[v] == false) dfs_inv(v, visited, stack);
        }

        cout << "G(inv): " << endl;
        for (auto &a: stack){
            cout << a << " ";
        }
        cout << endl;

        for (int i = 0; i < size_gr; i++) visited[i] = false;
        while(stack.size() > 0){
            int v = stack.back();
            stack.pop_back();
            if (visited[v] == false) dfs_inv(v, visited, result);
        }

        cout << "G: " << endl;
        for (auto &a: result){
            cout << a << " ";
        }
        cout << endl;
    }
};
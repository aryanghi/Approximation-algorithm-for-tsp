//
//  my_Algorithm.h
//  tsp
//
//  Created by Aryan on 1/14/25.
//


#include "common.h"
#include <queue>

using namespace std;


void primMST(const vector<vector<double>>& graph, vector<vector<double>>& mst) {
    int V = (int)graph.size();
    vector<bool> inMST(V, false);
    vector<double> key(V, numeric_limits<double>::infinity());
    vector<int> parent(V, -1);

    key[0] = 0;
    for (int count = 0; count < V - 1; count++) {
        double minKey = numeric_limits<double>::infinity();
        int u = -1;
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    mst.clear();
    mst.resize(V, vector<double>(V, 0));  // ساخت ماتریس مجاورت خالی
    for (int i = 1; i < V; i++) {
        mst[i][parent[i]] = graph[i][parent[i]];
        mst[parent[i]][i] = graph[i][parent[i]];
    }

    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            int u = parent[i];
            int v = i;
            mst[u][v] = graph[u][v];
            mst[v][u] = graph[u][v];
        }
    }
}


void compute_degress(vector<vector<double>> &T, vector<int>& degress){
    degress.clear();
    for(int i=0; i<T.size(); ++i){
        int counter=0;
        for(int j=0; j<T.size(); ++j)
            if(T[i][j] > 0)
                counter++;
        degress.push_back(counter);
    }
}


void compute_branches(vector<int>& degress, vector<int>& branches){
    branches.clear();
    for(int i=0; i<degress.size(); ++i)
        if(degress[i] > 2)
            branches.push_back(i);
}


int delete_branch(int n, vector<vector<double>>& T){
    double maxcost=-1;
    int maxindex=-1;
    
    for(int i=0; i<T.size(); ++i)
        if(T[n][i] >= maxcost){
            maxcost=T[n][i];
            maxindex=i;
        }
    T[n][maxindex]=0;
    T[maxindex][n]=0;
    return maxindex;
}


void leaves_visit(int root, vector<int>& degress, vector<vector<double>>& T, vector<int>& leaves, set<int>& visited){
    visited.insert(root);
    if(degress[root]==1 || degress[root]==0)
        leaves.push_back(root);
    for(int i=0; i<T.size(); ++i)
        if(T[root][i] > 0 && !(visited.contains(i)))
            leaves_visit(i, degress, T, leaves, visited);
}

void leaves_visit_helper(int root, vector<int>& degress, vector<vector<double>>& T, vector<int>& leaves){
    set<int> visited;
    leaves.clear();
    leaves_visit(root, degress, T, leaves, visited);
}


void merge_trees(vector<int>& leaves1, vector<int>& leaves2, const vector<vector<double>>& G, vector<vector<double>>& T) {
    priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, greater<>> pq;
    for (int leaf1 : leaves1)
        for (int leaf2 : leaves2)
            pq.push({G[leaf1][leaf2], leaf1, leaf2});
    
    while (!pq.empty()) {
        auto [cost, leaf1, leaf2] = pq.top();
        pq.pop();
        if (T[leaf1][leaf2] == 0 && T[leaf2][leaf1] == 0) {  // Avoid duplicate edges
            T[leaf1][leaf2] = cost;
            T[leaf2][leaf1] = cost;
            break;
        }
    }
}

void make_path_helper(int root, vector<vector<double>>& T, vector<int>& path, set<int>& visited){
    visited.insert(root);
    path.push_back(root);
    for(int i=0; i<T.size(); ++i)
        if(T[root][i] > 0 && !(visited.contains(i)))
            make_path_helper(i, T, path, visited);
}


void make_path(vector<vector<double>>& T, vector<int>& path){
    vector<int> rightpath;
    vector<int> leftpath;
    set<int> visited;
    int counter=0;
    int index1=-1 , index2=-1;
    
    for(int i=0; i<T.size(); ++i)
        if(T[0][i] > 0){
            counter++;
            if(counter==1)
                index1=i;
            else
                index2=i;
        }
    if(counter==1)
        make_path_helper(0, T, path, visited);
    else{
        visited.insert(0);
        rightpath.push_back(0);
        make_path_helper(index1, T, rightpath, visited);
        make_path_helper(index2, T, leftpath, visited);
        
        for(int i=(int)(leftpath.size())-1; i>=0; --i)
            path.push_back(leftpath[i]);
        for(int i=0; i<rightpath.size(); ++i)
            path.push_back(rightpath[i]);
        
        
    }
}


void print_res(vector<int>& res, const vector<vector<double>>& G){
    double cost=0;
    int i;
    for(i=0; i<res.size()-1; ++i){
        cost=cost+G[res[i]][res[i+1]];
        cout << res[i] << " -> ";
    }
    
    cout<<res[i]<<endl;
    cost=cost+G[res[i]][res[0]];
    cout<< "The cost is "<<cost<<endl;
}


void tspApproximationMST(const vector<vector<double>>& G) {
    vector<vector<double>> T;
    vector<int> degress;
    vector<int> branches;
    vector<int> leaves1;
    vector<int> leaves2;
    vector<int> res;
    int deletedNode;
    
    primMST(G, T);
    compute_degress(T, degress);
    compute_branches(degress, branches);
    while(branches.size() != 0){
        for(int i=0; i<branches.size(); ++i){
            deletedNode=delete_branch(branches[i], T);
            compute_degress(T, degress);
            leaves_visit_helper(deletedNode, degress, T, leaves2);
            leaves_visit_helper(branches[i], degress, T, leaves1);
            merge_trees(leaves1, leaves2, G, T);
            compute_degress(T, degress);
            compute_branches(degress, branches);
        }
    }
    
    make_path(T, res);
    print_res(res, G);
}


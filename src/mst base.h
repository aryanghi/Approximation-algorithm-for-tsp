//
//  mst base.h
//  tsp
//
//  Created by Aryan on 1/14/25.
//

#include "common.h"
#include "AdjacencyListMatrix.h"


using namespace std;


void find_min(const vector<double>& v, double &minn, int &i, const set<int> &my_set){
    i=-1;
    minn=(double)INFINITY;
    for(int j=0; j<v.size(); ++j)
        if(minn>v[j] && !(my_set.contains(j))){
            minn=v[j];
            i=j;
        }

}



void show_res(const vector<int> &res, const vector<vector<double>>& G){
    long double cost=0.0;
    int i;
    for(i=0; i<res.size()-1; ++i)
        cost= cost+ G[res[i]][res[i+1]];
    cost=cost+G[res[i]][0];
    
    cout<<"The path is ";
    
    for(int i=0; i<res.size()-1; ++i)
        cout<<res[i]<< " -> ";
    cout<<"0"<<endl;
    
    cout<<"The cost is "<<cost<< endl;

}



void prim_algorithm(int s, const vector<vector<double>>& G, list_adj &T){
    vector<double> v;
    vector<int> pressedor((int)G.size(),-1);
    v.push_back(0);
    for(int i=0; i<G.size()-1; ++i)
        v.push_back((double)INFINITY);
    
    
    int min_index;
    double min_val;
    set<int> my_res;
    
    my_res.insert(0);
    for(int i=0; i<G.size(); ++i)
        if(!(my_res.contains(i)) && v[i]>G[0][i]){
            v[i]=G[0][i];
            pressedor[i]=0;
        }
    
    while (my_res.size()!=v.size()) {
        find_min(v, min_val, min_index, my_res);
        my_res.insert(min_index);
            for(int i=0; i<G.size(); ++i)
                if(!(my_res.contains(i)) && v[i]>G[min_index][i]){
                    v[i]=G[min_index][i];
                    pressedor[i]=min_index;
                }
        T.add_edg(pressedor[min_index], min_index);
    }
}




void Mst_base(const vector<vector<double>>& G){
    vector<int> res;
    list_adj T(int(G.size()));
    
    prim_algorithm(0, G, T);
    T.preorder(0, res);
    res.push_back(0);
    show_res(res, G);
}



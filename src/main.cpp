//
//  main.cpp
//  tsp
//
//  Created by Aryan on 1/14/25.
//

#include "/Users/macuser/Documents/tsp/tsp/header/dp_and_brute_force.h"
#include "/Users/macuser/Documents/tsp/tsp/header/input.h"
#include "/Users/macuser/Documents/tsp/tsp/header/mst base.h"
#include "/Users/macuser/Documents/tsp/tsp/header/my_Algorithm.h"




int main(int argc, const char * argv[]) {
    vector<string> my_in;
    vector<vector<double>> adj;
    vector<vector<int>>res;
    
    
    read(my_in);
    init(my_in, adj);
    make_adj(my_in , adj);
    
    my_in.clear();
    cout<<"BF ran"<<endl;
    find_all_Hamiltonian_path(adj, res);
    compute_val(adj, res);
    cout<<endl<<"------------------------------------------------------"<<endl;
    cout<<"Dp ran"<<endl;
    cout<<tsp(adj)<<endl;
    cout<<"------------------------------------------------------"<<endl;
    cout<< "Mst base Ran"<<endl;
    Mst_base(adj);
    cout<<"------------------------------------------------------"<<endl;
    cout<< "greedy ran"<<endl;
    tspApproximationMST(adj);
    cout<<"------------------------------------------------------"<<endl;
    
}



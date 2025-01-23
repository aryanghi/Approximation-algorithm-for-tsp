//
//  dp_and_brute_force.h
//  tsp
//
//  Created by Aryan on 1/14/25.
//

#include "common.h"

using namespace std;


void find_all_Hamiltonian_path(const vector<vector<double>>& G, vector<vector<int>>& res, vector<int> tmp = {0}, set<int> visited = {0}) {
    if (tmp.size() == G.size()) {
        tmp.push_back(0);
        res.push_back(tmp);
        return;
    }

    for (int i = 1; i < G.size(); ++i) {
        if (visited.find(i) == visited.end()) {
            tmp.push_back(i);
            visited.insert(i);
            find_all_Hamiltonian_path(G, res, tmp, visited);
            tmp.pop_back();
            visited.erase(i);
        }
    }
}


void compute_val(const vector<vector<double>>& G, const vector<vector<int>>& paths) {
    double minCost = numeric_limits<double>::max();
    vector<int> bestPath;

    for (const auto& path : paths) {
        double cost = 0;
        for (int j = 0; j < path.size() - 1; ++j) {
            cost += G[path[j]][path[j + 1]];
        }
        if (cost < minCost) {
            minCost = cost;
            bestPath = path;
        }
    }

   
    cout << "Optimal Path: ";
    for (int i = 0; i < bestPath.size(); ++i) {
        cout << bestPath[i];
        if (i != bestPath.size() - 1)
            cout << " -> ";
    }
    cout << endl;

    cout<<"The min cost is "<<minCost<<endl;
}


// Function to reconstruct and print the path
void printPath(int mask, int curr, vector<vector<int>> &path, int n) {
    cout << "Path: " << curr; // Start from the current city

    // While not all cities have been visited
    while (mask != (1 << n) - 1) {
        curr = path[mask][curr]; // Get the next city
        cout << " -> " << curr; // Print the next city
        mask |= (1 << curr); // Mark this city as visited
    }

    cout << " -> 0" << endl; // Return to starting city
}



double totalCost(int mask, int curr, int n,
                 vector<vector<double>> &cost, vector<vector<double>> &memo, vector<vector<int>> &path) {
    
    // Base case: if all cities are visited, return the cost to return to the starting city (0)
    if (mask == (1 << n) - 1) {
        return cost[curr][0];
    }

    if (memo[curr][mask] != -1)
        return memo[curr][mask];

    double ans = numeric_limits<double>::max(); // Use max double value

    // Try visiting every city that has not been visited yet
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) { // If city i is not visited
            double newCost = cost[curr][i] + totalCost((mask | (1 << i)), i, n, cost, memo, path);
            if (newCost < ans) {
                ans = newCost;
                path[mask][curr] = i; // Store the next city in the path
            }
        }
    }

    return memo[curr][mask] = ans;
}



double tsp(vector<vector<double>> &cost) {
    int n = (int)cost.size();
    vector<vector<double>> memo(n, vector<double>(1 << n, -1));
    vector<vector<int>> path(1 << n, vector<int>(n, -1)); // To store the best path

    // Start from city 0, and only city 0 is visited initially (mask = 1)
    double minCost = totalCost(1, 0, n, cost, memo, path);

    // Print the minimum cost
    cout << "Minimum cost: " << minCost << endl;

    // Print the best path
    printPath(1, 0, path, n);

    return minCost;
}


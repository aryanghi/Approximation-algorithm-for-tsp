//
//  input.h
//  tsp
//
//  Created by Aryan on 1/14/25.
//

#include "common.h"

using namespace std;

void read(vector<string>& my_in) {
    string file_name;
    cout << "Enter the file name (with path if needed): ";
    cin >> file_name;

    fstream my_file(file_name);
    if (!my_file.is_open()) {
        cerr << "Error: Could not open the file \"" << file_name << "\".\n";
        return;
    }

    string mytxt;
    while (getline(my_file, mytxt)) {
        my_in.push_back(mytxt);
    }

    my_file.close();
}


void make_adj(const vector<string>& s , vector<vector<double>>& v){
    for (int i = 0; i < s.size(); ++i) {
        int j = 0;
        for (j = 0; j < s[i].size(); ++j) {
            if (s[i][j] == ' ')
                break;
        }
        
        string tmp;
        if (j > 0)
            tmp = s[i].substr(0, j);
        
        int row=stoi(tmp);
        j++;
        
        int k=j;
        for(; k<s[i].size(); ++k){
            if (s[i][k] == ' ')
                break;
        }
        
        string tmpp;
        if (j > 0)
            tmpp = s[i].substr(j, k);
        
        int colm=stoi(tmpp);
        k++;
        long double val=(long double)stold(s[i].substr(k,int(s[i].size())));
        v[row][colm]=val;
        v[colm][row]=val;
    }
}


void init(const vector<string>& s, vector<vector<double>>& v){
    int n = (1 + sqrt(1 + 4 * (2*int(s.size()))) / 2);
    for(int i=0; i<n; ++i){
        vector<double> tmp(n);
        v.push_back(tmp);
    }
}
